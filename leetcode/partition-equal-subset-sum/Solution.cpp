#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum % 2) {
			return false;
		}

		vector<bool> dp(sum/2+1, false);
		dp[0] = true;
		for (auto e : nums) {
			for (int i = sum/2;i >= e; --i) {
				if (dp[i-e]) {
					dp[i] = true;
				}
			}
		}

		return dp[sum/2];
    }
    bool canPartitionV1(vector<int>& nums) {
        bitset<10001> bits(1);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (auto n : nums) bits |= bits << n;
        return !(sum & 1) && bits[sum >> 1];
    }
};


int main(int argc, char *argv[])
{
	Solution s;
	vector<int> n = {100,100,100,100,100,100,100,100};
	cout << s.canPartition(n) <<endl;
	return 0;
}
