/*
 * @lc app=leetcode.cn id=454 lang=cpp
 * @lcpr version=30204
 *
 * [454] 四数相加 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> cnt;
        for(auto num1: nums1) {
            for(auto num2: nums2) {
                cnt[num1+num2] ++;
            }
        }

        int ans=0;
        for(auto num3: nums3) {
            for(auto num4: nums4) {
                int target = 0-num3-num4;
                if(cnt.find(target) != cnt.end()) {
                    ans+=cnt[target];
                }
            }
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2]\n[-2,-1]\n[-1,2]\n[0,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n[0]\n[0]\n[0]\n
// @lcpr case=end

 */
