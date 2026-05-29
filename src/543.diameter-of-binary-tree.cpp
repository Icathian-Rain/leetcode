/*
 * @lc app=leetcode.cn id=543 lang=cpp
 * @lcpr version=30204
 *
 * [543] 二叉树的直径
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
    int ans=0;
    int dfs(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        // cout << root->val << " " << left << " " << right << endl;
        ans = max(ans, left+right);
        return max(left, right)+1;
    }

    int depthOpt(TreeNode* root, int& diameter) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = depthOpt(root->left, diameter);
        int rightDepth = depthOpt(root->right, diameter);
        // 经过当前节点的最长路径边数 = 左深度 + 右深度。
        diameter = max(diameter, leftDepth + rightDepth);
        return max(leftDepth, rightDepth) + 1;
    }

    int diameterOfBinaryTreeOpt(TreeNode* root) {
        int diameter = 0;
        depthOpt(root, diameter);
        return diameter;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

 */

