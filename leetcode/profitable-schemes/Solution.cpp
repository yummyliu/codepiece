#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
		int MOD = 1e9 + 7;
		int N = group.size();

		// 循环数组
		long dp[2][P+1][G+1];
		memset(dp,0,sizeof(dp));
		dp[0][0][0] = 1;

		for (int i = 0; i < N; ++i) {
			int p0 = profit[i];
			int g0 = group[i];

			auto cur1 = dp[i%2];
			auto cur2 = dp[(i+1)%2];

			for (int jp = 0; jp <= P; jp++ ) {
				for (int jg = 0; jg <= G; jg++ ) {
					cur2[jp][jg] = cur1[jp][jg];
				}
			}

			for (int p1 = 0; p1 <= P; p1++ ) {
				int p = min(p1+p0, P);
				// 题意提炼
				for (int g1 = 0; g1 <= G-g0; g1++ ) {
					int g = g1+g0;
					cur2[p][g] += cur1[p1][g1];
					cur2[p][g] %= MOD;
				}
			}
		}

		long ans=0;
		for (auto x : dp[N%2][P]) {
			ans += x;
		}

		// wrong : return (int) ans%MOD;
		return (int) (ans % MOD);
    }
};
