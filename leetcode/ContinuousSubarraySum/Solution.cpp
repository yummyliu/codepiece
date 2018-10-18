class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (k == 0) {
            int i = 0;
            while (i< (int)nums.size() && nums[i]!=0) i++;
            int j = i;
            while (j < (int)nums.size() && nums[j]==0) j++;
            if (j-i > 1)
                return true;
            else 
                return false;
        }
        
        vector<int> presum(nums.size());
        int tmpsum = 0;
        for (int i = 0; i< (int)nums.size(); i++) {
            tmpsum+=nums[i];
            presum[i] = tmpsum;
            if (i == 0 || presum[i] % k != 0) continue;
            else return true;
        }
        
        for (int i=1; i< (int)nums.size(); i++) {
            for (int j=i+1; j < (int)nums.size(); j++) {
                int cursum = presum[j] - presum[i-1];
                if (cursum % k != 0) continue;
                else return true;
            }
        }
        return false;
    }
};
