#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int characterReplacementv1(string s, int k) {
        int N = s.size();
        if (N <= 1) return N;

        vector<pair<int,char>> prerepeats(N);   // prerepeats[i].first :  repeated count
                                                // prerepeats[i].second :
        int i = 0;
        while (i < N) {
            int cur = i++;
            while (i < N && s[i] == s[i-1]) {
                i ++;
            }
            prerepeats.push_back(make_pair(i-cur, s[cur]));

        }

        int MaxLen = min(N,prerepeats.back().first+k);
        i = prerepeats.size()-1;
        while (i >=0) {
            int curLen = prerepeats[i].first;
            int curchar = prerepeats[i].second;
            int remainK = k;
            int prej = i-1;
            while (prej >=0 && remainK>=0) {
                if (prerepeats[prej].second == curchar) {
                    curLen += prerepeats[prej].first;
                    prej --;
                    continue;
                }
                else if (!remainK) break;
                else {
                    remainK -= prerepeats[prej].first;
                    curLen += prerepeats[prej].first;
                    prej--;
                }
            }
            if (prej < 0 && remainK >0) curLen = min(curLen + remainK, N);
            MaxLen = max(MaxLen,curLen);
            i--;
        }

        return MaxLen;
    }
	int characterReplacement(string s, int k) {
	    int i = 0, j = 0, ctr[91] = {};
	    while (j < s.size()) {
	        ctr[s[j++]]++;
	        if (j-i - *max_element(ctr+65, ctr+91) > k)
	            ctr[s[i++]]--;
	    }
	    return j - i;
	}
};
