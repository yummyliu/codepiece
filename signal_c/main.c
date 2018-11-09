#include <sys/types.h>
#include <signal.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int ischild=0;
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
int main(int argc, char *argv[])
{
	int pid;

	struct sigaction abc;
	abc.sa_handler = sig_handler;
	sigemptyset(&abc.sa_mask);
	abc.sa_flags = 0;

	sigaction(SIGCHLD, &abc, NULL);
	sigaction(SIGINT,  &abc, NULL);
	sigaction(SIGHUP,  &abc, NULL);

	if ((pid = fork()) != 0) {
		printf("%s\n", "this is parent");
		strncpy(argv[0],"master",strlen(argv[0]));
		for(;;){pause();}
	} else {
		printf("%s\n", "this is child");
		ischild = 1;
		strncpy(argv[0],"child",strlen(argv[0]));
		for(;;){pause();}
	}
} /* example6.c */
