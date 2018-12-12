#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> ret;

        if (!root) return ret;
		helper(root, "", ret);

		return ret;
    }

	void helper(TreeNode* root, string uppath, vector<string>& ret)
	{
		if (!root->left && !root->right) {
            ret.push_back(uppath.append(to_string(root->val)));
			return;
        }

		if (root->left) helper(root->left, uppath+to_string(root->val)+"->", ret);
		if (root->right) helper(root->right, uppath+to_string(root->val)+"->", ret);
	}
};

