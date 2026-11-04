/*
 * @lc app=leetcode.cn id=295 lang=cpp
 * @lcpr version=30204
 *
 * [295] 数据流的中位数
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class MedianFinder {
    // 小顶堆, 存大于mid的数
    priority_queue<int, vector<int>, greater<int>> high;

    // 大顶堆, 存小于mid的数
    priority_queue<int, vector<int>, less<int>> low;

    void addNumOpt(int num) {
        // low 保存较小的一半；跨堆搬运保证 low 中的数不大于 high。
        low.push(num);
        high.push(low.top());
        low.pop();
        if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedianOpt() {
        // low 的大小等于 high 或多一个；加法前转浮点数。
        if (low.size() > high.size()) return low.top();
        return (static_cast<double>(low.top()) + high.top()) / 2.0;
    }
public:
    MedianFinder(){

    }

    void addNum(int num) {
        low.push(num);
        high.push(low.top());
        low.pop();
        if(high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        if(low.size() > high.size()) {
            return low.top();
        } else {
            return (1.0*low.top()+high.top())/2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
// @lc code=end
