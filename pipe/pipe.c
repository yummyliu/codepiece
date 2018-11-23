/* implement '/bin/ps -ef | /bin/more' */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int st;

main() {
	int fds[2];
	char *argv[3];
	pipe(fds); 
	if (fork() == 0) {
		close(0); dup(fds[0]);        /* redirect standard input to fds[0] */
		//    close(fds[1]);
		argv[0] = "/usr/bin/more"; argv[1] = 0;
		if (execv(argv[0], argv) == -1) {
			printf("/usr/bin/more failed\n");
		}
		exit(0);
	} if (fork() == 0) {
		close(1); dup(fds[1]);        /* redirect standard output to fds[1];*/
		close(fds[1]);
		argv[0] = "/bin/ps"; argv[1] = "-ef"; argv[2] = 0;
		if (execv(argv[0], argv) == -1) {
			printf("/bin/ps failed\n");
		}
		exit(0);
	}
	close(fds[1]);
	wait(&st); wait(&st);
} 
