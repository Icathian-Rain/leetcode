/*
 * @lc app=leetcode.cn id=381 lang=cpp
 * @lcpr version=30204
 *
 * [381] O(1) 时间插入、删除和获取随机元素 - 允许重复
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class RandomizedCollection {
    vector<int> arr;
    unordered_map<int, unordered_set<int>> mp;
public:
    RandomizedCollection() {

    }

    bool insert(int val) {
        arr.push_back(val);
        mp[val].insert(arr.size()-1);
        return mp[val].size() == 1;
    }

    bool remove(int val) {
        if(mp.find(val) == mp.end()) {
            return false;
        }
        // 要删除的位置
        int idx = *(mp[val].begin());
        int lastIdx = arr.size()-1;
        int lastVal = arr[lastIdx];
        mp[val].erase(idx);

        // 如果要删除的位置不是最后一个
        if(idx != lastIdx) {
            // 需要交换位置
            arr[idx] = lastVal;
            mp[lastVal].erase(lastIdx);
            mp[lastVal].insert(idx);
        }

        arr.pop_back();

        if(mp[val].size() == 0) {
            mp.erase(val);
        }
        return true;
    }

    int getRandom() {
        return arr[rand()%arr.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
// @lc code=end
