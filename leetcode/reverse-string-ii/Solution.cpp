#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {
        int N = s.size();

		int i = 0;
		while (i < N) {
			int end = min(i+k, N);
			reverse(s.begin()+i, s.begin()+end);
			i += 2*k;
		}

		return s;
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	cout << s.reverseStr("abcd", 4) <<endl;

	return 0;
}
