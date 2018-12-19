#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int num(vector<int> cells) {
        int num = 0;
        for (int i=0;i<8;i++) {
            num = (num*10) + cells[i];
        }

        return num;
    }
    vector<int> tovec(int N) {
        vector<int> ret(8,0);

        int i=7;
        while (i>=0) {
            ret[i] = N & 1;
            N >>=1;
        }

        return ret;
    }
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {

        unordered_map<int, int> lastI;
        vector<int> nxtIndex;

        vector<int> nxt(8);
        vector<int> pre = cells;

        int i=0;
        for (; i<N; i++) {
            int curnum = num(pre);

            if (lastI.find(curnum) != lastI.end()){
                break;
            }
            lastI[curnum] = i;
            nxtIndex.push_back(curnum);

            for (int j=0; j<8; j++) {
                if (j==0 || j==7)
                    nxt[j] = 0;
                else
                    nxt[j] = pre[j-1] == pre[j+1];

            }

            pre = nxt;
        }
        if (i==N)
            return nxt;

        int loopFirstNum = num(pre);
        int loopLen = i - lastI[loopFirstNum];

        return tovec(nxtIndex[lastI[loopFirstNum]+(N-lastI[loopFirstNum])%loopLen]);
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	vector<int> cels = {1,0,0,1,0,0,1,0};
	s.prisonAfterNDays(cels, 100);
	return 0;
}
