#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
		int curMax = INT_MIN;
		int i = nums.size()-1;

		while (i>=0) {
			if (nums[i] >= curMax) {
				curMax = nums[i];
			} else {
				int j = i-1;
				while (j < (int)nums.size() && nums[j] > nums[i]) {
					j ++;
				}
				swap(nums[i], nums[j-1]);
				break;
			}

			i--;
		}

        reverse(nums.begin()+i+1, nums.end());
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	vector<int> ns = {1,2,3};
	s.nextPermutation(ns);
	return 0;
}
