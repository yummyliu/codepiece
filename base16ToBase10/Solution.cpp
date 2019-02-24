#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<unsigned int> bin2dec(vector<unsigned int> binary)
{
    vector<unsigned int> decimal;
    bool all_zero = false;

    // binary[i]: stores 8-bit of the nubmer.
    // Ex. 258 = 0x102 => binary[0] = 0x2, binary[1] = 0x1.
    while (!all_zero) {
        all_zero = true;
        for (int i = binary.size() - 1; i >= 0; i--) {
            int q = binary[i] / 10;
            int r = binary[i] % 10;

            binary[i] = q;
            if (i > 0) {
                binary[i-1] += (r << 8);
            } else {
                decimal.insert(decimal.begin(), r);
            }
            if (q != 0) {
                all_zero = false;
            }
        }
    }
    // each element stands for one digit of the decimal number.
    // Ex. 258 => decimal[0] = 2, decimal[1] = 5, decimal[2] = 8.
    return decimal;
}

int main(int argc, char *argv[])
{
	vector<unsigned int> binary = {13,14,15};

	for (auto a : bin2dec(binary)) {
		cout << a ;
	}
	cout <<endl;
	return 0;
}
