/*
 * @lc app=leetcode.cn id=560 lang=cpp
 * @lcpr version=30204
 *
 * [560] 和为 K 的子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n=nums.size();
        unordered_map<int, int> cnt;
        int ans=0;
        int sum=0;
        cnt[sum]++;
        for(int i=0; i<n; i++) {
            sum += nums[i];
            int target = sum-k;
            if(cnt.find(target) != cnt.end()) {
                ans += cnt[target];
            }
            cnt[sum]++;
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n3\n
// @lcpr case=end

 */

