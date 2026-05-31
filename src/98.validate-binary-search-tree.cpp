/*
 * @lc app=leetcode.cn id=98 lang=cpp
 * @lcpr version=30204
 *
 * [98] 验证二叉搜索树
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

using ll=long long;
class Solution {
    bool isValidBSTOpt(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) {
            return true;
        }

        // 每个节点都必须落在祖先传下来的开区间内，而不只是满足父子关系。
        if (root->val <= lower || root->val >= upper) {
            return false;
        }
        return isValidBSTOpt(root->left, lower, root->val) &&
               isValidBSTOpt(root->right, root->val, upper);
    }

public:

    ll mv = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root==nullptr) return true;
        bool left = isValidBST(root->left);
        if(mv < root->val) mv = root->val;
        else return false;
        bool right = isValidBST(root->right);
        return left && right;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,1,3]\n
// @lcpr case=end

// @lcpr case=start
// [5,1,4,null,null,3,6]\n
// @lcpr case=end

 */

