#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
		if (needle.size()==0) {
			return 0;
		}
		if ( needle.size() > haystack.size()) {
			return -1;
		}

		vector<int> nxt = getNxt(needle);

		for (size_t j = 0, i = 0; i < haystack.size(); ) {
			if (j<needle.size() &&  needle[j] == haystack[i]) {
				i++;
				j++;
			}
			if (j==needle.size()) {
				return i-j;
			} else if (i < haystack.size() && needle[j] != haystack[i]) {
				if (j==0) {
					i++;
				} else {
					j = nxt[j-1];
				}
			}
		}

		return -1;
    }

	vector<int> getNxt(string s) {
		// nxt[i] : s[0]~s[nxt[i]-1] <==> s[i-1-(nxt[i]-1)] ~ s[i-1]
		// if s[i] not match; i=nxt[i-1]
		vector<int> nxt(s.size(),0);

		size_t suf=1,pre=0;
		while (suf<s.size()) {
			if (s[suf] == s[pre]) {
				nxt[suf++] = ++pre;
			} else {
				if (0 != pre) {
					pre = nxt[pre-1];
				} else {
					nxt[suf++] = 0;
				}
			}
		}

		return nxt;
	}
};

int main(int argc, char *argv[])
{
	Solution s;
	s.strStr("ABABDABACDABABCABAB","ABABCABAB");
	return 0;
}
