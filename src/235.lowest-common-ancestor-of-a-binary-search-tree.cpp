/*
 * @lc app=leetcode.cn id=235 lang=cpp
 * @lcpr version=30204
 *
 * [235] 二叉搜索树的最近公共祖先
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
    TreeNode* lowestCommonAncestorOpt(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else {
                // 两个目标分处两侧，或当前节点就是其中之一，当前节点就是 LCA。
                return root;
            }
        }
        return nullptr;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        // 
        if(root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else if(root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else {
            return root;
        }


    }
};
// @lc code=end



/*
// @lcpr case=start
// [6,2,8,0,4,7,9,null,null,3,5]\n2\n8\n
// @lcpr case=end

// @lcpr case=start
// [6,2,8,0,4,7,9,null,null,3,5]\n2\n4\n
// @lcpr case=end

 */

