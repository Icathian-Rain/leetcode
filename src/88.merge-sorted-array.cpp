/*
 * @lc app=leetcode.cn id=88 lang=cpp
 * @lcpr version=30204
 *
 * [88] 合并两个有序数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    void mergeOpt(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;
        int p2 = n - 1;
        int write = m + n - 1;

        // 从后往前写，避免覆盖 nums1 前 m 个还没比较的元素。
        while (p2 >= 0) {
            if (p1 >= 0 && nums1[p1] > nums2[p2]) {
                nums1[write] = nums1[p1];
                --p1;
            } else {
                nums1[write] = nums2[p2];
                --p2;
            }
            --write;
        }
    }

public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int pos=m+n-1, p1=m-1, p2=n-1; pos>=0; pos--) {
            if(p1 < 0) {
                nums1[pos] = nums2[p2];
                p2--;
            } else if(p2 < 0) {
                nums1[pos] = nums1[p1];
                p1--;
            } else if(nums1[p1] > nums2[p2]) {
                nums1[pos] = nums1[p1];
                p1--;
            } else {
                nums1[pos] = nums2[p2];
                p2--;
            }
        }
        return ;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,0,0,0]\n3\n[2,5,6]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n[]\n0\n
// @lcpr case=end

// @lcpr case=start
// [0]\n0\n[1]\n1\n
// @lcpr case=end

 */

