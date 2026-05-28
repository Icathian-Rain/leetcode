/*
 * @lc app=leetcode.cn id=104 lang=cpp
 * @lcpr version=30204
 *
 * [104] 二叉树的最大深度
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
    int maxDepthOpt(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = maxDepthOpt(root->left);
        int rightDepth = maxDepthOpt(root->right);
        return max(leftDepth, rightDepth) + 1; // 当前节点贡献 1 层。
    }

public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return max(leftDepth, rightDepth)+1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2]\n
// @lcpr case=end

 */

