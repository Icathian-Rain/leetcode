/*
 * @lc app=leetcode.cn id=105 lang=cpp
 * @lcpr version=30204
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
    unordered_map<int, int> inorderIndex;

    TreeNode* buildTreeOpt(vector<int>& preorder, int preL, int preR,
                           int inL, int inR) {
        if (preL == preR) {
            return nullptr;
        }

        int rootVal = preorder[preL];
        TreeNode* root = new TreeNode(rootVal);
        int rootIndex = inorderIndex[rootVal];
        int leftSize = rootIndex - inL;

        // 前序首位是根；中序根左侧的长度决定左右子树区间。
        root->left = buildTreeOpt(preorder, preL + 1, preL + 1 + leftSize,
                                  inL, rootIndex);
        root->right = buildTreeOpt(preorder, preL + 1 + leftSize, preR,
                                   rootIndex + 1, inR);
        return root;
    }

    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int preL, int preR, int inL, int inR) {
        if(inL == inR) return nullptr;
        int rootVal = preorder[preL];
        TreeNode* root = new TreeNode(rootVal);
        int lpreL = preL+1;
        int lpreR;
        int linL  = inL;
        int linR = inL;
        while(inorder[linR] != rootVal) {
            linR++;
        }
        int lSize = linR - linL;
        lpreR = lpreL+lSize;

        root->left = build(preorder, inorder, lpreL,lpreR, linL, linR);
        root->right = build(preorder, inorder, lpreR, preR, linR+1, inR);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,9,20,15,7]\n[9,3,15,20,7]\n
// @lcpr case=end

// @lcpr case=start
// [-1]\n[-1]\n
// @lcpr case=end

 */

