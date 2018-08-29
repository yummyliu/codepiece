// You need to find the largest value in each row of a binary tree.
//
// Example:
// Input:
//
//           1
//          / \
//         3   2
//        / \   \ 
//       5   3   9
//
// Output: [1, 3, 9]
#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
		vector<int> ret;

		vector<TreeNode*> odd;
		vector<TreeNode*> even;
		if (root) even.push_back(root);

		while (!odd.empty() || !even.empty()) {
			if (!odd.empty()) {
				int maxval = odd[0]->val;
				for (auto i : odd) {
					if (i->val > maxval) {
						maxval = i->val;
					}
					if (i->left) even.push_back(i->left);;
					if (i->right) even.push_back(i->right);
				}
				odd.clear();
				ret.push_back(maxval);
			}

			if (!even.empty()) {
				int maxval = even[0]->val;
				for (auto i : even) {
					if (i->val > maxval) {
						maxval = i->val;
					}
					if (i->left) odd.push_back(i->left);;
					if (i->right) odd.push_back(i->right);
				}
				even.clear();
				ret.push_back(maxval);
			}
		}

		return ret;
    }
};
