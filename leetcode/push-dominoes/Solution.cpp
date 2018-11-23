#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string pushDominoes(string dominoes) {
		int N = dominoes.size();

		vector<int> R(N, INT_MAX);
		vector<int> L(N, INT_MAX);

		int l=N-1;
		while (l>=0) {
			while (l>=0 && dominoes[l] != 'L') {
				--l;
				continue;
			}
			if (l>=0) L[l--] = 0;
			else continue;

			int d = 0;
			while (l>=0 && dominoes[l] == '.') {
				L[l--] = ++d;
			}
		}

		int r=0;
		while (r<N) {
			while (r<N && dominoes[r] != 'R') {
				++r;
				continue;
			}
			if (r<N) R[r++] = 0;
			else continue;

			int d = 0;
			while (r<N && dominoes[r] == '.') {
				R[r++] = ++d;
			}
		}

		string ret;

		for (int i = 0; i < N; ++i) {
			if (abs(L[i]) < abs(R[i])) {
				ret.append("L");
			} else if (abs(L[i]) > abs(R[i])) {
				ret.append("R");
			} else {
				ret.append(".");
			}
		}

		return ret;
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	s.pushDominoes(".L.R...LR..L..");
	return 0;
}
