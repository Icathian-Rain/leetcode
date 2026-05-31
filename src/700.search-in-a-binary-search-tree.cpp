/*
 * @lc app=leetcode.cn id=700 lang=cpp
 * @lcpr version=30204
 *
 * [700] 二叉搜索树中的搜索
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
    TreeNode* searchBSTOpt(TreeNode* root, int val) {
        while (root != nullptr && root->val != val) {
            // BST 搜索每次只保留可能包含 val 的一侧子树。
            root = val < root->val ? root->left : root->right;
        }
        return root;
    }

public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) return nullptr;
        if(root->val == val) return root;
        else if(root->val < val) return searchBST(root->right, val);
        else return searchBST(root->left, val);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,7,1,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [4,2,7,1,3]\n5\n
// @lcpr case=end

 */

