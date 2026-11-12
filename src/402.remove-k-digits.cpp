/*
 * @lc app=leetcode.cn id=402 lang=cpp
 * @lcpr version=30204
 *
 * [402] 移掉 K 位数字
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    string removeKdigitsOpt(string num, int k) {
        string stk; // 栈内是当前前缀在配额内能成的最小数
        for (char c : num) {
            // 高位换小值优先：栈顶更大且还有配额才弹
            while (!stk.empty() && stk.back() > c && k > 0) {
                stk.pop_back();
                k--;
            }
            stk.push_back(c);
        }
        // 配额没用尽：剩余数字非降，从尾部删最大的若干位
        while (k > 0) {
            stk.pop_back();
            k--;
        }
        // 去前导零
        size_t firstNonZero = stk.find_first_not_of('0');
        if (firstNonZero == string::npos) return "0"; // 全零或删空
        return stk.substr(firstNonZero);
    }

public:
    string removeKdigits(string num, int k) {
        string ans;
        for(auto c: num) {
            while(!ans.empty() && ans.back() > c && k>0) {
                ans.pop_back();
                k--;
            }
            ans.push_back(c);
        }
        while(k > 0) {
            ans.pop_back();
            k--;
        }
        int i=0;
        while(i < ans.size() && ans[i] == '0') i++;
        ans = ans.substr(i);
        return ans.empty() ? "0": ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "1432219"\n3\n
// @lcpr case=end

// @lcpr case=start
// "10200"\n1\n
// @lcpr case=end

// @lcpr case=start
// "10"\n2\n
// @lcpr case=end

 */

