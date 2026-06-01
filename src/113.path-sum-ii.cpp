/*
 * @lc app=leetcode.cn id=113 lang=cpp
 * @lcpr version=30204
 *
 * [113] 路径总和 II
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
    void dfsOpt(TreeNode* root, int target, vector<int>& path, vector<vector<int>>& ans) {
        if (root == nullptr) {
            return;
        }

        path.push_back(root->val);
        target -= root->val;
        // 到叶子时才结算一条完整路径，不能在中间节点提前加入答案。
        if (root->left == nullptr && root->right == nullptr && target == 0) {
            ans.push_back(path);
        } else {
            dfsOpt(root->left, target, path, ans);
            dfsOpt(root->right, target, path, ans);
        }
        path.pop_back();
    }

    vector<vector<int>> pathSumOpt(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        dfsOpt(root, targetSum, path, ans);
        return ans;
    }

    vector<vector<int>> ans;
    vector<int> path;
    void dfs(TreeNode* root, int target) {
        if(root == nullptr) return ;
        path.push_back(root->val);
        target -= root->val;
        if(root->left == nullptr && root->right == nullptr) {
            if(target == 0) {
                ans.push_back(path);
            }
        } else {
            dfs(root->left, target);
            dfs(root->right, target);
        }
        target += root->val;
        path.pop_back();
        return ;
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,4,8,11,null,13,4,7,2,null,null,5,1]\n22\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n5\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n0\n
// @lcpr case=end

 */

