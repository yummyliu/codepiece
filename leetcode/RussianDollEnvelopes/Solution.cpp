#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEnvelopes_0(vector<pair<int, int>>& envelopes) {
		// Time Limit Exceeded 
		if (0 == envelopes.size()) {
			return 0;
		}

		vector<vector<bool>> iscover; // iscover[i][j] : envelopes[j] can cover envelopes[i]
		iscover.resize(envelopes.size());
		for (auto& i : iscover) {
			i.resize(envelopes.size());
		}

		for (int i = 0; i < int(envelopes.size()); ++i) {
			for (int j = 0; j < int(envelopes.size()); ++j) {
				if (i == j) {
					continue;
				}

				if (envelopes[i].first < envelopes[j].first
						&& envelopes[i].second < envelopes[j].second) {
					iscover[i][j] = true;
				}
			}
		}

		set<int> curNodes;
		for (int i = 0; i < int(iscover.size()); ++i) {
			int j = 0;
			while (j < int(iscover.size()) && !iscover[j][i]) {
				j++;
			}
			if (j == int(iscover.size())) {
				// envelopes[i] cover nothing
				curNodes.insert(i);
			}
		}

		int maxLen = 0;
		while (!curNodes.empty()) {
			maxLen ++;

			set<int> newNodes;
			for (auto e : curNodes) {
				for (int i = 0; i < int(envelopes.size()); ++i) {
					if (iscover[e][i]) {
						newNodes.insert(i);
					}
				}
			}

			curNodes = newNodes;
		}

		return maxLen;
    }
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
		// Time Limit Exceeded 
		if (0 == envelopes.size()) {
			return 0;
		}

		vector<vector<bool>> iscover; // iscover[i][j] : envelopes[j] can cover envelopes[i]
		iscover.resize(envelopes.size());
		for (auto& i : iscover) {
			i.resize(envelopes.size());
		}

		for (int i = 0; i < int(envelopes.size()); ++i) {
			for (int j = 0; j < int(envelopes.size()); ++j) {
				if (i == j) {
					continue;
				}

				if (envelopes[i].first < envelopes[j].first
						&& envelopes[i].second < envelopes[j].second) {
					iscover[i][j] = true;
				}
			}
		}

		vector<int> curMaxLen;
		curMaxLen.resize(envelopes.size());
		set<int> curNodes;
		for (int i = 0; i < int(iscover.size()); ++i) {
			int j = 0;
			while (j < int(iscover.size()) && !iscover[j][i]) {
				j++;
			}
			if (j == int(iscover.size())) {
				// envelopes[i] cover nothing
				curMaxLen[i] = 1;
				curNodes.insert(i);
			}
		}

		while (!curNodes.empty()) {
			set<int> newNodes;
			for (auto e : curNodes) {
				for (int i = 0; i < int(iscover.size()); ++i) {
					if (iscover[e][i] && curMaxLen[i] < curMaxLen[e]+1) {
						curMaxLen[i] = curMaxLen[e] +1;
						newNodes.insert(i);
					}
				}
			}
		}

		int maxLen = 1;
		for (auto curm : curMaxLen) {
			if (curm> maxLen) {
				maxLen = curm;
			}
		}
		return maxLen;
    }
    int maxEnvelopes_1(vector<pair<int, int>>& es) {
        sort(es.begin(), es.end(), [](pair<int, int> a, pair<int, int> b){
            return a.first < b.first || (a.first == b.first && a.second > b.second);});
        vector<int> dp;
        for (auto e : es)
        {
            auto iter = lower_bound(dp.begin(), dp.end(), e.second);
            if (iter == dp.end())
                dp.push_back(e.second);
            else if (e.second < *iter)
                *iter = e.second;
        }
        return dp.size();
    }


    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if (envelopes.empty()) return 0;
		// std::pair uses lexicographic comparison: It will compare based on the first element. If the values of the first elements are equal, it will then compare based on the second element.
		//
		// The definition in the C++03 standard (section 20.2.2) is:
		//
		// template <class T1, class T2>
		// bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y);
		//
		// Returns: x.first < y.first || (!(y.first < x.first) && x.second < y.second).
        sort(envelopes.begin(), envelopes.end());
        vector<int> dp(envelopes.size(), 1);
        for (int i = 0; i < envelopes.size(); ++i)
            for (int j = 0; j < i; ++j)
                if (envelopes[j].first < envelopes[i].first && envelopes[j].second < envelopes[i].second)
                    dp[i]  = max(dp[i] , dp[j] + 1);
        return *max_element(dp.begin(), dp.end());
    }
};
