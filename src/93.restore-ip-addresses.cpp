/*
 * @lc app=leetcode.cn id=93 lang=cpp
 * @lcpr version=30204
 *
 * [93] 复原 IP 地址
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<string> restoreIpAddressesOpt(string s) {
        vector<string> result;
        vector<string> segments;

        function<void(int)> dfs = [&](int start) {
            int used = static_cast<int>(segments.size());
            int remainChars = static_cast<int>(s.size()) - start;
            int remainSegments = 4 - used;
            if (remainChars < remainSegments || remainChars > remainSegments * 3) {
                return; // 剩余字符数量无法填满剩余段数。
            }

            if (used == 4) {
                if (start == static_cast<int>(s.size())) {
                    result.push_back(segments[0] + "." + segments[1] + "." +
                                     segments[2] + "." + segments[3]);
                }
                return;
            }

            int value = 0;
            for (int end = start; end < static_cast<int>(s.size()) && end < start + 3; ++end) {
                value = value * 10 + (s[end] - '0');
                if (value > 255) {
                    break;
                }
                if (end > start && s[start] == '0') {
                    break; // 多位段不能以 0 开头。
                }
                segments.push_back(s.substr(start, end - start + 1));
                dfs(end + 1);
                segments.pop_back();
            }
        };

        dfs(0);
        return result;
    }

public:
    vector<string> ans;
    vector<int> path;
    string tostr() {
        string res = "";
        for(int i=0; i<4; i++) {
            res += to_string(path[i]);
            if(i != 3) {
                res += ".";
            }
        }
        return res;
    }


    void dfs(string& s, int start) {
        if(start == s.length() || path.size() == 4) {
            if(start == s.length() && path.size() == 4) {
                ans.push_back(tostr());
            }
            return ;
        }
        if(s[start] == '0') {
            path.push_back(0);
            dfs(s, start+1);
            path.pop_back();
            return ;
        }
        int tmp = 0;
        for(int i=start; i<s.length(); i++) {
            tmp = tmp*10+(s[i]-'0');
            if(tmp >= 0 && tmp <= 255) {
                path.push_back(tmp);
                dfs(s, i+1);
                path.pop_back();
            } else {
                break;
            }
        }
    }





    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "25525511135"\n
// @lcpr case=end

// @lcpr case=start
// "0000"\n
// @lcpr case=end

// @lcpr case=start
// "101023"\n
// @lcpr case=end

 */

