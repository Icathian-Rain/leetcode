/*
 * @lc app=leetcode.cn id=451 lang=cpp
 * @lcpr version=30204
 *
 * [451] 根据字符出现频率排序
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    string frequencySortOpt(string s) {
        vector<pii> counts;
        counts.reserve(128);
        for (int ch = 0; ch < 128; ++ch) {
            counts.push_back({0, ch});
        }
        for (unsigned char ch : s) {
            ++counts[ch].first;
        }
        // 字符集固定，只需排序 128 个计数项；同频字符顺序不限。
        sort(counts.begin(), counts.end(), greater<pii>());
        string result;
        result.reserve(s.size());
        for (const auto& [count, ch] : counts) {
            if (count > 0) {
                result.append(count, static_cast<char>(ch));
            }
        }
        return result;
    }

public:
    string frequencySort(string s) {
        vector<pii> cnt;
        for(int i=0; i<128; i++) {
            cnt.push_back({0, i});
        }
        for(auto ch: s) {
            cnt[ch].first++;
        }
        sort(cnt.begin(), cnt.end(), greater<pii>());
        string ans = "";
        for(auto [count, ch]: cnt) {
            if(count != 0)
            ans += string(count, ch);
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// "tree"\n
// @lcpr case=end

// @lcpr case=start
// "cccaaa"\n
// @lcpr case=end

// @lcpr case=start
// "Aabb"\n
// @lcpr case=end

 */

