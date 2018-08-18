// On an N x N grid, each square grid{i}{j} represents the elevation at that point (i,j).
//
// Now rain starts to fall. At time t, the depth of the water everywhere is t.
// You can swim from a square to another 4-directionally adjacent square
// if and only if the elevation of both squares individually are at most t.
// You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?
//
// Example 1:
//
// Input: {{0,2},{1,3}}
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
//
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
// Example 2:
//
// Input: {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}}
// Output: 16
// Explanation:
//  0  1  2  3  4
//  24 23 22 21  5
//  12 13 14 15 16
//  11 17 18 19 20
//  10  9  8  7  6
//
//  The final route is marked in bold.
//  We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
//  Note:
//
//  2 <= N <= 50.
//  grid{i}{j} is a permutation of {0, ..., N*N - 1}.
#include <iostream>
#include <vector>
using namespace std;
class DSU
{
public:
	DSU (int R,int C){
		// root of all grid element is R*C
		par.resize(R*C);
		for (int i = 0; i < R*C ; ++i) {
			par[i] = i;
		}

		rnk.resize(R*C);
		for (int i = 0; i < R*C; ++i) {
			rnk[i] = 0;
		}

		sz.resize(R*C);
		for (int i = 0; i < R*C; ++i) {
			sz[i] = 1;
		}
	};

	virtual ~DSU () {};

	int Find(int x)
	{
		if (par[x] != x) {
			par[x] = Find(par[x]);
		}
		return par[x];
	}

	void Union(int x, int y)
	{
		int xr = Find(x);
		int yr = Find(y);

		if (xr == yr) {
			return;
		}
		if (rnk[xr] < rnk[yr]) {
			/* xr always the higher rank tree
			 */
			swap(xr,yr);
		}
		if (rnk[xr] == rnk[yr]) {
			rnk[xr] ++;
		}
		par[yr] = xr;
		sz[xr] += sz[yr];
	}

	int Size(int x)
	{
		return sz[Find(x)];
	}

	int lastpar()
	{
		return Find(sz.size()-1);
	}
	int firstpar()
	{
		return Find(0);
	}
private:
	/* data */
	vector<int> par;
	vector<int> rnk;
	vector<int> sz;
};
class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

    int swimInWater(vector<vector<int>>& grid) {
		int R = grid.size();
		int C = grid[0].size();
		DSU dsu(R,C);

		for (int r = 0; r < R; ++r) {
			auto row = grid[r];
			for (int c = 0; c < C; ++c) {
				auto h = row[c];
				if (r-1 >= 0 && h == grid[r-1][c]) {
					dsu.Union(r*C+c, (r-1)*C+c);
				}
				if (c-1 >=0 && h == grid[r][c-1]) {
					dsu.Union(r*C+c, r*C+c-1);
				}
			}
		}

		if (dsu.lastpar() == dsu.firstpar()) {
			return 0;
		}

		int t = 0;
		while (dsu.lastpar() != dsu.firstpar()) {
			t++;
			for (int r = 0; r < R; ++r) {
				auto row = grid[r];
				for (int c = 0; c < C; ++c) {
					if (grid[r][c] < t) {
						grid[r][c] = t;
					}
					if (r-1 >= 0 && grid[r-1][c] == grid[r][c]) {
						dsu.Union((r-1)*C+c, r*C+c);
					}
					if (c-1 >= 0 && grid[r][c] == grid[r][c-1]) {
						dsu.Union(r*C+c, r*C+c-1);
					}
				}
			}
		}

		return t;
	}

private:
	/* data */
	int ns[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};
};

int main()
{
	vector<vector<int>> grid = {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};
	Solution s;

	auto a = s.swimInWater(grid);
	std::cout << a << std::endl;
	return 0;
}
