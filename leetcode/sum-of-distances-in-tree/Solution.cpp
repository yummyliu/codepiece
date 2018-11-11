#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
	void dfs0(int parent, int cur, vector<vector<int>>& adj, vector<int>& count, vector<int>& sum)
	{

		for (auto nxt : adj[cur]) {
			if (nxt == parent) continue;

			dfs0(cur, nxt,adj,count,sum);

			count[cur] += count[nxt];
			sum[cur] += sum[nxt]+count[nxt];
		}
		count[cur]++;
	}

	void dfs1(int parent, int cur, int N, vector<vector<int>>& adj, vector<int>& count, vector<int>& sum, vector<int>& ans)
	{
		for (auto nxt : adj[cur]) {
			if (nxt == parent) continue;

			ans[nxt] = ans[cur] + N - 2*count[nxt];

			dfs1(cur, nxt, N, adj, count, sum, ans);
		}
	}

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
		vector<vector<int>> adjacent(N,vector<int>());
		for (auto& v : edges) {
			adjacent[v[0]].push_back(v[1]);
			adjacent[v[1]].push_back(v[0]);
		}
		vector<int> count(N, 0);
		vector<int> sum(N, 0);
		vector<int> ans(N, 0);

		dfs0(-1, 0, adjacent, count, sum);
		ans[0] = sum[0];
		dfs1(-1, 0, N, adjacent, count, sum, ans);

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
