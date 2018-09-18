#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string complexNumberMultiply(string a, string b) {
		auto aplus = a.find_first_of('+');
		auto ai = a.find_first_of('i');
		auto a1 = atoi(a.substr(0,aplus).c_str());
		auto a2 = atoi(a.substr(aplus+1,ai-aplus-1).c_str());

		auto bplus = b.find_first_of('+');
		auto bi = b.find_first_of('i');
		auto b1 = atoi(b.substr(0,bplus).c_str());
		auto b2 = atoi(b.substr(bplus+1,bi-bplus-1).c_str());

		return to_string(a1*b1-a2*b2)+"+"+to_string(a1*b2+a2*b1)+"i";
    }
};

int main(int argc, char *argv[])
{
	Solution s;

	std::cout << s.complexNumberMultiply("33+31i", "23+49i")  << std::endl;
	return 0;
}
