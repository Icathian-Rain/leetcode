/*
 * @lc app=leetcode.cn id=450 lang=cpp
 * @lcpr version=30204
 *
 * [450] 删除二叉搜索树中的节点
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
    TreeNode* deleteNodeOpt(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->val) {
            root->left = deleteNodeOpt(root->left, key);
            return root;
        }
        if (key > root->val) {
            root->right = deleteNodeOpt(root->right, key);
            return root;
        }

        if (root->left == nullptr) {
            return root->right;
        }
        if (root->right == nullptr) {
            return root->left;
        }

        TreeNode* successor = root->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        // 用右子树最小节点接住左子树，保持整体中序顺序不变。
        successor->left = root->left;
        return root->right;
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return root;
        if(root->val == key) {
            if(root->left == nullptr && root->right == nullptr) {
                // no left and no right
                delete root;
                return nullptr;
            } else if(root->left == nullptr || root->right == nullptr) {
                // no left or no right
                auto newroot = root->left != nullptr ? root->left : root->right;
                delete root;
                return newroot;
            } else {
                // left and right
                auto cur = root->right;
                while(cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = root->left;
                auto newroot = root->right;
                delete root;
                return newroot;
            }
        }

        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,3,6,2,4,null,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [5,3,6,2,4,null,7]\n0\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */

