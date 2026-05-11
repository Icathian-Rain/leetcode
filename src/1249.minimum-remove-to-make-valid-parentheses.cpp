/*
 * @lc app=leetcode.cn id=1249 lang=cpp
 * @lcpr version=30204
 *
 * [1249] 移除无效的括号
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    string minRemoveToMakeValidOpt(string s) {
        vector<int> openingIndexes;
        vector<bool> remove(s.size(), false);

        for(int i = 0; i < (int)s.size(); i++) {
            if(s[i] == '(') {
                openingIndexes.push_back(i);
            } else if(s[i] == ')') {
                if(openingIndexes.empty()) {
                    remove[i] = true;
                } else {
                    openingIndexes.pop_back();
                }
            }
        }

        // 剩余未匹配左括号都需要删除。
        for(int index: openingIndexes) {
            remove[index] = true;
        }

        string ans;
        for(int i = 0; i < (int)s.size(); i++) {
            if(!remove[i]) {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }

public:
    string minRemoveToMakeValid(string s) {
        int n=s.length();
        stack<int> st;
        unordered_set<int> idx;
        for(int i=0; i<n; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else if(s[i] == ')') {
                if(st.empty()) {
                    idx.insert(i);
                } else {
                    st.pop();
                }
            }
        }

        while(!st.empty()) {
            idx.insert(st.top());
            st.pop();
        }

        string ans="";
        for(int i=0; i<n; i++) {
            if(idx.find(i) == idx.end()) {
                ans.push_back(s[i]);
            }
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// "lee(t(c)o)de)"\n
// @lcpr case=end

// @lcpr case=start
// "a)b(c)d"\n
// @lcpr case=end

// @lcpr case=start
// "))(("\n
// @lcpr case=end

 */

