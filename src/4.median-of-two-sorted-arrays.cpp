/*
 * @lc app=leetcode.cn id=4 lang=cpp
 * @lcpr version=30204
 *
 * [4] 寻找两个正序数组的中位数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int getKth(vector<int>& nums1, int index1, vector<int>& nums2, int index2, int k) {
        if (index1 == nums1.size()) {
            return nums2[index2 + k - 1];
        }
        if (index2 == nums2.size()) {
            return nums1[index1 + k - 1];
        }
        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        int half = k / 2;
        int newIndex1 = min(index1 + half, static_cast<int>(nums1.size())) - 1;
        int newIndex2 = min(index2 + half, static_cast<int>(nums2.size())) - 1;

        if (nums1[newIndex1] <= nums2[newIndex2]) {
            // nums1 的这段元素不可能包含第 k 小，整体排除。
            return getKth(nums1, newIndex1 + 1, nums2, index2, k - (newIndex1 - index1 + 1));
        }

        return getKth(nums1, index1, nums2, newIndex2 + 1, k - (newIndex2 - index2 + 1));
    }

    double findMedianSortedArraysOpt(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        int leftMedian = getKth(nums1, 0, nums2, 0, (total + 1) / 2);
        int rightMedian = getKth(nums1, 0, nums2, 0, (total + 2) / 2);
        return (leftMedian + rightMedian) / 2.0;
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return findMedianSortedArraysOpt(nums1, nums2);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3]\n[2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n[3,4]\n
// @lcpr case=end

 */

