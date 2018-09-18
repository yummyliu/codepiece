// In a 2D grid of 0s and 1s, we change at most one 0 to a 1.
// After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).
// Example 1:
// Input: [[1, 0], [0, 1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
// Example 2:
// Input: [[1, 1], [1, 0]]
// Output: 4
// Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
// Example 3:
// Input: [[1, 1], [1, 1]]
// Output: 4
// Explanation: Can't change any 0 to 1, only one island with area = 4.
//
//  Notes:
//  1 <= grid.length = grid[0].length <= 50.
//  0 <= grid[i][j] <= 1.

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	void merge(int a, int b, vector<int>& ps, map<int,int>& msize) {
		for (size_t i = 0; i < ps.size(); ++i) {
			if (ps[i] == b) {
				ps[i] = a;
			}
		}
		msize[a] += msize[b];
	}

	int largestIsland(vector<vector<int>>& grid) {
		int ret = 1;
		int rn = grid.size();
		int cn = grid[0].size();
		vector<int> ps;
		map<int, int> msize;
		ps.resize(rn*cn);

		for (int i = 0; i < rn; ++i) {
			for (int j = 0; j < cn; ++j) {
				ps[i*cn+j] = i*cn+j;
				if (grid[i][j]) msize[i*cn+j]=1;
			}
		}

		for (int i = 0; i < rn; ++i) {
			for (int j = 0; j < cn; ++j) {
				if (grid[i][j]) {
					if (i-1>=0 && grid[i-1][j]) {
						ps[i*cn+j] = ps[(i-1)*cn+j];
						msize[ps[i*cn+j]] ++;

						if (j-1>=0 && grid[i][j-1] && ps[i*cn+j] != ps[i*cn+j-1]) {
							merge(ps[i*cn+j],ps[i*cn+j-1],ps,msize);
						}
						continue;
					}
					if (j-1>=0 && grid[i][j-1]) {
						ps[i*cn+j] = ps[i*cn+j-1];
						msize[ps[i*cn+j]] ++;
					}
				}
			}
		}

		bool all0 = true;
		for (int i = 0; i < rn; ++i) {
			for (int j = 0;j < cn;j++) {
				if (0==grid[i][j]) {
					all0 = false;
					set<int> ns;
					if (i-1>=0)  ns.insert(ps[(i-1)*cn+j]);
					if (i+1<rn) ns.insert(ps[(i+1)*cn+j]);
					if (j-1>=0)  ns.insert(ps[i*cn+j-1]);
					if (j+1<cn) ns.insert(ps[i*cn+j+1]);

					int tmpret = 1;
					for (auto e : ns) {
						tmpret += msize[e];
					}
					if (tmpret > ret) {
						ret = tmpret;
					}
				}
			}
		}

		if (all0) {
			return rn*cn;
		}
		return ret;
    }
};

int main()
{
	vector<vector<int>> grid = {{1,0,1,0,1},
								{0,1,1,0,1},
								{1,1,1,0,0},
								{1,0,1,1,1},
								{0,0,1,1,0}};
//	{{1,1,1,1,0},
//	 {1,0,0,0,0},
//	 {0,0,0,1,1},
//	 {1,1,0,1,0},
//	 {0,0,0,0,1}};
	Solution s;
	s.largestIsland(grid);
	std::cout << s.largestIsland(grid) << std::endl;
	return 0;
}
