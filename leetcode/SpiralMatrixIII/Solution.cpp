// https://leetcode.com/problems/spiral-matrix-iii/description/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
		int tmpmax0 = (R-1-r0 < r0)?r0:R-1-r0;
		int tmpmax1 = (C-1-c0 < c0)?c0:C-1-c0;
		int radius = (tmpmax0 > tmpmax1)? tmpmax0 : tmpmax1;

		vector<vector<int>> newM;
		newM.resize(radius*2+1);
		for (auto &e : newM) {
			e.resize(radius*2+1);
		}

		int moveR = radius - r0;
		int moveC = radius - c0;
		int Rlow = moveR;
		int Clow = moveC;
		int Rhigh = R+moveR;
		int Chigh = C+moveC;

		for (int i = Rlow; i < Rhigh; ++i) {
			for (int j = Clow; j < Chigh; j++) {
				newM[i][j] = 1;
			}
		}

		vector<vector<int>> ret;
		int curR = 0; //
		char curdirection = 'r';
		int i = radius, j = radius;
		for (; ret.size() < size_t(R*C);) {
			if (newM[i][j] == 1) {
				ret.push_back({i-Rlow,j-Clow});
			}
			std::cout << ret.size() <<" "<< i-Rlow << " " << j-Clow <<" "<< curdirection<< std::endl;

			switch (curdirection) {
				case 'r':
					if (j == radius + curR) {
						curdirection = 'd';
						curR ++;
						j ++;
						break;
					}
					j ++;
					break;
				case 'd':
					if (i == radius + curR) {
						curdirection = 'l';
						j--;
						break;
					}
					i++;
					break;
				case 'l':
					if (j == radius - curR) {
						curdirection = 'u';
						i--;
						break;
					}
					j --;
					break;
				case 'u':
					if ( i == radius - curR) {
						curdirection = 'r';
						j++;
						break;
					}
					i --;
					break;
			}
		}

		return ret;
	}
};

int main()
{
	Solution s;
	auto r = s.spiralMatrixIII(3,3,1,1);

	return 0;
}
