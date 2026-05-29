/*
 * @lc app=leetcode.cn id=110 lang=cpp
 * @lcpr version=30204
 *
 * [110] 平衡二叉树
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
using pii=pair<int, int>;
class Solution {
    int heightOrFailOpt(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = heightOrFailOpt(root->left);
        if (leftHeight == -1) {
            return -1;
        }
        int rightHeight = heightOrFailOpt(root->right);
        if (rightHeight == -1) {
            return -1;
        }

        // 用 -1 作为“不平衡”哨兵，避免额外返回两个状态。
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return max(leftHeight, rightHeight) + 1;
    }

    bool isBalancedOpt(TreeNode* root) {
        return heightOrFailOpt(root) != -1;
    }
 
public:
    pii dfs(TreeNode *root) {
        if(root == nullptr) return {0, true};
        auto [leftDepth, left] = dfs(root->left);
        if(left == false) return {0, false};
        auto [rightDepth, right] = dfs(root->right);
        if(right == false) return {0, false};
        if(abs(leftDepth-rightDepth) > 1) return {0, false};
        return {max(leftDepth, rightDepth)+1, true};
    }


    bool isBalanced(TreeNode* root) {
        return dfs(root).second;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,2,3,3,null,null,4,4]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

