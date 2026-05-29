/*
 * @lc app=leetcode.cn id=199 lang=cpp
 * @lcpr version=30204
 *
 * [199] 二叉树的右视图
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
    void dfsRightFirst(TreeNode* node, int depth, vector<int>& ans) {
        if (node == nullptr) {
            return;
        }

        // 第一次到达某一层时，由于先走右子树，该节点就是这一层右视图节点。
        if (depth == static_cast<int>(ans.size())) {
            ans.push_back(node->val);
        }
        dfsRightFirst(node->right, depth + 1, ans);
        dfsRightFirst(node->left, depth + 1, ans);
    }

    vector<int> rightSideViewOpt(TreeNode* root) {
        vector<int> ans;
        dfsRightFirst(root, 0, ans);
        return ans;
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int n=q.size();
            for(int i=0; i<n; i++) {
                auto p=q.front(); q.pop();
                if(i == n-1) ans.push_back(p->val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,null,5,null,4]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,null,null,null,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,3]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

