#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Given a non-empty string check if it can be constructed by taking a substring of it
// and appending multiple copies of the substring together.
// You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

    bool repeatedSubstringPattern(string s) {
		int N = s.size();
		int i = 1;
		int j = 0;

		vector<int> dp(N+1,0); // dp[i+1] means how many repeated char before i
		while (i < N) {
			if (s[i] == s[j]) {
				dp[++i] == ++j;
			} else if (j==0) {
				i++;
			} else {
				j = dp[j-1];
			}
		}

		return dp[N] && N % (N-dp[N]) == 0;
	}
private:
	/* data */
};

int main(int argc, char *argv[])
{
	Solution s;
	string ss = "abababaabababaabababa";
	cout << s.repeatedSubstringPattern(ss) << endl;
	return 0;
}
