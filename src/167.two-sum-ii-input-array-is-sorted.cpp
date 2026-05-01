/*
 * @lc app=leetcode.cn id=167 lang=cpp
 * @lcpr version=30204
 *
 * [167] 两数之和 II - 输入有序数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n=numbers.size();
        for(int i=0, j=n-1; i<j;) {
            if(numbers[i]+numbers[j] < target) {
                i++;
            } else if(numbers[i]+numbers[j] > target) {
                j--;
            } else {
                return {i+1, j+1};
            }
        }
        return {};
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,7,11,15]\n9\n
// @lcpr case=end

// @lcpr case=start
// [2,3,4]\n6\n
// @lcpr case=end

// @lcpr case=start
// [-1,0]\n-1\n
// @lcpr case=end

 */

