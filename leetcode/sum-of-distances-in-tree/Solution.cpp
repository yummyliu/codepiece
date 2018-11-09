#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
		vector<vector<int>> adjacent(N,vector<int>());
		for (auto& v : edges) {
			adjacent[v[0]].push_back(v[1]);
			adjacent[v[1]].push_back(v[0]);
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
