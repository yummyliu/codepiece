#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        sum = accumulate(nums.begin(), nums.end(), 0);

        return pick(true,0,nums.size()-1,nums,0);
    }

    bool pick(bool ismyturn, int left, int right, vector<int>& nums, int cursum) {
        if (left > right) {
            return cursum >= (sum-cursum);
        }

        if (ismyturn) {
            return pick(!ismyturn, left+1, right, nums, cursum+nums[left])
                || pick(!ismyturn, left, right-1, nums, cursum+nums[right]);
        } else {
            return pick(!ismyturn, left+1, right, nums, cursum)
                && pick(!ismyturn, left, right-1, nums, cursum);
        }
    }

    int sum;
};

int main(int argc, char *argv[])
{
	vector<int> num = {1,5,233,7};
	Solution s;

	s.PredictTheWinner(num);
	return 0;
}
