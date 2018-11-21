#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int binaryGap(int N) {
        int ret = 0;
        int preOnePosition = -1;
        int count = 0;

        int i=0;
        while (N > (1 << i)) {
            if (!(N & (1<<i))) {
                i++;
				continue;
            }

            if (preOnePosition != -1) {
                ret = max(i-preOnePosition, ret);
            }

            while (N & (1<<i)) {
                i++;
                count ++;
            }
            preOnePosition = i-1;
        }

        return  (!ret&&count>1)?1:ret;
    }
    int binaryGap(int N) {
        int ret = 0;
        int preOnePosition = -1;

        for (int i=0; i<32; i++) {
            if ((N>>i) & 1) {
                if (preOnePosition >= 0) ret = max(ret, i-preOnePosition);

                preOnePosition = i;
            }
        }

        return ret;
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	s.binaryGap(8);
	return 0;
}
