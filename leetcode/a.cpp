#include <iostream>
using namespace std;
void func(int * a) {
	*a ++;
}

void func1(int& a) {
	a ++;
}

int main(int argc, char *argv[])
{
	int a = 10;
	func(&a);
	std::cout << a << std::endl;

	int b = 10;
	func1(b);
	std::cout << b << std::endl;
	return 0;
}
