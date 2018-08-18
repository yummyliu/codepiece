#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class DSU
{
public:
	DSU (int R){
		// root of all grid element is R*C
		par.resize(R);
		for (int i = 0; i < R ; ++i) {
			par[i] = i;
		}

		rnk.resize(R);
		for (int i = 0; i < R; ++i) {
			rnk[i] = 0;
		}

		sz.resize(R);
		for (int i = 0; i < R; ++i) {
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

	int Rsize()
	{
		int count=0;
		int S = par.size();
		for (int i = 0; i < S; ++i) {
			if (i == par[i]) count ++;
		}
		return count;
	}

private:
	/* data */
	vector<int> par;
	vector<int> rnk;
	vector<int> sz;
};

class Solution {
public:

    int numSimilarGroups(vector<string>& A) {
		int R = A.size();
		DSU dsu(R);

		// init Union
		for (int i = 0; i < R; ++i) {
			for (int j = i+1; j < R;j ++) {
				if (isSimilar(A[i], A[j])) {
					dsu.Union(i, j);
				}
			}
		}

		// return root set
		return dsu.Rsize();
    }
private:
	bool isSimilar(string A, string B) {
		const char* cA = A.c_str();
		const char* cB = B.c_str();

		vector<int> pc;
		for (size_t i = 0; i < A.size(); ++i) {
			if (cA[i] - cB[i] !=0) {
				pc.push_back(cA[i] - cB[i]);
			}
		}
		if (pc.size() == 2 && pc[0] == pc[1]*(-1)) {
			return true;
		}

		if (A.compare(B) == 0) {
			sort(A.begin(), A.end());
			for (size_t i = 0; i < A.size()-1; ++i) {
				if (A[i] == A[i+1]) {
					return true;
				}
			}
		}

		return false;
	}

};

int main(int argc, char *argv[])
{
	vector<string> A = {"aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa"};//,"aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa","aaaaaaaaa"};

	Solution s;
	int c = s.numSimilarGroups(A);
	std::cout << c << std::endl;
	return 0;
}
