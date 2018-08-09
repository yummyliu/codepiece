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
// there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
//
// The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.
//
// Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.
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
// Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){
		for (int i = 0; i <= 1001; ++i) {
			ps[i] = -1;
		}
	};
	virtual ~Solution (){};

	int parent(int i) {
		while (ps[i] != i && ps[i] != -1) {
			i = ps[i];
		}
		if (ps[i] == i) {
			return -1;
		}
		return i;
	}

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		vector<int> res;
		for (auto e : edges) {
			// u < v
			int parent_u = parent(e[0]);
			int parent_v = parent(e[1]);
			if (parent_u == parent_v) {
				res = e;
			}
			ps[e[1]] = parent_u;
			ps[parent_v] = parent_u;
		}

		return res;
    }

private:
	int ps[1001];
};

int main(int argc, char *argv[])
{
	// 一次ac通过，調。。
	std::vector<vector<int>> v = {{}{}{}{}{}};
	return 0;
}
