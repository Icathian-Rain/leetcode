/*
 * @lc app=leetcode.cn id=1 lang=cpp
 * @lcpr version=30204
 *
 * [1] 两数之和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    // 暴力法，时间复杂度O(n2)
    vector<int> s1(vector<int>& nums, int target) {
        int n=nums.size();
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                if(nums[i]+nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }

    // 哈希表，时间复杂度O(n)
    vector<int> s2(vector<int>& nums, int target) {
        int n=nums.size();
        unordered_map<int, int> mp;
        for(int i=0; i<n; i++) {
            if(mp.find(nums[i]) != mp.end()) {
                return {mp[nums[i]], i};
            }
            mp[target-nums[i]] = i;
        }
        return {};
    }

public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // return s1(nums, target);
        return s2(nums, target);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,7,11,15]\n9\n
// @lcpr case=end

// @lcpr case=start
// [3,2,4]\n6\n
// @lcpr case=end

// @lcpr case=start
// [3,3]\n6\n
// @lcpr case=end

 */

