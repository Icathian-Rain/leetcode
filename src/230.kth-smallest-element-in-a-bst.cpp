/*
 * @lc app=leetcode.cn id=230 lang=cpp
 * @lcpr version=30204
 *
 * [230] 二叉搜索树中第 K 小的元素
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
    int kthSmallestOpt(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }

            cur = st.top();
            st.pop();
            // BST 中序遍历按升序访问，第 k 次弹出的节点就是答案。
            if (--k == 0) {
                return cur->val;
            }
            cur = cur->right;
        }

        return -1;
    }

    int idx = 1;
    int dfs(TreeNode* root, int k) {
        if(root == nullptr) return -1;
        int ans = dfs(root->left, k);
        if(ans != -1) return ans;
        if(idx == k) return root->val;
        idx++;
        return dfs(root->right, k);

    }
public:
    int kthSmallest(TreeNode* root, int k) {
        return dfs(root, k);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,1,4,null,2]\n1\n
// @lcpr case=end

// @lcpr case=start
// [5,3,6,2,4,null,null,1]\n3\n
// @lcpr case=end

 */

