/*
 * @lc app=leetcode.cn id=226 lang=cpp
 * @lcpr version=30204
 *
 * [226] 翻转二叉树
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    TreeNode* invertTreeOpt(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode* left = invertTreeOpt(root->left);
        TreeNode* right = invertTreeOpt(root->right);
        root->left = right;  // 左右子树已经各自翻转，再交换到当前节点两侧。
        root->right = left;
        return root;
    }

public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        auto left = invertTree(root->left);
        auto right = invertTree(root->right);
        root->right = left;
        root->left = right;
        return root;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,7,1,3,6,9]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,3]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

