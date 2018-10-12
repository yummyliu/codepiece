// The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
//
// Now your job is to find the total Hamming distance between all pairs of the given numbers.
//
// Example:
// Input: 4, 14, 2
//
// Output: 6
//
// Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
// showing the four bits relevant in this case). So the answer will be:
// HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
// Note:
// Elements of the given array are in the range of 0 to 10^9
// Length of the array will not exceed 10^4.

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	int totalHammingDistance(vector<int>& nums)
	{
		vector<int> digit0Nums;
		digit0Nums.resize(30);
		vector<int> digit1Nums;
		digit1Nums.resize(30);

		bool allZero = false;
		int id=0;
		while (!allZero) {
			allZero = true;

			for (auto& i : nums) {
				int bit = i%2;
				if (bit==0) {
					digit0Nums[id] ++;
				} else {
					digit1Nums[id] ++;
				}

				i=i/2;
				if (i!=0) {
					allZero = false;
				}
			}
			id++;
		}

		int ret=0;
		for (int i = 0; i < id; ++i) {
			ret += (digit0Nums[i] * digit1Nums[i]);
		}

		return ret;
	}

private:
	/* data */
};

int main()
{
	Solution s;
	vector<int> a = {4,14,2};
	std::cout << s.totalHammingDistance(a) << std::endl; 
	return 0;
}
