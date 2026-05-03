/*
 * @lc app=leetcode.cn id=16 lang=cpp
 * @lcpr version=30204
 *
 * [16] 最接近的三数之和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int threeSumClosestOpt(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int best = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (abs(sum - target) < abs(best - target)) {
                    best = sum;
                }

                if (sum == target) {
                    return target;
                }
                // 和偏小时只能增大左侧候选，和偏大时只能减小右侧候选。
                if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return best;
    }

public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n=nums.size();
        int ans=1e7;
        sort(nums.begin(), nums.end());
        for(int i=0; i<n; i++) {
            if(i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j=i+1, k=n-1;
            while(j < k) {
                int sum=nums[i]+nums[j]+nums[k];
                if(sum == target) {
                    return target;
                } else if(sum < target) {
                    while(j<k && nums[j] == nums[j+1])j++;
                    j++;
                } else {
                    while(j<k && nums[k] == nums[k-1])k--;
                    k--;
                }
                if(abs(sum-target) < abs(ans-target)) {
                    ans=sum;
                }
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-1,2,1,-4]\n1\n
// @lcpr case=end

// @lcpr case=start
// [0,0,0]\n1\n
// @lcpr case=end

 */

