#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> diStringMatch(string S) {
        vector<int> ans(S.size()+1,-1);

        int i=0, n=0;
        while (i < S.size()) {
            if (S[i] == 'I')
                ans[i] = n++;
            i++;
        }

        ans[i--] = n++;

        while (i>=0) {
            if (S[i] == 'D')
                ans[i] = n++;
            i--;
        }

        return ans;
    }
};
