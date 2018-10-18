#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.size() == 0) return 0;

		int R=matrix.size(),C=matrix[0].size();
		vector<vector<int>> keepbook(R);
		for (auto& i : keepbook) {
			i.resize(C,1);
		}

		vector<vector<int>> direct = {{0,1},{0,-1},{1,0},{-1,0}};
		int hasChange = true;
		while (hasChange) {
			hasChange = false;
			for (int i = 0; i < R; ++i) {
				for (int j = 0; j < C; ++j) {
					for (const auto& d : direct) {
						int nxti = d[0]+i;
						int nxtj = d[1]+j;
						if (nxti <0 || nxti >= R || nxtj <0 || nxtj >=C ) continue;

						if (matrix[nxti][nxtj] < matrix[i][j]
							&& keepbook[i][j] <= keepbook[nxti][nxtj]) {
							keepbook[i][j] = keepbook[i][j]+1;
							hasChange = true;
						}
					}
				}
			}
		}

		int MaxLen = 1;
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (keepbook[i][j] > MaxLen) MaxLen = keepbook[i][j];
			}
		}

		return MaxLen;
    }
};

// [[9,9,4],
//  [6,6,8],
//  [2,1,1]]
int main(int argc, char *argv[])
{
	Solution s;
	vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
	cout << s.longestIncreasingPath(matrix) <<endl;

	return 0;
}
