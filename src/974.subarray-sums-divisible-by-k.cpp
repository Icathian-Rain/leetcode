/*
 * @lc app=leetcode.cn id=974 lang=cpp
 * @lcpr version=30204
 *
 * [974] 和可被 K 整除的子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n=nums.size();
        unordered_map<int, int> cnt;
        int ans=0;
        int sum=0;
        cnt[0] = 1;
        for(int i=0; i<n; i++) {
            sum += nums[i];
            // (sum - target) % k == 0;
            int modulus = (sum % k + k) % k;
            if(cnt.find(modulus) != cnt.end()) {
                ans+=cnt[modulus];
            }
            cnt[modulus]++;
        }
        return ans;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,5,0,-2,-3,1]\n5\n
// @lcpr case=end

// @lcpr case=start
// [5]\n9\n
// @lcpr case=end

 */

