#include <stdio.h>

struct
{
	int a : 4;
	int b : 13;
	int c : 1;
} test1;

struct
{
	short a : 4;
	short b : 3;
} test2;

struct
{
	char a : 4;
	char b : 3;
} test3;

struct
{
	char a : 4;
	short b : 3;
} test4;

struct {
	/* data */
	char a;
}test5;

/* Bit fields can only be declared as part of a structure. The address-of operator (&) cannot be applied to bit-field components.
 * Bit fields have the same semantics as the integer type. This means a bit field is used in expressions in exactly the same way as a variable of the same base type would be used, regardless of how many bits are in the bit field.
 */
int main(int argc, char *argv[])
{

	test1.c = 1;
	test1.a = 1;
	test1.b = 1;
	printf("test1: %d\ntest2: %d\ntest3: %d\ntest4: %d\n", sizeof(test1), sizeof(test2), sizeof(test3), sizeof(test4));
	printf("test1.b: %d\ntest2.a: %d\ntest5: %d\n", test1.b, test2.a, sizeof(test5));
	return 0;
}
