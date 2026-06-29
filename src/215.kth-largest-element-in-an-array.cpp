/*
 * @lc app=leetcode.cn id=215 lang=cpp
 * @lcpr version=30204
 *
 * [215] 数组中的第K个最大元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findKthLargestOpt(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int num : nums) {
            heap.push(num);
            // 始终只保留当前最大的 k 个数，堆顶就是第 k 大。
            if (heap.size() > k) {
                heap.pop();
            }
        }

        return heap.top();
    }

public:
    int partition(vector<int>& nums, int l, int r) {
        int randomIndex = l + rand() % (r - l + 1);
        swap(nums[randomIndex], nums[r]);
        int pivot = nums[r];
        int i=l;
        for(int j=l; j<r; j++) {
            if(nums[j] <= pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[r]);
        return i;
    }

    int s1(vector<int>& nums, int k) {
        srand(time(nullptr));
        int n=nums.size();
        int target = n-k;
        int l=0, r=n-1;
        while(l<=r) {
            int p=partition(nums, l, r);
            if(p == target) {
                return nums[p];
            } else if(p<target) {
                l = p+1;
            } else {
                r = p-1;
            }
        }
        return -1; 
    }

    int s2(vector<int>& nums, int k){
        int n=nums.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i=0; i<n; i++) {
            int num=nums[i];
            pq.push(num);
            if(pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }


    int findKthLargest(vector<int>& nums, int k) {
        // return s1(nums, k);
        return s2(nums, k);
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 4\n
// @lcpr case=end

 */

