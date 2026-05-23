/*
 * @lc app=leetcode.cn id=658 lang=cpp
 * @lcpr version=30204
 *
 * [658] 找到 K 个最接近的元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> findClosestElementsOpt(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - k;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (x - arr[middle] > arr[middle + k] - x) {
                left = middle + 1; // 左端太远，答案窗口应整体右移。
            } else {
                right = middle; // 当前窗口仍可能是最靠左的最优窗口。
            }
        }

        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }

public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n=arr.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(arr[m] >= x) {
                r = m;
            } else {
                l = m+1;
            }
        }
        // arr[l] 为第一个大于等于x的数
        int left, right;
        left=l-1, right=l;
        for(int i=0; i<k; i++) {
            if(left >= 0 && right < n) {
                if(x-arr[left] <= arr[right]-x) {
                    left--;
                } else {
                    right++;
                }
            } else if(left < 0) {
                right++;
            } else {
                left--;
            }
        }
        vector<int> ans;
        for(int i=left+1; i<right; i++) {
            ans.push_back(arr[i]);
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n4\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2,3,4,5]\n4\n-1\n
// @lcpr case=end

 */

