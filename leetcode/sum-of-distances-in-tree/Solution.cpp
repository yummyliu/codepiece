#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
	void dfs(int upnode, int i, int N, vector<vector<bool>>& vs, vector<vector<int>>& adj, vector<vector<int>>& D){
		bool allvisited = true;
		for (int e = 0; e < (int)adj[i].size(); ++e) {
			if (adj[i][e]==upnode) {
				continue;
			}
			allvisited &= vs[i][e];
		}
		if (allvisited) {
			return;
		}

		for (int j = 0; i < (int)adj[i].size(); ++i) {
			vs[i][j] = true;
			D[i][adj[i][j]] = 1;
			dfs(i, adj[i][j],N,vs,adj,D);
			for (int e = 0; e < N; e++) {
				if (D[j][e] != INT_MAX ) {
					D[i][e] = D[j][e]+1;
				}
			}
		}
	}
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
		vector<vector<int>> adjacent(N,vector<int>());
		vector<vector<int>> D(N,vector<int>(N,INT_MAX));
		for (auto& v : edges) {
			adjacent[v[0]].push_back(v[1]);
			adjacent[v[1]].push_back(v[0]);
		}
		vector<vector<bool>> visited(N);
		for (int i = 0; i < N; ++i) {
			visited[i].resize(adjacent[i].size(), false);
		}

		for (int i = 0; i < N; ++i) {
			dfs(-1, i, N, visited, adjacent, D);
		}

		vector<int> ans;
		for (int i = 0; i < N; ++i) {
			ans.push_back(accumulate(D[i].begin(), D[i].end(), 0, [](int a, int b){
							if (INT_MAX == b) {
								return a;
							}
							return a+b;
						}));
		}
		return ans;
    }
};

int main()
{
	vector<vector<int>> es = {{2,0},{1,0}};
	Solution s;
	auto res = s.sumOfDistancesInTree(3,es);

	for (auto i : res) {
		std::cout << i << std::endl;
	}
	return 0;
}
