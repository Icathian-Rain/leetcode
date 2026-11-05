/*
 * @lc app=leetcode.cn id=1438 lang=cpp
 * @lcpr version=30204
 *
 * [1438] 绝对差不超过限制的最长连续子数组
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int longestSubarrayOpt(vector<int>& nums, int limit) {
        deque<int> minIndexes, maxIndexes;
        int left = 0, best = 0;
        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            // 保存下标时，同值只保留更晚过期的候选即可。
            while (!maxIndexes.empty() && nums[maxIndexes.back()] <= nums[right]) {
                maxIndexes.pop_back();
            }
            maxIndexes.push_back(right);
            while (!minIndexes.empty() && nums[minIndexes.back()] >= nums[right]) {
                minIndexes.pop_back();
            }
            minIndexes.push_back(right);
            // 窗口中任意两数的最大绝对差就是 max - min。
            while (static_cast<long long>(nums[maxIndexes.front()])
                   - nums[minIndexes.front()] > limit) {
                ++left;
                if (maxIndexes.front() < left) maxIndexes.pop_front();
                if (minIndexes.front() < left) minIndexes.pop_front();
            }
            best = max(best, right - left + 1);
        }
        return best;
    }

public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n=nums.size();
        int ans = 0;
        // minq: 单调递增队列,队首存储最小值下标
        // maxq: 单调递减队列,队首是存储最大值下标
        deque<int> minq, maxq;
        for(int l=0, r=0; r<n; r++) {
            while(!maxq.empty() && nums[maxq.back()] < nums[r]) {
                maxq.pop_back();
            }
            maxq.push_back(r);
            while(!minq.empty() && nums[minq.back()] > nums[r]) {
                minq.pop_back();
            }
            minq.push_back(r);
            while(nums[maxq.front()] - nums[minq.front()] > limit) {
                if(maxq.front() == l) maxq.pop_front();
                if(minq.front() == l) minq.pop_front();
                l++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [8,2,4,7]\n4\n
// @lcpr case=end

// @lcpr case=start
// [10,1,2,4,7,2]\n5\n
// @lcpr case=end

// @lcpr case=start
// [4,2,2,2,4,4,2,2]\n0\n
// @lcpr case=end

 */
