#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

static char *str1 = "OP1\n";

int main()
{
  int f1;

  close(STDOUT_FILENO); // STDOUT_FILENO = 1  
  f1 = open ("myjunk", O_RDWR | O_CREAT | O_TRUNC, 0777);
  close(STDERR_FILENO); // STDERR_FILENO = 2
  dup(f1);

  cout << "print to standard output!!!, f1 = " << f1 << "\n";fflush(0); 
  cout << "print to standard output!!!, f1 = " << f1 << "\n";fflush(0);
  cerr << "print to standard error!!!, f1 = " << f1 << "\n";fflush(0); 

  cerr << "print to standard error!!!, f1 = " << f1 << "\n";fflush(0); 
  write(1, str1, strlen(str1));fflush(0);
  write(1, str1, strlen(str1));fflush(0);

  return 0;
}
