#ifndef GLOBAL_H
#define GLOBAL_H

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

#include "usual/logging.h"

#define MAX_CHILDNUM 5
#define BUFLEN 256

typedef void (*spawn_proc_pt) (void *data);
typedef struct event my_event_t;
typedef struct child_s child_t;
typedef struct client client_t;

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

struct child_s {
	int		channel[2];
	int		pid;
	int     status;

	spawn_proc_pt   proc;
	void    *data;

	client_t conn_clients;
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


extern child_t cs[MAX_CHILDNUM];
extern int clen;
extern int my_pos;

void doprocessing (void* data);
void sig_regist();

void on_accept(int fd, short ev, void *arg);
void on_read(int fd, short ev, void *arg);
void on_channel(int fd, short ev, void *arg);


extern bool ischild;
extern int pid;
extern char* procName;

extern struct event_base* ebase;

extern int cf_verbose;

#endif /* ifndef GLOBAL_H */
