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

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <usual/event.h>
#include <err.h>
#include <sys/socket.h>
#include <sys/queue.h>

#define MAX_CHILDNUM 5
#define BUFLEN 256

typedef void (*spawn_proc_pt) (void *data);
typedef struct event my_event_t;
typedef struct child_s child_t;
struct child_s {
	/* data */
	int channel[2];
	int pid;
	int                 status;

	spawn_proc_pt   proc;
	void               *data;
};
/**
 * In event based programming we need to queue up data to be written
 * until we are told by libevent that we can write.  This is a simple
 * queue of buffers to be written implemented by a TAILQ from queue.h.
 */
struct bufferq {
    /* The buffer. */
    u_char *buf;

    /* The length of buf. */
    int len;

    /* The offset into buf to start writing from. */
    int offset;

    /* For the linked list structure. */
    TAILQ_ENTRY(bufferq) entries;
};

/**
 * A struct for client specific data, also includes pointer to create
 * a list of clients.
 *
 * In event based programming it is usually necessary to keep some
 * sort of object per client for state information.
 */
struct client {
    /* Events. We need 2 event structures, one for read event
     * notification and the other for writing. */
    struct event ev_read;
    struct event ev_write;

    /* This is the queue of data to be written to this client. As
     * we can't call write(2) until libevent tells us the socket
     * is ready for writing. */
    TAILQ_HEAD(, bufferq) writeq;
};

child_t cs[MAX_CHILDNUM];
int ci = 0;

void doprocessing (void* data);
static void sig_parent_handler(int signo);
static void sig_child_handler(int signo);
static void sig_handler(int signo);
static void channel_event_handler(my_event_t *ev);

void on_accept(int fd, short ev, void *arg);
void on_read(int fd, short ev, void *arg);

int ischild=0;
int pid=-1;
char* procName;

struct event_base* ebase;

int main(int argc, char *argv[])
{
	procName = (argv[0]);
	strncpy(argv[0],"mpro-w",strlen(argv[0]));
	if (argc != 2) {
		printf("mpro $port\n");
		exit(0);
	}
	// multiprocess bounded single
	struct sigaction abc;
	abc.sa_handler = sig_handler;
	sigemptyset(&abc.sa_mask);
	abc.sa_flags = 0;

	sigaction(SIGCHLD, &abc, NULL);
	sigaction(SIGINT,  &abc, NULL);
	sigaction(SIGHUP,  &abc, NULL);

	// socket config
	int sockfd, portno;
	struct sockaddr_in serv_addr;

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}

	/* Now start listening for the clients, here
	 * process will go in sleep mode and will wait
	 * for the incoming connection
	 */

	struct event ev_accept;
	ebase = event_init();

	listen(sockfd,5);
	/* We now have a listening socket, we create a read event to
	 * be notified when a client connects. */
	event_set(&ev_accept, sockfd, EV_READ|EV_PERSIST, on_accept, NULL);
	if (event_add(&ev_accept, NULL) < 0) {
		perror("error add event");
	}

	/* Start the libevent event loop. */
	if (0 < event_dispatch()) {
		perror("error add event");
	}
}

void on_accept(int sockfd, short ev, void *arg){

	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);

	int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("ERROR on accept");
		exit(1);
	}

	/* Create child process */
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, cs[ci].channel) == -1)
	{
		printf("socketpair() failed while spawning \"%s\"", "worker");
	}

	pid = fork();

	if (pid < 0) {
		perror("ERROR on fork");
		exit(1);
	}

	if (pid == 0) {
		/* This is the client process */
		printf("%s %d\n", "this is child: ", getpid());
		ischild = 1;
		strncpy(procName,"mpro-w",strlen(procName));

		struct event ev_read;
		event_set(&ev_read, sockfd, EV_READ|EV_PERSIST, on_read, NULL);
		if (event_add(&ev_read, NULL) < 0) {
			perror("error add event");
		}

		/* Start the libevent event loop. */
		if (0 < event_dispatch()) {
			perror("error add event");
		}

		//close(sockfd);
		//doprocessing(newsockfd);
		//exit(0);
	}
	else {
		ci++;
		printf("%s\n", "this is parent");
		for(;;){pause();}
		//close(newsockfd);
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
		err(1, "malloc failed");

	len = read(fd, buf, BUFLEN);
	if (len == 0) {
		/* Client disconnected, remove the read event and the
		 * free the client structure. */
		printf("Client disconnected.\n");
		close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	}
	else if (len < 0) {
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

void doprocessing (void* data) {
	int sock = *(int*)data;
	int n;
	char buffer[256];
	bzero(buffer,256);
	n = read(sock,buffer,255);

	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("Here is the message: %s\n",buffer);
	n = write(sock,"I got your message",18);

	if (n < 0) {
		perror("ERROR writing to socket");
		exit(1);
	}

}
static void sig_parent_handler(int signo)
{
	switch (signo) {
		case SIGCHLD:
			printf("caught SIGCHLD: %d\n", signo);
			break;
		case SIGINT:
			printf("caught SIGINT: %d\n", signo);
			break;
		default:
			printf("caught UnKnown: %d\n", signo);
			break;
	}
}
static void sig_child_handler(int signo)
{
	switch (signo) {
		case SIGCHLD:
			printf("caught child SIGCHLD: %d\n", signo);
			break;
		case SIGINT:
			printf("caught child SIGINT: %d\n", signo);
			break;
		default:
			printf("caught child UnKnown: %d\n", signo);
			break;
	}
}

static void sig_handler(int signo)
{
	if (ischild) {
		sig_child_handler(signo);
	} else {
		sig_parent_handler(signo);
	}
}

static void channel_event_handler(my_event_t *ev){
	while (true) {

	}
}

