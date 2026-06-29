/*
 * @lc app=leetcode.cn id=703 lang=cpp
 * @lcpr version=30204
 *
 * [703] 数据流中的第 K 大元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class KthLargest {
public:
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(auto num: nums) {
            pq.push(num);
        }
        while(pq.size() > k) {
            pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        while(pq.size() > k) {
            pq.pop();
        }
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
// @lc code=end



/*
// @lcpr case=start
// ["KthLargest", "add", "add", "add", "add", "add"][[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]\n
// @lcpr case=end

// @lcpr case=start
// ["KthLargest", "add", "add", "add", "add"][[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]\n
// @lcpr case=end

 */

