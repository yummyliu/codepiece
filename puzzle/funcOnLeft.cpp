#include <iostream>
using namespace std;
/* such a function will not be safe if x is non static variable of it */
int &fun()
{
   static int x;
   printf("x: %d \n", x);
   static int b;
   printf("b: %d \n", b);
   return x;
}

int main()
{
    static int b = 5;
    int &a = b;
    a = 10;
    std::cout << b << std::endl;

   getchar();
   return 0;
}
