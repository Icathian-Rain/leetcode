/*
 * @lc app=leetcode.cn id=1825 lang=cpp
 * @lcpr version=30204
 *
 * [1825] 求出 MK 平均值
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using ll = long long;
class MKAverage {
    // low: 最小的k个数
    // mid: 中间m-2*k个数
    // high: 最大的k个数
    multiset<int> low, mid, high;
    ll sum;
    queue<int> q;
    int m, k;

    void addElementOpt(int num) {
        q.push(num);
        if (!low.empty() && num <= *low.rbegin()) low.insert(num);
        else if (!high.empty() && num >= *high.begin()) high.insert(num);
        else {
            mid.insert(num);
            sum += num;
        }
        if (q.size() > static_cast<size_t>(m)) {
            int old = q.front();
            q.pop();
            auto it = low.find(old);
            if (it != low.end()) low.erase(it);
            else if (auto highIt = high.find(old); highIt != high.end()) {
                high.erase(highIt);
            } else {
                mid.erase(mid.find(old));
                sum -= old;
            }
        }
        // 预热期也逐次分段，避免首次凑满 m 个时集中搬移 2k 个数。
        size_t lowTarget = min(static_cast<size_t>(k), q.size());
        size_t highTarget = min(static_cast<size_t>(k), q.size() - lowTarget);
        // 先把两侧多余元素送入 mid，再补足两侧，保证补位时有候选。
        while (low.size() > lowTarget) {
            auto it = prev(low.end());
            int value = *it;
            low.erase(it);
            mid.insert(value);
            sum += value;
        }
        while (high.size() > highTarget) {
            auto it = high.begin();
            int value = *it;
            high.erase(it);
            mid.insert(value);
            sum += value;
        }
        while (low.size() < lowTarget) {
            auto it = mid.begin();
            int value = *it;
            mid.erase(it);
            sum -= value;
            low.insert(value);
        }
        while (high.size() < highTarget) {
            auto it = prev(mid.end());
            int value = *it;
            mid.erase(it);
            sum -= value;
            high.insert(value);
        }
    }

public:
    MKAverage(int m, int k): m(m), k(k), sum(0) {

    }

    void addElement(int num) {
        q.push(num);
        if(q.size()<=m) {
            mid.insert(num);
            sum += num;
            if(q.size() == m) {
                for(int i=0; i<k; i++) {
                    int x = *mid.begin();
                    mid.erase(mid.find(x));
                    sum -= x;
                    low.insert(x);
                }
                for(int i=0; i<k; i++) {
                    int x = *mid.rbegin();
                    mid.erase(mid.find(x));
                    sum -= x;
                    high.insert(x);
                }
            }
            return ;
        }
        int old = q.front();
        q.pop();
        if(low.find(old) != low.end()) {
            low.erase(low.find(old));
        } else if(high.find(old) != high.end()) {
            high.erase(high.find(old));
        } else {
            mid.erase(mid.find(old));
            sum -= old;
        }

        if(!low.empty() && num <= *low.rbegin()) {
            low.insert(num);
        } else if(!high.empty() && num >= *high.begin()) {
            high.insert(num);
        } else {
            mid.insert(num);
            sum += num;
        }

        while(low.size() > k) {
            int x = *low.rbegin();
            low.erase(prev(low.end()));
            mid.insert(x);
            sum += x;
        }
        while(high.size() > k) {
            int x = *high.begin();
            high.erase(high.begin());
            mid.insert(x);
            sum += x;
        }
        while(low.size() < k) {
            int x = *mid.begin();
            mid.erase(mid.find(x));
            sum -= x;
            low.insert(x);
        }
        while(high.size() < k) {
            int x = *mid.rbegin();
            mid.erase(mid.find(x));
            sum -= x;
            high.insert(x);
        }
    }

    int calculateMKAverage() {
        if(q.size() < m) return -1;
        return sum / (m-2*k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
// @lc code=end



/*
// @lcpr case=start
// ["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement","addElement", "addElement", "calculateMKAverage"][[3, 1], [3], [1], [], [10], [], [5], [5], [5], []]\n
// @lcpr case=end

 */
