#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        unordered_set<int> unvisit;
        unordered_map<int,int> gs;
        for (int i=1; i<=N; i++) {
            unvisit.insert(i);
            gs[i] = -1;
        }

        vector<vector<int>> graph(N+1);
        for (auto d : dislikes) {
            int a = d[0];
            int b = d[1];

            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        while (!unvisit.empty()) {
            int cur = *(unvisit.begin());

            gs[cur] = 1;
            if (!helper(cur, graph, gs, unvisit))
                return false;
        }

        return true;
    }

    bool helper(int I, const vector<vector<int>>& graph, unordered_map<int,int>& gs, unordered_set<int>& unvisit) {
        int curgid = gs[I];

        for (int n : graph[I]) {
            if (gs[n] == -1) {
                gs[n] = 1-curgid;
                helper(n, graph, gs, unvisit);
            }

            if (gs[n] == curgid) {
                return false;
            }
        }

        unvisit.erase(I);
        return true;
    }
};

int main(int argc, char *argv[])
{
	int N =4;
	vector<vector<int>> nums = {{1,2},{1,3},{2,4}};

	Solution s;
	cout << s.possibleBipartition(N, nums);
	return 0;
}
