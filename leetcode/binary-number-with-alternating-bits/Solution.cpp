#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool hasAlternatingBits(int n) {
		int pre = -1;

		while (n != 0 ) {
			cur = n%2;
			if (pre != -1 && pre == cur) {
				return false;
			}
			pre = cur;
			n = n/2;
		}

		return true;
    }
};
