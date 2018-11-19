class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int d=0;
        for (int c=0;c<A[0].size();c++) {
            int r=0;
            for (;r<A.size()-1 && A[r][c]<=A[r+1][c]; r++);
            if (r!=A.size()-1) d++;
        }
        return d;
    }
};
