/*
 * @lc app=leetcode.cn id=480 lang=cpp
 * @lcpr version=30204
 *
 * [480] 滑动窗口中位数
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<double> medianSlidingWindowOpt(vector<int>& nums, int k) {
        multiset<int> left, right;
        vector<double> result;
        result.reserve(nums.size() - k + 1);
        auto balance = [&]() {
            // 左侧保存较小的 ceil(当前元素数 / 2) 个元素。
            while (left.size() > right.size() + 1) {
                auto it = prev(left.end());
                right.insert(*it);
                left.erase(it);
            }
            while (left.size() < right.size()) {
                auto it = right.begin();
                left.insert(*it);
                right.erase(it);
            }
        };
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (left.empty() || nums[i] <= *left.rbegin()) left.insert(nums[i]);
            else right.insert(nums[i]);
            balance();
            if (i >= k) {
                // 重复值只删一个副本，两侧同值可任选一侧删除后再平衡。
                auto it = left.find(nums[i - k]);
                if (it != left.end()) left.erase(it);
                else right.erase(right.find(nums[i - k]));
                balance();
            }
            if (i >= k - 1) {
                if (k % 2) result.push_back(*left.rbegin());
                else result.push_back((static_cast<double>(*left.rbegin())
                                       + *right.begin()) / 2.0);
            }
        }
        return result;
    }

    vector<double> s1(vector<int>& nums, int k) {
        multiset<int> left, right;
        vector<double> ans;
        auto balance = [&]() {
            while(left.size() > right.size()+1) {
                auto it = prev(left.end());
                right.insert(*it);
                left.erase(it);
            }
            while(left.size() < right.size()) {
                auto it = right.begin();
                left.insert(*it);
                right.erase(it);
            }
        };
        auto add = [&](int x) {
            if(left.empty() || x <= *left.rbegin()) {
                left.insert(x);
            } else {
                right.insert(x);
            }
            balance();
        };
        auto remove = [&](int x) {
            auto it = left.find(x);
            if(it != left.end()) {
                left.erase(it);
            } else {
                right.erase(right.find(x));
            }
            balance();
        };
        int n=nums.size();
        for(int i=0; i<n; i++) {
            int x = nums[i];
            add(x);
            if(i >= k) {
                remove(nums[i-k]);
            }
            if(i >= k-1) {
                if(k%2) ans.push_back(*left.rbegin());
                else ans.push_back(((double)*left.rbegin() + *right.begin())/2.0);
            }
        }
        return ans;

    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        return s1(nums, k);
    }
};
// @lc code=end
