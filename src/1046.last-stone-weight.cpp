/*
 * @lc app=leetcode.cn id=1046 lang=cpp
 * @lcpr version=30204
 *
 * [1046] 最后一块石头的重量
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int lastStoneWeightOpt(vector<int>& stones) {
        priority_queue<int> heap;
        for (int stone : stones) {
            heap.push(stone);
        }

        while (heap.size() > 1) {
            int first = heap.top();
            heap.pop();
            int second = heap.top();
            heap.pop();
            // 两块重量不同才会产生新的候选石头。
            if (first != second) {
                heap.push(first - second);
            }
        }

        return heap.empty() ? 0 : heap.top();
    }

public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int, vector<int>, less<int>> pq;
        for(auto stone: stones) {
            pq.push(stone);
        }

        while(pq.size() >= 2) {
            int y = pq.top(); pq.pop();
            int x = pq.top(); pq.pop();
            // cout << y << " " << x << endl;
            if(x == y) {
                continue;
            } else {
                pq.push(y-x);
            }
        }
        return pq.size() == 0 ? 0 : pq.top();
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,7,4,1,8,1]\n
// @lcpr case=end

 */

