// Your are given an array of positive integers nums.
//
// Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
//
// Example 1:
// Input: nums = [10, 5, 2, 6], k = 100
// Output: 8
// Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
// Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
// Note:
//
// 0 < nums.length <= 50000.
// 0 < nums[i] < 1000.
// 0 <= k < 10^6.
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
		int N = nums.size();
		int ret = 0;
		int i = 0;

		while (i < N) {
			long product = nums[i];

			int j = i;
			while (j < N && product < k) {
				j++;
				product *= nums[j];
			}

			long M = j-i;
			if (j==N ) {
				ret += (M*(M+1))/2;
				break;
			}
			if (j == i) {
				i++;
				continue;
			}

			int diff = 1;
			while (nums[i+diff] == nums[i] && nums[i+diff]==1) {
				diff ++;
			}
			ret += (M*(M+1))/2 - ((M-diff)*(M-diff+1))/2;

			i += diff;
		}

		return ret;
	}
};

int main()
{
	Solution s;
	vector<int> a = {1,1,2,1,1,3,1};
	int r =s.numSubarrayProductLessThanK(a,3);

	std::cout << r << std::endl;
	return 0;
}
