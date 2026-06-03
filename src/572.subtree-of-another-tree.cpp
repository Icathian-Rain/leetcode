/*
 * @lc app=leetcode.cn id=572 lang=cpp
 * @lcpr version=30204
 *
 * [572] 另一棵树的子树
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
    bool isSubtreeOpt(TreeNode* root, TreeNode* subRoot) {
        vector<int> source;
        vector<int> pattern;
        serialize(root, source);
        serialize(subRoot, pattern);
        return kmpContains(source, pattern);
    }

    void serialize(TreeNode* root, vector<int>& values) {
        if (root == nullptr) {
            values.push_back(INT_MIN);
            return;
        }

        // 同时记录空孩子，避免不同结构得到相同遍历序列。
        values.push_back(root->val);
        serialize(root->left, values);
        serialize(root->right, values);
    }

    bool kmpContains(const vector<int>& source, const vector<int>& pattern) {
        vector<int> lps(pattern.size(), 0);
        for (int i = 1, len = 0; i < static_cast<int>(pattern.size());) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                ++i;
            }
        }

        for (int i = 0, j = 0; i < static_cast<int>(source.size()); ++i) {
            while (j > 0 && source[i] != pattern[j]) {
                j = lps[j - 1];
            }
            if (source[i] == pattern[j]) {
                ++j;
            }
            if (j == static_cast<int>(pattern.size())) {
                return true;
            }
        }
        return false;
    }

public:
    bool isSame(TreeNode* root, TreeNode* subRoot) {
        if(root == nullptr && subRoot == nullptr) return true;
        if(root == nullptr || subRoot == nullptr) return false;
        if(root->val != subRoot->val) return false;
        return isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
    }



    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(isSame(root, subRoot) == true) return true;
        if(root == nullptr && subRoot != nullptr) return false;
        return isSubtree(root->left, subRoot) | isSubtree(root->right, subRoot);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,4,5,1,2]\n[4,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,4,5,1,2,null,null,null,null,0]\n[4,1,2]\n
// @lcpr case=end

 */

