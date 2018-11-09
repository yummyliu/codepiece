#include <sys/types.h>
#include <signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int numofchild = 0;
void sigchildhandler() {int aa; numofchild --; wait(&aa);}
int main() {
  char cmd[1000], buf[1000], *argv[2];
  struct sigaction abc;
  int pid;

  abc.sa_handler = sigchildhandler;
  sigemptyset(&abc.sa_mask);
  abc.sa_flags = 0;

  sigaction(SIGCHLD, &abc, NULL);

  while(1) {
      while(fgets(buf, 100, stdin) == NULL);
      sscanf(buf, "%s", cmd);
      printf("%d children, command = %s\n", numofchild, cmd);
      fflush(stdout);
      if (strcmp(cmd, "quit") == 0) {
          if (numofchild == 0) exit(0);
          else printf("Cannot exit, there are still %d children.\n", numofchild);
      }
      if ((pid = fork()) == 0) {
          argv[0] = cmd, argv[1] = NULL;
          execv(argv[0], argv); exit(0);
     }
     if (pid != -1) numofchild ++;
  }
} /* example6.c */
