#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minDeletionSizeI(vector<string>& A) {
        int d=0;
        for (int c=0;c<A[0].size();c++) {
            int r=0;
            for (;r<A.size()-1 && A[r][c]<=A[r+1][c]; r++);
            if (r!=A.size()-1) d++;
        }
        return d;
    }

	int	minDeletionSize(vector<string>& A) {
		int maxlen = 1;
		int M = A.size();
		int N = A[0].size();
		vector<int> dp(N,1);

		for (int j=1; j<N; j++) {
			int k=j-1;
			while (k >=0) {
				int i = 0;
				for (; i < M && A[i][k] <= A[i][j]; ++i);
				if (i==M) {
					dp[j] = max(dp[k]+1, dp[j]);
					maxlen = max(dp[j], maxlen);
				}
				k--;
			}
		}

		return N-maxlen;
	}
};


