/*
 * @lc app=leetcode.cn id=124 lang=cpp
 * @lcpr version=30204
 *
 * [124] 二叉树中的最大路径和
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
    int maxGainOpt(TreeNode* root, int& best) {
        if (root == nullptr) {
            return 0;
        }

        int leftGain = max(0, maxGainOpt(root->left, best));
        int rightGain = max(0, maxGainOpt(root->right, best));
        // 当前节点作为路径最高拐点时，可以同时连接左右两侧。
        best = max(best, root->val + leftGain + rightGain);
        return root->val + max(leftGain, rightGain);
    }

    int maxPathSumOpt(TreeNode* root) {
        int best = INT_MIN;
        maxGainOpt(root, best);
        return best;
    }

    int ans=INT_MIN;

    int dfs(TreeNode* root) {
        if(root == nullptr) return 0;
        
        int leftMax = dfs(root->left);
        int rightMax = dfs(root->right);
        // 情况1: 根节点+两边
        ans = max(ans, leftMax+rightMax+root->val);
        // 情况2: 根节点+一边, 根节点
        int ret = max({leftMax+root->val, rightMax+root->val, root->val});
        ans = max(ans, ret);
        return ret;


    }
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [-10,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [2,-1,-2]
// @lcpr case=end

 */

