/*
 * @lc app=leetcode.cn id=992 lang=cpp
 * @lcpr version=30204
 *
 * [992] K 个不同整数的子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int subarraysWithKDistinctOpt(vector<int>& nums, int k) {
        auto atMost = [&](int limit) -> int {
            if(limit < 0) {
                return 0;
            }

            unordered_map<int, int> count;
            int left = 0;
            int ans = 0;

            for(int right = 0; right < (int)nums.size(); right++) {
                count[nums[right]]++;

                while((int)count.size() > limit) {
                    count[nums[left]]--;
                    if(count[nums[left]] == 0) {
                        count.erase(nums[left]);
                    }
                    left++;
                }

                // 以 right 结尾、起点在 [left, right] 的子数组都满足最多 limit 种。
                ans += right - left + 1;
            }

            return ans;
        };

        return atMost(k) - atMost(k - 1);
    }

public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int n=nums.size();

        auto f=[&](int target)->int {
            unordered_map<int, int> cnt;
            int ans=0;
            for(int l=0, r=0; r<n; r++) {
                cnt[nums[r]]++;
                while(l<=r && cnt.size() >= target) {
                    cnt[nums[l]]--;
                    if(cnt[nums[l]] == 0) {
                        cnt.erase(nums[l]);
                    }
                    l++;
                }

                ans+=l;
            }
            return ans;
        };

        return f(k)-f(k+1);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,1,2,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,3,4]\n3\n
// @lcpr case=end

 */

