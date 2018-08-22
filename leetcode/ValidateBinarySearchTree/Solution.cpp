/**
 * Definition for a binary tree node.
 */
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	int checker(TreeNode* root, int* _min, int* _max) {
		if (!root) {
			return true;
		}

		int lmin, lmax, rmin, rmax;
		bool leftisvalid = checker(root->left, &lmin, &lmax);
		bool rightisvalid = checker(root->right, &rmin, &rmax);
		if (leftisvalid && rightisvalid
			&& (!root->left || root->val > lmax)
			&& (!root->right || root->val < rmin)
		   ){
			if (!root->left) *_min = root->val;
			else *_min = lmin;
			if (!root->right) *_max= root->val;
			else *_max = rmax;
			return true;
		}
		return false;
	}
    bool isValidBST(TreeNode* root) {
		int tmpmin, tmpmax;
		return checker(root, &tmpmin, &tmpmax);
    }
};

// Given a binary tree, determine if it is a valid binary search tree (BST).
//
// Assume a BST is defined as follows:
//
// The left subtree of a node contains only nodes with keys less than the node's key.
// The right subtree of a node contains only nodes with keys greater than the node's key.
// Both the left and right subtrees must also be binary search trees.
// Example 1:
//
// Input:
//     2
//    / \
//   1   3
// Output: true
// Example 2:
//
//     5
//    / \
//   1   4
//      / \
//     3   6
// Output: false
// Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
//              is 5 but its right child's value is 4.
//
