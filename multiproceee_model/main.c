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

int listen_fd;

struct event_base* ebase;
static struct event ev_accept;
static struct event ev_read;
static struct event ev_channel;

void usage()
{
	printf("demo -p $port -g\n\t-p $port\n\t-c clear debug msg");
}

int main(int argc, char *argv[])
{
	procName = (argv[0]);
	strncpy(argv[0],"demo-master",strlen(argv[0]));

	// parse param
	int ch,portno;
	while ((ch = getopt(argc, argv, "gp:")) != -1) {
		switch (ch) {
			case 'p':
				portno = atoi(optarg);
				break;
			case 'g':
				// debug
				cf_verbose = 1;
				break;
			case '?':
			default:
				usage();
				exit(0);
		}
	}
	log_info("verbose: %d\n",cf_verbose);

	sig_regist();

	// config listen_socket
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		log_error("ERROR opening socket");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		log_error("ERROR on binding");
		exit(1);
	}

	listen(listen_fd,5);

	// regist event
	ebase = event_init();
	/*
	 *	Pre-2.0 versions of Libevent did not have event_assign() or event_new().
	 *	Instead, you had event_set(), which associated the event with the "current" base.
	 *	If you had more than one base, you needed to remember to call event_base_set()
	 *	afterwards to make sure that the event was associated with the base you actually wanted to use.
	 *	Interface
	 *	void event_set(struct event *event, evutil_socket_t fd, short what,
	 *	        void(*callback)(evutil_socket_t, short, void *), void *arg);
	 *	        int event_base_set(struct event_base *base, struct event *event);
	 *	event_set can set only once
	 */
	event_set(&ev_accept, listen_fd, EV_READ|EV_PERSIST, on_accept, NULL);
	if (event_add(&ev_accept, NULL) < 0) {
		log_error("error add event");
	}

	// loop event
	if (0 < event_dispatch()) {
		log_error("error event_dispatch");
	}
}
void on_accept(int sockfd, short ev, void *arg){

	log_debug("on_accept: %d, %p\n", ev, arg);

	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);

	int child_accept_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (child_accept_sockfd < 0) {
		log_error("ERROR on accept");
		exit(1);
	}
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, cs[clen].channel) == -1) {
		log_error("socketpair() failed while spawning \"%s\"", "worker");
	}

	pid = fork();
	if (pid < 0) {
		log_error("ERROR on fork");
		exit(1);
	} else if (pid == 0) {
		pid = getpid();
		log_debug("%s %d\n", "this is child: ", pid);
		ischild = true;
		my_pos = clen;
		strncpy(procName,"demo-slave",strlen(procName));

		event_set(&ev_read, child_accept_sockfd, EV_READ|EV_PERSIST, on_read, NULL);
		if (event_add(&ev_read, NULL) < 0) {
			log_error("error add event");
		}
		event_set(&ev_channel, cs[my_pos].channel[1], EV_WRITE|EV_PERSIST, on_channel, NULL);
		if (event_add(&ev_channel, NULL) < 0) {
			log_error("error add event");
		}

		event_del(&ev_accept);
		close(cs[my_pos].channel[0]);
		close(listen_fd);
	} else {
		close(cs[clen++].channel[1]);
		clen++;
		log_debug("fork one child");
		close(child_accept_sockfd);
	}
}

void on_read(int fd, short ev, void *arg)
{
	u_char *buf;
	int len;

	/* Because we are event based and need to be told when we can
	 * write, we have to malloc the read buffer and put it on the
	 * clients write queue. */
	buf = (u_char*)malloc(BUFLEN);
	if (buf == NULL)
		log_error("malloc failed");

	len = read(fd, buf, BUFLEN);
	if (len == 0) {
		/* Client disconnected, remove the read event and the
		 * free the client structure. */
		log_info("Client disconnected.\n");
		close(fd);
		event_del(&ev_read);
		return;
	} else if (len < 0) {
		/* Some other error occurred, close the socket, remove
		 * the event and free the client structure. */
		log_debug("Socket failure, disconnecting client: %s",
				strerror(errno));
		close(fd);
		event_del(&ev_read);
		return;
	}

	log_debug("%d got msg: %s\n", pid, buf);
	// /* We can't just write the buffer back as we need to be told
	//  * when we can write by libevent.  Put the buffer on the
	//  * client's write queue and schedule a write event. */
	// bufq = (struct bufferq*)calloc(1, sizeof(struct bufferq));
	// if (bufq == NULL)
	// 	err(1, "malloc faild");
	// bufq->buf = buf;
	// bufq->len = len;
	// bufq->offset = 0;
	// TAILQ_INSERT_TAIL(&client->writeq, bufq, entries);

	// /* Since we now have data that needs to be written back to the
	//  * client, add a write event. */
	// if (0 < event_add(&client->ev_write, NULL)) {
	// 	log_error("Error event add");
	// }
}

void on_channel(int sockfd, short ev, void *arg){
	struct msghdr msg;
	recvmsg(sockfd, &msg, 0);
	// TODO

}


