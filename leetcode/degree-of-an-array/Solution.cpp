class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> firstPos;
        unordered_map<int, int> allCount;
        unordered_map<int, bool> visit;

        int maxlen = 1;
        for (int i=0; i<nums.size(); i++) {
            if (firstPos.end() == firstPos.find(nums[i])) {
                firstPos[nums[i]] = i;
                allCount[nums[i]] = 1;
                visit[nums[i]] = false;
            } else {
                allCount[nums[i]] ++;
                maxlen = max(maxlen, allCount[nums[i]]);
            }
        }

        int minret = nums.size();
        for (int i=nums.size()-1; i>=0; i--) {
            if (allCount[nums[i]] == maxlen && !visit[nums[i]]) {
                minret = min(minret, i-firstPos[nums[i]]+1);

                visit[nums[i]] = true;
            }
        }

        return minret;
    }
};
