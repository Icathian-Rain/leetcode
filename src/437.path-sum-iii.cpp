/*
 * @lc app=leetcode.cn id=437 lang=cpp
 * @lcpr version=30204
 *
 * [437] 路径总和 III
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
using ll = long long;
class Solution {
    unordered_map<ll, int> cnt;
    int ans = 0;
    int pathSumOpt(TreeNode* root, int targetSum) {
        unordered_map<ll, int> prefixCount;
        prefixCount[0] = 1;

        function<int(TreeNode*, ll)> dfsOpt = [&](TreeNode* node, ll prefix) {
            if (node == nullptr) {
                return 0;
            }

            prefix += node->val;
            // 以当前节点结尾的合法路径数量，等于此前出现过的目标前缀数量。
            int paths = prefixCount[prefix - targetSum];
            ++prefixCount[prefix];
            paths += dfsOpt(node->left, prefix);
            paths += dfsOpt(node->right, prefix);
            --prefixCount[prefix]; // 回溯，避免兄弟子树误用当前路径状态。
            return paths;
        };

        return dfsOpt(root, 0);
    }

    void dfs(TreeNode* root, int targetSum, ll sum) {
        if(root == nullptr) return ;
        sum += root->val;
        cout << sum << endl;
        if(cnt.find(sum - targetSum) != cnt.end()) {
            ans += cnt[sum-targetSum];
        }
        cnt[sum] += 1;
        dfs(root->left, targetSum, sum);
        dfs(root->right, targetSum, sum);
        cnt[sum] -= 1;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        cnt[0] = 1;
        dfs(root, targetSum, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,5,-3,3,2,null,11,3,-2,null,1]\n0\n
// @lcpr case=end

// @lcpr case=start
// [5,4,8,11,null,13,4,7,2,null,null,5,1]\n22\n
// @lcpr case=end

// @lcpr case=start
[1000000000,1000000000,null,294967296,null,1000000000,null,1000000000,null,1000000000]\n0
// @lcpr case=end
 */

