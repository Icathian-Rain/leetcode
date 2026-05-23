/*
 * @lc app=leetcode.cn id=981 lang=cpp
 * @lcpr version=30204
 *
 * [981] 基于时间的键值存储
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pis=pair<int, string>;
class TimeMap {
    string getOpt(const string& key, int timestamp) {
        auto it = mp.find(key);
        if (it == mp.end()) {
            return "";
        }

        const vector<pis>& records = it->second;
        auto pos = upper_bound(
            records.begin(),
            records.end(),
            timestamp,
            [](int time, const pis& record) {
                return time < record.first;
            }
        );

        if (pos == records.begin()) {
            return "";
        }
        --pos; // upper_bound 找到第一个大于 timestamp 的版本，前一个才是可用版本。
        return pos->second;
    }

public:
    unordered_map<string, vector<pis>> mp;
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if(mp.find(key) == mp.end()) {
            return "";
        }
        vector<pis>& arr=mp[key];
        int n=arr.size();
        int l=0, r=n;
        while(l<r) {
            // 寻找最后一个ts <= new ts
            // 寻找第一个ts > new ts，然后序号-1
            int m=l+(r-l)/2;
            if(arr[m].first > timestamp) {
                r=m;
            } else {
                l=m+1;
            }
        }
        
        return l==0? "" : arr[l-1].second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
// @lc code=end



/*
// @lcpr case=start
// ["TimeMap", "set", "get", "get", "set", "get", "get"][[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]\n
// @lcpr case=end

 */

