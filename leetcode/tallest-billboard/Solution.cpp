class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;

        for (auto r : rods) {
            unordered_map<int, int> cur(dp);

            for(auto p : cur) {
                int diff = p.first;
                dp[diff+r] = max(dp[diff+r], cur[diff]);
                dp[abs(diff-r)] = max(dp[abs(diff-r)], cur[diff]+min(r, diff));
            }
        }

        return dp[0];
    }
};
