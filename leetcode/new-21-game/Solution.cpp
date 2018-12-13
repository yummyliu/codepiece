#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double new21Game(int N, int K, int W) {
        vector<double> dp(N+W+1,0);
        for (int i=K; i<N+1; i++)
            dp[i] = 1.0;

        double S = min(N-K+1, W);
        for (int i=K-1; i>=0; i--) {
            dp[i] = S/double(W);
            S += dp[i]-dp[i+W];
        }

        return dp[0];
    }
};
