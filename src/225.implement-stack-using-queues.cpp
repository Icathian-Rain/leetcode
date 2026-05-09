/*
 * @lc app=leetcode.cn id=225 lang=cpp
 * @lcpr version=30204
 *
 * [225] 用队列实现栈
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class MyStack {
    queue<int> q;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        int n=q.size();
        q.push(x);
        for(int i=0; i<n; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int ret = q.front();
        q.pop();
        return ret;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MyStack", "push", "push", "top", "pop", "empty"][[], [1], [2], [], [], []]\n
// @lcpr case=end

 */

