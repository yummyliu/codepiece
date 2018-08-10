/* =============================================================================
#     FileName: Solution.cpp
#         Desc:
#       Author: LiuYangming
#        Email: sdwhlym@126.com
#     HomePage: http://yummyliu.github.io
#      Version: 0.0.1
#   LastChange: 2018-08-08 14:21:13
#      History:
============================================================================= */
// In this problem, a rooted tree is a directed graph such that,
// there is exactly one node (the root) for which all other nodes are descendants of this node,
// plus every node has exactly one parent, except for the root node which has no parents.
//
// The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N),
// with one additional directed edge added.
// The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges.
// Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v,
// where u is a parent of child v.
//
// Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes.
// If there are multiple answers, return the answer that occurs last in the given 2D-array.
//
// Example 1:
// Input: [[1,2], [1,3], [2,3]]
// Output: [2,3]
// Explanation: The given directed graph will be like this:
//   1
//  / \
// v   v
// 2-->3
// Example 2:
// Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
// Output: [4,1]
// Explanation: The given directed graph will be like this:
// 5 <- 1 -> 2
//      ^    |
//      |    v
//      4 <- 3
// Note:
// The size of the input 2D-array will be between 3 and 1000.
// Every integer represented in the 2D-array will be between 1 and N,
// where N is the size of the input array.
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){
	};
	virtual ~Solution (){};

	vector<int> dfs(int root, int t) {
		vector<int> res;
		if (cs[root][0] == t) {
			// left child
			if (as[0] == root) {
				res.push_back(as[0]);
				res.push_back(cs[root][0]);
				return res;
			} else {
				res.push_back(as[1]);
				res.push_back(cs[root][0]);
				return res;
			}
		} else if (cs[root][1] ==t ) {
			// right child
			if (as[0] == root) {
				res.push_back(as[0]);
				res.push_back(cs[root][1]);
				return res;
			} else {
				res.push_back(as[1]);
				res.push_back(cs[root][1]);
				return res;
			}
		} else {
			// deep search
			auto lres = dfs(cs[root][0], t);
			auto rres = dfs(cs[root][1], t);

			return (lres.size() != 0)? lres:rres;
		}
		return res;
	}

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		vector<int> res;
		int maxV =0;
		for (auto e : edges) {
			int p = e[0];
			int c = e[1];
			if (maxV < p) {
				maxV = p;
			}
			if (maxV < c) {
				maxV = c;
			}

			cs[p].push_back(c);

			if (ps[c].size() == 0) {
				ps[c].push_back(p);
			} else {
				// c has two parent, which is not allowed in a tree
				as[0] = ps[c][0];
				as[1] = p;
				t = c;
				ps[c].erase(ps[c].begin());
			}
		}

		// find root
		int root = 0;
		for (int i = 1; i < maxV; ++i) {
			if (ps[i].size() == 0) {
				root = i;
				break;
			}
		}
		return dfs(root, t);
    }

private:
	vector<int> ps[1001];
	vector<int> cs[1001];
	int as[2];
	int t;
};

int main()
{
	std::vector<vector<int>> v = {{2,1},{3,1},{4,2},{1,4}};
	Solution s;
	s.findRedundantConnection(v);
	return 0;
}
