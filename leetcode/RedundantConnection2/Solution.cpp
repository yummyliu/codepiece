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

		bool checkloop(int a, std::vector<int> ps) {
			int i =a;
			while (ps[i] != 0 && ps[i] != a) {
				i = ps[i];
			}
			if (ps[i] == a) {
				return true;
			}
			return false;
		}

		vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
			bool dup_parent =false;
			vector<int> ps(edges.size()+1, 0);
			vector<vector<int>> res;

			// whether one point has two parent
			for (auto& e : edges) {
				int p = e[0];
				int c = e[1];

				if (ps[c] > 0) {
					res.push_back({ps[c],c});
					res.push_back(e);
					dup_parent = true;
					e[0] = e[1] = -1;
				} else {
					ps[c] = p;
				}
			}

			ps = vector<int>(edges.size()+1, 0);
			// whether has a loop
			for (auto& e : edges) {
				int p = e[0];
				int c = e[1];

				if (p==-1) continue;

				ps[c] = p;

				if (checkloop(p, ps)) {
					return dup_parent? res[0] : e;
				}
			}

			// no loop
			return res[1];
		}


	private:
};

int main()
{
//	std::vector<vector<int>> v = {{2,1},{3,1},{4,2},{1,4}};
	std::vector<vector<int>> v = {{1,2},{2,3},{3,4},{4,1},{1,5}};
//	std::vector<vector<int>> v = {{4,1},{1,5},{4,2},{5,1},{4,3}};
	Solution s;
	auto res = s.findRedundantDirectedConnection(v);

	for (auto i : res) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
