#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int,int> counts;
        for (auto n: nums) {
            counts[n] ++;
            //cout << n << counts[n] << endl;
        }
        for (const auto& p:counts) {
            cout << p.first << p.second << endl;
        }
        cout << "---" << endl;
        int ret=0;
        for (const auto& p:counts) {
            cout << p.first << p.second << endl;
            if (counts.count(p.first+1)>0) {
            // if (counts[p.first+1]) {
                ret = max(p.second+counts[p.first+1], ret);
            }
        }

        return ret;
    }
};

int main(int argc, char *argv[])
{
	vector<int> ns = {1,2,3,4};

	Solution s;
	cout << s.findLHS(ns) <<endl;
	return 0;
}
