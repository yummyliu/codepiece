#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include <unistd.h>


void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}
char** pgb_os_argv;
int pgb_argc;
static int
pgb_save_argv(int argc, char *const *argv)
{
    pgb_os_argv = (char **) argv;
    pgb_argc = strlen(argv[0]);

    return 0;
}
int main(int argc, char *argv[])
{

	pgb_save_argv(argc,argv);
	printf("%s\n", pgb_os_argv[0]);
	printf("%d\n", pgb_argc);
	printf("%d\n", argc);
  const char* parent_message = "hello";  // parent process will write this message
  const char* child_message = "goodbye"; // child process will then write this one

  void* shmem = create_shared_memory(128);

  memcpy(shmem, parent_message, sizeof(char)*strlen(parent_message));

  int pid = fork();

  if (pid == 0) {
	strncpy(pgb_os_argv[0],"pgb-worker",pgb_argc);
    //printf("Child read: %s\n", shmem);
    //memcpy(shmem, child_message, sizeof(char)*strlen(child_message));
 	//printf("%s\n", pgb_os_argv[0]);
	//printf("%d\n", pgb_argc);
	//printf("%d\n", argc);
	//printf("Child wrote: %s\n", shmem);
	sleep(30);

  } else {
	strncpy(pgb_os_argv[0],"pgb-master",pgb_argc);
    //printf("Parent read: %s\n", shmem);
    sleep(30);
    //printf("After 1s, parent read: %s\n", shmem);
  }
}
