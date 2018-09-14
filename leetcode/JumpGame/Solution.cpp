#include <vector>
using namespace std;
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int FD = nums[0]+0;
        int i = 0;
        while (i<nums.size() && i <= FD) {
            if (FD < nums[i]+i)
                FD = nums[i]+i;
            if (FD >= nums.size()-1)
                return true;
            i++;
        }
        return false;
    }
};
