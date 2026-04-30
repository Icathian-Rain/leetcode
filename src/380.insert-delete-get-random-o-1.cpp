/*
 * @lc app=leetcode.cn id=380 lang=cpp
 * @lcpr version=30204
 *
 * [380] O(1) 时间插入、删除和获取随机元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class RandomizedSet {
    vector<int> arr;
    unordered_map<int, int> mp;
public:
    RandomizedSet() {

    }

    bool insert(int val) {
        if(mp.find(val) != mp.end()) {
            return false;
        }
        int len=arr.size();
        arr.push_back(val);
        mp[val] = len;
        return true;
    }

    bool remove(int val) {
        if(mp.find(val) == mp.end()) {
            return false;
        }
        int len=arr.size();
        int idx = mp[val];
        swap(arr[idx], arr[len-1]);
        mp[arr[idx]] = idx;

        arr.pop_back();
        mp.erase(val);
        return true;
    }

    int getRandom() {
        int len=arr.size();
        return arr[rand()%len];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
// @lc code=end
