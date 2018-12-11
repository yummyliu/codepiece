#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;
// We partition a row of numbers A into at most K adjacent (non-empty) groups,
// then our score is the sum of the average of each group. What is the largest score we can achieve?
//
// Note that our partition must use every number in A, and that scores are not necessarily integers.
//
// Example:
// Input:
// A = [9,1,2,3,9]
// K = 3
// Output: 20
// Explanation:
// The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
// We could have also partitioned A into [9, 1], [2], [3, 9], for example.
// That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
//
//
// Note:
//
// 1 <= A.length <= 100.
// 1 <= A[i] <= 10000.
// 1 <= K <= A.length.
// Answers within 10^-6 of the correct answer will be accepted as correct.
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
		if (A.empty() || !K) return 0;
		int N = A.size();

		vector<double> sum(N+1);
		sum[0] = 0;
		for (int i = 1; i <= N; ++i) {
			sum[i] = sum[i-1] + A[i-1];
		}

		vector<vector<double>> dp(K+1,vector<double>(N+1,0));
		for (int i = 0; i <= N; ++i) {
			dp[1][i] = sum[i]/i;
		}
		for (int k = 1; k<=K; k++) {
			for (int i = k-1; i <= N; ++i) {
				for (int j = k-1; j <= i-1; ++j) {
					dp[k][i]= max(dp[k][i], (sum[i] - sum[j])/((double)(i-j)) + dp[k-1][j]);
				}
			}
		}

		return dp[K][N];
    }
    double largestSumOfAverages_v1(vector<int>& A, int K) {
		// loop dp
	    int N = A.size();
        vector<int> P(1,0);

        for (int i=0; i<N; ++i) {
            P.push_back(P.back() + A[i]);
        }

        vector<double> dp;
        for(int i = 0; i<N; ++i) {
            dp.push_back(average(P,i,N));
        }

        for(int m=0; m<K-1; m++) {
            for(int i=0; i<N; i++)
                for(int j=i+1;j<N;j++)
                    dp[i] = max(dp[i],average(P,i,j)+dp[j]);
        }

        return dp[0];
    }

    double average(const vector<int> &P, int i, int j) {
        return double((P[j]-P[i]))/(j-i);
    }

};


int main()
{
	Solution s;
	vector<int> A = {1,2,3,4,5,6,7};
	cout << s.largestSumOfAverages(A,4) << endl;
	return 0;
}
