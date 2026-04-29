/*
 * @lc app=leetcode.cn id=523 lang=cpp
 * @lcpr version=30204
 *
 * [523] 连续的子数组和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n=nums.size();
        if(n<2) return false;
        unordered_map<int, int> pos;
        int sum=0;
        pos[0] = -1;
        for(int i=0; i<n; i++) {
            sum += nums[i];
            int mod = sum%k;
            if(pos.find(mod) != pos.end()) {
                if(i-pos[mod]>=2) {
                    return true;
                }
            } else {
                pos[mod]=i;
            }
            
        }
        return false;
    
    }
};
// @lc code=end



/*
// @lcpr case=start
// [23,2,4,6,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n6\n
// @lcpr case=end

// @lcpr case=start
// [23,2,6,4,7]\n13\n
// @lcpr case=end

// @lcpr case=start
// [5,0,0,0]\n3
// @lcpr case=end
 */

