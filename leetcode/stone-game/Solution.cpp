#include <vector>
using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int N = piles.size();

        sum = accumulate(piles.begin(), piles.end(), 0);

        vector<vector<int>> memo1(N, vector<int>(N, -1));
        vector<vector<int>> memo2(N, vector<int>(N, -1));

        return pick(true, 0, piles.size()-1, piles, 0, memo1, memo2);
    }

    bool pick(bool alexTurn, int left, int right,
              const vector<int>& piles, int alexNum,
			  vector<vector<int>>& memo1,
			  vector<vector<int>>& memo2) {
        if (left > right) {
            return alexNum > sum - alexNum;
        }

        if (alexTurn) {
            if (memo1[left][right]!=-1)
                return memo1[left][right];
            else {
                memo1[left][right] = pick(!alexTurn, left+1, right, piles, alexNum+piles[left],memo1, memo2)
                    || pick(!alexTurn, left, right-1, piles, alexNum+piles[right], memo1, memo2);
                return memo1[left][right];
            }
        } else {
            if (memo2[left][right]!=-1)
                return memo2[left][right];
            else {
                memo2[left][right] =  pick(!alexTurn, left+1, right, piles, alexNum, memo1, memo2)
                    && pick(!alexTurn, left, right-1, piles, alexNum, memo1, memo2);
                return memo2[left][right];
            }
        }
    }

    int sum;
};

int main(int argc, char *argv[])
{
	vector<int> nums = {3,7,2,3};

	Solution s;
	s.stoneGame(nums);
	return 0;
}
