class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        
        int pre = 0, nxt = 0;
        
        for (;nxt < nums.size(); nxt ++) {
            if (nums[nxt] == nums[pre]) continue;
            
            nums[++pre] = nums[nxt];
        }
        if (nxt > pre)
            nums.erase(nums.begin()+pre+1,nums.end());
        return nums.size();
    }
};
