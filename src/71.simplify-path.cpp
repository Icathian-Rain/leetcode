/*
 * @lc app=leetcode.cn id=71 lang=cpp
 * @lcpr version=30204
 *
 * [71] 简化路径
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start

class Solution {
    string simplifyPathOpt(string path) {
        vector<string> parts;
        string segment;

        for(int i = 0; i <= (int)path.size(); i++) {
            if(i == (int)path.size() || path[i] == '/') {
                if(segment == "..") {
                    if(!parts.empty()) {
                        parts.pop_back();
                    }
                } else if(!segment.empty() && segment != ".") {
                    // 普通目录名保留，"..." 也是合法目录名。
                    parts.push_back(segment);
                }
                segment.clear();
            } else {
                segment.push_back(path[i]);
            }
        }

        if(parts.empty()) {
            return "/";
        }

        string ans;
        for(const string& part: parts) {
            ans += "/" + part;
        }
        return ans;
    }

public:
    string simplifyPath(string path) {
        vector<string> ansPath;
        vector<string> fullPath;
        string tmp="";

        for(auto ch: path) {
            if(ch == '/') {
                if(tmp != "") {
                    fullPath.push_back(tmp);
                    tmp = "";
                }
            } else {
                tmp.push_back(ch);
            }
        }

        if(tmp != "") fullPath.push_back(tmp);


        for(auto p: fullPath) {
            // cout << p << "->";
            if(p == "..") {
                if(!ansPath.empty()) {
                    ansPath.pop_back();
                }
            } else if(p == ".") {
                continue;
            } else {
                ansPath.push_back(p);
            }
        }
        // cout << endl;
        string ans = "";
        for(auto p: ansPath) {
            ans.push_back('/');
            ans+=p;
        }

        return ans == "" ? "/": ans;




    }
};
// @lc code=end



/*
// @lcpr case=start
// "/home/"\n
// @lcpr case=end

// @lcpr case=start
// "/home//foo/"\n
// @lcpr case=end

// @lcpr case=start
// "/home/user/Documents/../Pictures"\n
// @lcpr case=end

// @lcpr case=start
// "/../"\n
// @lcpr case=end

// @lcpr case=start
// "/.../a/../b/c/../d/./"\n
// @lcpr case=end

 */

