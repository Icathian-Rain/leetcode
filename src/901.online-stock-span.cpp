/*
 * @lc app=leetcode.cn id=901 lang=cpp
 * @lcpr version=30204
 *
 * [901] 股票价格跨度
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class StockSpanner {
public:
    vector<int> stock;
    stack<int> st;
    stack<pair<int, int>> spansOpt;
    StockSpanner() {
        

    }

    int nextOpt(int price) {
        int span = 1;
        while(!spansOpt.empty() && spansOpt.top().first <= price) {
            // 被当前价格覆盖的连续天数可以直接合并。
            span += spansOpt.top().second;
            spansOpt.pop();
        }
        spansOpt.push({price, span});
        return span;
    }
    
    int next(int price) {
        int idx=stock.size();
        while(!st.empty() && price >= stock[st.top()]) {
            st.pop();
        }
        int ans = idx+1;
        if(!st.empty()) {
            ans = idx - st.top();
        }
        stock.push_back(price);
        st.push(idx);
        return ans;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
// @lc code=end



/*
// @lcpr case=start
// ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"][[], [100], [80], [60], [70], [60], [75], [85]]\n
// @lcpr case=end

// @lcpr case=start
// ["StockSpanner", "next", "next", "next", "next","next"][[],[31],[41],[48],[59],[79]]\n
// @lcpr case=end
 */

