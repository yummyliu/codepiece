class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int d=0;
        int N = A.size();
        int M = A[0].size();

        vector<bool> isorder(N,false);
        isorder[N-1] = true;

        for (int j = 0; j<M; j++) {
            int i=0;
            for (; i<N-1 && (A[i][j] <= A[i+1][j] || isorder[i]); i++);
            if (i < N-1) {
                d++;
                continue;
            }

            for (int i = 0; i<N-1; i++) {
                if (A[i][j] < A[i+1][j]) {
                    isorder[i] = true;
                }
            }
        }


        return d;
    }
};
