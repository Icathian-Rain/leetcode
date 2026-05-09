/*
 * @lc app=leetcode.cn id=155 lang=cpp
 * @lcpr version=30204
 *
 * [155] 最小栈
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class MinStack {
    stack<int> st;
    stack<int> minEle;
public:
    MinStack() {
        minEle.push(INT_MAX);
    }
    
    void push(int val) {
        st.push(val);
        minEle.push(min(minEle.top(), val));

    }
    
    void pop() {
        st.pop();
        minEle.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minEle.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MinStack","push","push","push","getMin","pop","top","getMin"][[],[-2],[0],[-3],[],[],[],[]]\n
// @lcpr case=end

 */

