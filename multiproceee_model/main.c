/* =============================================================================
#     FileName: main.c
#         Desc:
#       Author: LiuYangming
#        Email: sdwhlym@gmail.com
#     HomePage: http://yummyliu.github.io
#      Version: 0.0.1
#   LastChange: 2018-11-23 17:08:39
#      History:
============================================================================= */
#include "main.h"

child_t cs[MAX_CHILDNUM];
int clen = 0;
int my_pos = -1;
bool ischild=false;
int pid=-1;
char* procName;
struct event_base* ebase;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("mpro $port\n");
		exit(0);
	}
	procName = (argv[0]);
	strncpy(argv[0],"demo-master",strlen(argv[0]));

	sig_regist();

	// socket config & listen
	int sockfd;
	int portno = atoi(argv[1]);
	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	listen(sockfd,5);

	// event regist
	struct event ev_accept;
	ebase = event_init();
	event_set(&ev_accept, sockfd, EV_READ|EV_PERSIST, on_accept, NULL);
	if (event_add(&ev_accept, NULL) < 0) {
		perror("error add event");
	}

	/* Start the libevent event loop. */
	if (0 < event_dispatch()) {
		perror("error event_dispatch");
	}
}

void on_channel(int sockfd, short ev, void *arg){
	struct msghdr msg;
	recvmsg(sockfd, &msg, 0);
	// TODO

}

void on_accept(int sockfd, short ev, void *arg){

	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);

	// XXX accept before fork? or fork before accept?
	int child_accept_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (child_accept_sockfd < 0) {
		perror("ERROR on accept");
		exit(1);
	}

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, cs[clen].channel) == -1) {
		printf("socketpair() failed while spawning \"%s\"", "worker");
	}

	pid = fork();
	if (pid < 0) {
		perror("ERROR on fork");
		exit(1);
	} else if (pid == 0) {
		printf("%s %d\n", "this is child: ", getpid());
		ischild = true;
		my_pos = clen;
		strncpy(procName,"demo-slave",strlen(procName));

		struct event ev_read;
		event_set(&ev_read, child_accept_sockfd, EV_READ|EV_PERSIST, on_read, NULL);
		event_set(&ev_read, cs[my_pos].channel[1], EV_WRITE|EV_PERSIST, on_channel, NULL);

		if (event_add(&ev_read, NULL) < 0) {
			perror("error add event");
		}

		// XXX child do not need event_init again?
		if (0 < event_dispatch()) {
			perror("error add event");
		}

	} else {
		clen++;
		printf("%s\n", "fork one child");
	}
}

void on_read(int fd, short ev, void *arg)
{
	struct client *client = (struct client *)arg;
	struct bufferq *bufq;
	u_char *buf;
	int len;

	/* Because we are event based and need to be told when we can
	 * write, we have to malloc the read buffer and put it on the
	 * clients write queue. */
	buf = (u_char*)malloc(BUFLEN);
	if (buf == NULL)
		perror("malloc failed");

	len = read(fd, buf, BUFLEN);
	if (len == 0) {
		/* Client disconnected, remove the read event and the
		 * free the client structure. */
		printf("Client disconnected.\n");
		close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	} else if (len < 0) {
		/* Some other error occurred, close the socket, remove
		 * the event and free the client structure. */
		printf("Socket failure, disconnecting client: %s",
				strerror(errno));
		close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	}

	/* We can't just write the buffer back as we need to be told
	 * when we can write by libevent.  Put the buffer on the
	 * client's write queue and schedule a write event. */
	bufq = (struct bufferq*)calloc(1, sizeof(struct bufferq));
	if (bufq == NULL)
		err(1, "malloc faild");
	bufq->buf = buf;
	bufq->len = len;
	bufq->offset = 0;
	TAILQ_INSERT_TAIL(&client->writeq, bufq, entries);

	/* Since we now have data that needs to be written back to the
	 * client, add a write event. */
	if (0 < event_add(&client->ev_write, NULL)) {
		perror("Error event add");
	}
}

