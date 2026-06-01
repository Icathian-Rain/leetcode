/*
 * @lc app=leetcode.cn id=112 lang=cpp
 * @lcpr version=30204
 *
 * [112] 路径总和
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
    bool hasPathSumOpt(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        // 只有叶子节点才能判断一条完整的根到叶路径。
        if (root->left == nullptr && root->right == nullptr) {
            return targetSum == root->val;
        }

        int rest = targetSum - root->val;
        return hasPathSumOpt(root->left, rest) ||
               hasPathSumOpt(root->right, rest);
    }

public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;
        targetSum -= root->val;
        if(root->left == nullptr && root->right == nullptr) {
            if(targetSum == 0) return true;
            else return false;
        } 
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);

    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,4,8,11,null,13,4,7,2,null,null,null,1]\n22\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n5\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */

