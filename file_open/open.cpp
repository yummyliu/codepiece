//example1.cpp
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
int main()
{
  int f1, f2, f3, f4, f5, f6;
  f1 = open("open.cpp", O_RDONLY);
  cout << "f1 = " << f1 << "\n";
  f2 = open("open.cpp", O_RDONLY);
  cout <<  "f2 = " << f2 << "\n";
  close(1);
  f3 = open("aaa", O_RDONLY | O_WRONLY | O_CREAT, 0666);
  cout <<  "f3 = " << f3 << "\n";
  cerr <<  "f3 = " << f3 << "\n";
}

