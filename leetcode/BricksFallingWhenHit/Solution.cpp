#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU
{
public:
	DSU (int R,int C){
		// root of all grid element is R*C
		par.resize(R*C+1);
		for (int i = 0; i < R*C+1 ; ++i) {
			par[i] = i;
		}

		rnk.resize(R*C+1);
		for (int i = 0; i < R*C+1; ++i) {
			rnk[i] = 0;
		}

		sz.resize(R*C+1);
		for (int i = 0; i < R*C+1; ++i) {
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

	int top()
	{
		// Size of component at ephemeral "source" node at index R*C,
		// minus 1 to not count the source itself in the size
		return Size(sz.size()-1) - 1;
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
	Solution (){
		ns = {{0,1},{0,-1},{1,0},{-1,0}};
	};
	virtual ~Solution (){};

	int index(int r, int c)
	{
		return r*C + c;
	}

	vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
		R = grid.size();
		C = grid[0].size();

		/* cut grid into diff set with hits
		 * 1. mark hit to 0
		 */
		vector<vector<int>> A;
		for (auto &i : grid) {
			A.push_back(i);
		}
		for (auto &e : hits) {
			auto i = e[0];
			auto j = e[1];

			A[i][j] = 0;
		}
		/* 2. union subset
		 */
		DSU dsu(R,C);
		for (size_t r = 0; r < A.size(); ++r) {
			auto row = A[r];
			for (size_t c = 0; c < row.size(); ++c) {
				auto val = row[c];

				if (val) {
					int i = index(r, c);
					if (r == 0) {
						dsu.Union(i, R*C);
					}
					if (r && A[r-1][c]) {
						dsu.Union(i, index(r-1, c));
					}
					if (c && A[r][c-1]) {
						dsu.Union(i, index(r, c-1));
					}
				}
			}
		}

		vector<int> ans;
		std::reverse(hits.begin(),hits.end());
		for (auto &e : hits) {
			int r = e[0];
			int c = e[1];

			/* 与roof连接的set有多大，如果本次hit能够连接一部分，那么这部分就是hit会掉落的部分。
			 */
			int pre_roof = dsu.top();

			if (grid[r][c]==0) {
				ans.push_back(0);
			} else {
				int i = index(r, c);
				for (auto &n : ns) {
					int nr = r+n[0];
					int nc = c+n[1];
					if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
						continue;
					}
					if (A[nr][nc]) {
						dsu.Union(i, index(nr, nc));
					}
				}

				if (r == 0) {
					dsu.Union(i, R*C);
				}
				A[r][c] =1;
				ans.push_back(max(0, dsu.top() - pre_roof - 1));
			}
		}
		std::reverse(begin(ans),end(ans));
		return ans;
    }

	int R,C;
private:
	/* data */
	vector<vector<int>> ns;
};

int main()
{
	vector<vector<int>> grid = {{1,1,1},{0,1,0},{0,0,0}};
	vector<vector<int>> hits = {{0,2},{2,0},{0,1},{1,2}};

	Solution s;
	auto ans = s.hitBricks(grid, hits);

	for (auto i : ans) {
		std::cout << i << std::endl;
	}
	return 0;
}
