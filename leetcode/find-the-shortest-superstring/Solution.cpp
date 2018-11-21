#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
		vector<vector<string>> twos(A.size(), vector<string>(A.size(),""));

		int i,j,N = A.size();

		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				if (i==j) continue;

				twos[i][j] = strSuff(A[i],A[j]);
			}
		}

		string ans="";

		return ans;
    }

	string strSuff(string h, string t) {
		int hi=h.size()-1, Nh=h.size(), maxlen=0;

		for (; hi>0; hi--) {
			if (h[hi]!=t[0]) continue;

			if (h.substr(hi) == t.substr(0,Nh-hi)) {
				maxlen = max(maxlen, Nh-hi);
			}
		}

		return t.substr(maxlen);
	}
};

int main(int argc, char *argv[])
{

	Solution s;
	vector<string> a = {"catg","ctaagt","gcta","ttca","atgcatc"};
	s.shortestSuperstring(a);
	return 0;
}
