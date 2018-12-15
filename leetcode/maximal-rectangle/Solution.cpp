class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int M = matrix.size();
        if (!M)
            return 0;
        int N = matrix[0].size();

        vector<vector<int>> horiDp(M+1, vector<int>(N+1, 0));
        int maxret =0;

        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                int I=i+1;
                int J=j+1;

                if (matrix[i][j] == '1') {
                    horiDp[I][J] = horiDp[I][J-1]+1;

                    int k=i-1, minWidth=horiDp[I][J];
                    maxret = max(maxret, 1*minWidth);
                    while (k>=0 && matrix[k][j]=='1') {
                        minWidth = min(minWidth, horiDp[k+1][J]);
                        int minHeigh = i-k+1;
                        maxret = max(maxret, minHeigh*minWidth);

                        k--;
                    }
                }
            }
        }

        return maxret;
    }
};
