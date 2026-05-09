/*
 * @lc app=leetcode.cn id=682 lang=cpp
 * @lcpr version=30204
 *
 * [682] 棒球比赛
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int calPointsOpt(vector<string>& operations) {
        vector<int> scores;
        int total = 0;

        for(const string& op: operations) {
            if(op == "C") {
                total -= scores.back();
                scores.pop_back();
            } else if(op == "D") {
                scores.push_back(scores.back() * 2);
                total += scores.back();
            } else if(op == "+") {
                // 新分数只依赖最近两轮有效得分。
                int current = scores[(int)scores.size() - 1] + scores[(int)scores.size() - 2];
                scores.push_back(current);
                total += current;
            } else {
                int current = stoi(op);
                scores.push_back(current);
                total += current;
            }
        }

        return total;
    }

public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        for(auto op: operations) {
            if(op == "C") {
                if(!st.empty())
                    st.pop();
            } else if(op == "D") {
                if(!st.empty()) {
                    int num=st.top();
                    st.push(num*2);
                }
            } else if(op == "+") {
                if(st.empty()) {
                    continue;
                }
                int num1 = st.top();
                st.pop();

                if(st.empty()) {
                    st.push(num1);
                    continue;
                }

                int num2 = st.top();
                st.push(num1);
                st.push(num1 + num2);
            } else {
                int num=atoi(op.c_str());
                st.push(num);
            }
        }
        int ans=0;
        while(!st.empty()) {
            ans+=st.top();
            st.pop();
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["5","2","C","D","+"]\n
// @lcpr case=end

// @lcpr case=start
// ["5","-2","4","C","D","9","+","+"]\n
// @lcpr case=end

// @lcpr case=start
// ["1"]\n
// @lcpr case=end

 */

