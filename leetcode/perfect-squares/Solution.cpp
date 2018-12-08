#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
	Solution () {
	}
    int numSquares(int n) {
		numsquaresRets.resize(n,-1);

		return helper(n);
    }

	int helper(int n)
	{
		int square = (int)sqrt(n);
		if (n == square*square) {
			numsquaresRets[n] = 1;
			return 1;
		}

        int minN = INT_MAX;
        for (int s = square; s>0; s--) {
			if (numsquaresRets[n-s*s]!=-1) {
				minN = min(minN, numsquaresRets[n-s*s]);
			} else {
				numsquaresRets[n-s*s] = 1+helper(n-s*s);
				minN = min(minN, numsquaresRets[n-s*s]);
			}
        }

        return minN;
	}

private:
	vector<int> numsquaresRets;
};
