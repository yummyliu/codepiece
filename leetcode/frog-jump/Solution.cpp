#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, unordered_set<int>> stepMap;
        vector<int> maxStep(stones.size(), 0);
        stepMap[0].insert(0);

		// based on curStone get to the furthest stone,
		// if can not get to i,
		//	then curStone ++ , since maxStep[curStone] always >=1, i always > curStone
        int curStone = 0;
        for (int i = 1; i < stones.size(); ++i) {
            while (maxStep[curStone] + 1 < stones[i] - stones[curStone]) ++curStone;

		// though maxStep[curStone] + 1 >= stones[i] - stones[curStone],
		// but it dose not promise that curStone can jump to i, because curStone can only jump stepMap[curStone](+-1) step
		// so it need check it, can all other stone between curStone and i
            for (int j = curStone; j < i; ++j) {
                int t = stones[i] - stones[j];

                if (stepMap[j].count(t - 1)
					|| stepMap[j].count(t)
					|| stepMap[j].count(t + 1)) {
                    stepMap[i].insert(t);
                    maxStep[i] = max(maxStep[i], t);
                }
            }
        }
        return maxStep.back() > 0;
    }
};

