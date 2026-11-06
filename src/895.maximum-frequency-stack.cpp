/*
 * @lc app=leetcode.cn id=895 lang=cpp
 * @lcpr version=30204
 *
 * [895] 最大频率栈
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class FreqStack {
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxFreq;

    void pushOpt(int val) {
        int currentFreq = ++freq[val];
        // 保存到达该频次的事件；同层栈顶就是最近到达者。
        group[currentFreq].push(val);
        maxFreq = max(maxFreq, currentFreq);
    }

    int popOpt() {
        auto it = group.find(maxFreq);
        int val = it->second.top();
        it->second.pop();
        if (--freq[val] == 0) {
            freq.erase(val);
        }
        // 低一层的记录已在更早的 push 中保留，不需要重新入栈。
        if (it->second.empty()) {
            group.erase(it);
            --maxFreq;
        }
        return val;
    }

public:
    FreqStack(): maxFreq(0) {
        
    }
    
    void push(int val) {
        freq[val]++;
        group[freq[val]].push(val);
        maxFreq = max(maxFreq, freq[val]);
    }
    
    int pop() {
        int val = group[maxFreq].top();
        freq[val]--;
        group[maxFreq].pop();
        if(group[maxFreq].empty()) {
            maxFreq--;
        }
        return val;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
// @lc code=end



/*
// @lcpr case=start
// ["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]\n
// @lcpr case=end

 */

