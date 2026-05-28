/*
 * @lc app=leetcode.cn id=100 lang=cpp
 * @lcpr version=30204
 *
 * [100] 相同的树
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
    bool isSameTreeOpt(TreeNode* p, TreeNode* q) {
        if (p == nullptr || q == nullptr) {
            return p == q; // 只有两个空节点才算结构相同。
        }
        if (p->val != q->val) {
            return false;
        }
        return isSameTreeOpt(p->left, q->left) &&
               isSameTreeOpt(p->right, q->right);
    }

public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr) return true;
        if((p==nullptr && q!= nullptr)||(p!=nullptr && q==nullptr)) return false;
        if(p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n[1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n[1,null,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1]\n[1,1,2]\n
// @lcpr case=end

 */

