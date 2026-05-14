/*
 * @lc app=leetcode.cn id=239 lang=cpp
 * @lcpr version=30204
 *
 * [239] 滑动窗口最大值
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> maxSlidingWindowOpt(vector<int>& nums, int k) {
        deque<int> indexes;
        vector<int> ans;

        for(int i = 0; i < (int)nums.size(); i++) {
            while(!indexes.empty() && indexes.front() <= i - k) {
                indexes.pop_front();
            }
            while(!indexes.empty() && nums[indexes.back()] <= nums[i]) {
                indexes.pop_back();
            }
            indexes.push_back(i);

            if(i >= k - 1) {
                // 队首下标始终对应当前窗口最大值。
                ans.push_back(nums[indexes.front()]);
            }
        }

        return ans;
    }

public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        class MyQueue {
            private:
                deque<int> q;
            public:
                void push(int val) {
                    // 将小于val的全部pop出来，插入val
                    while (!q.empty() && q.back() < val)
                    {
                        q.pop_back();
                    }
                    q.push_back(val);
                }
                void pop(int val) {
                    // 若目前最大值为val, 则pop出来
                    if(q.front() == val) {
                        q.pop_front();
                    }
                }
                int front() {
                    // front为最大值
                    return q.front();
                }
        };
        
        MyQueue q;
        vector<int> ans;
        for(int i=0;i<k;i++) {
            q.push(nums[i]);
        }
        ans.push_back(q.front());
        for(int i=k; i<nums.size(); i++) {
            q.push(nums[i]);
            q.pop(nums[i-k]);
            ans.push_back(q.front());
        }
        return ans;
        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3,-1,-3,5,3,6,7]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */

