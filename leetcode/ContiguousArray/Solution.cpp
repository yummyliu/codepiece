// Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
//
// Example 1:
// Input: [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
// Example 2:
// Input: [0,1,0]
// Output: 2
// Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
// Note: The length of the given binary array will not exceed 50,000.

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    Solution (){};
    virtual ~Solution (){};

    int findMaxLength_old(vector<int>& nums) {

        if (nums.size() < 2) {
            return 0;
        }

        int one_sums[nums.size()];
        memset(one_sums,0,sizeof(one_sums));
        one_sums[0] = nums[0];

        int maxLen  = 0;
        for (int i=1; i < int(nums.size()); ++i) {
            one_sums[i] = one_sums[i-1] + nums[i];

            int j = -1;
            while (j<i) {
                int low_bound = 0;
                if (j != -1) {
                    low_bound = one_sums[j];
                }
                if (i - j == 2*(one_sums[i]-low_bound)) {
                    if (maxLen < i-j) {
                        maxLen = i-j;
                    }
                }
                j++;
            }
        }
        return maxLen;
    }

    int findMaxLength(vector<int>& nums)
    {
        std::map<int, int> sumMap;
        sumMap[0]=-1;

        size_t maxLen = 0;
        int sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            sum += (nums[i] << 1) -1;
            if (sumMap.count(sum)) {
//                std::cout << "find sum same: "<< sum <<" in: "<<i << ", change" <<  maxLen << "->";
                maxLen = (i-sumMap[sum] > maxLen)?(i-sumMap[sum]):maxLen;
 //               std::cout << maxLen << std::endl;
            } else {
                sumMap[sum]=i;
            }
        }

        return maxLen;
    }

private:
    /* data */
};

int main()
{
    Solution s;
    std::vector<int> v = {1,1,0,1,1,0,1,0,1,1,1,1};
//    std::vector<int> v = {0,1};
    for (auto i : v) {
        std::cout << i ;
    }
    std::cout << std::endl;
    std::cout << s.findMaxLength(v) << std::endl;
    return 0;
}
