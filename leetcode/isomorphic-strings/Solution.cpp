#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size())
            return false;
        int N = s.size();

		unordered_map<char, char> ut;
        int i=1;
        while (i<N) {
			if ((s[i]!=s[i-1] && t[i]==t[i-1])
				|| (s[i]==s[i-1] && t[i]!=t[i-1])) {
				break;
			}
			if (s[i]!=s[i-1] && t[i]!=t[i-1]) {
				if (ut.find(t[i]) == ut.end()) {
					ut[t[i]] = s[i];
				} else if (ut[t[i]] != s[i]) {
					break;
				}
			}

			i++;
        }

		return i==N;
    }
};
