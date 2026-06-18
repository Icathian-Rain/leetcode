/*
 * @lc app=leetcode.cn id=698 lang=cpp
 * @lcpr version=30204
 *
 * [698] 划分为k个相等的子集
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool canPartitionKSubsetsOpt(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) {
            return false;
        }

        int target = total / k;
        sort(nums.begin(), nums.end(), greater<int>());
        if (!nums.empty() && nums[0] > target) {
            return false;
        }

        vector<int> buckets(k, 0);
        function<bool(int)> dfs = [&](int index) {
            if (index == static_cast<int>(nums.size())) {
                return true;
            }

            int value = nums[index];
            for (int bucket = 0; bucket < k; ++bucket) {
                if (buckets[bucket] + value > target) {
                    continue;
                }

                buckets[bucket] += value;
                if (dfs(index + 1)) {
                    return true;
                }
                buckets[bucket] -= value;

                if (buckets[bucket] == 0) {
                    break; // 空桶等价，当前空桶失败后无需尝试其他空桶。
                }
            }
            return false;
        };

        return dfs(0);
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum=0;
        for(auto num: nums) {
            sum += num;
        }
        if(sum%k != 0) return false;
        int target = sum/k;
        sort(nums.begin(), nums.end(), greater<int>());
        vector<int> bucket(k, 0);
        if(nums[0] > target) {
            return false;
        }

        function<bool(int)> dfs = [&](int idx) -> bool {
            if(idx == nums.size()) {
                return true;
            }
            int x=nums[idx];
            for(int i=0; i<k; i++) {
                if(bucket[i]+x > target) {
                    continue;
                }
                bucket[i] += x;
                if(dfs(idx+1) == true) return true; 
                bucket[i] -= x;

                if(bucket[i] == 0) {
                    break;
                }
            }
            return false;
        };
        return dfs(0);


    }
};
// @lc code=end



/*
// @lcpr case=start
// [4, 3, 2, 3, 5, 2, 1]\n4\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4]\n3\n
// @lcpr case=end

 */

