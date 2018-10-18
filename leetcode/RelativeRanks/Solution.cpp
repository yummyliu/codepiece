#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
		map<int, int> position;
		for (int i = 0; i < (int)nums.size(); ++i) {
			position[nums[i]] = i;
		}

        sort(nums.begin(), nums.end(),[](int a, int b) {
            return a > b;
        });

        vector<string> out(nums.size());
        for (int i = 0; i< (int)nums.size(); i++) {
			if (i == 0) {
				out[position[nums[i]]] = "Gold Medal";
			} else if (i == 1) {
				out[position[nums[i]]] = "Silver Medal";
			} else if (i == 2) {
				out[position[nums[i]]] = "Bronze Medal";
			} else {
				out[position[nums[i]]] = std::to_string(i+1);
			}
        }

        return out;
    }
};
