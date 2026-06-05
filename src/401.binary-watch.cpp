/*
 * @lc app=leetcode.cn id=401 lang=cpp
 * @lcpr version=30204
 *
 * [401] 二进制手表
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<string> readBinaryWatchOpt(int turnedOn) {
        vector<string> ans;
        for (int hour = 0; hour < 12; ++hour) {
            for (int minute = 0; minute < 60; ++minute) {
                // 小时和分钟亮灯数量之和必须正好等于 turnedOn。
                if (__builtin_popcount(hour) + __builtin_popcount(minute) != turnedOn) {
                    continue;
                }
                string time = to_string(hour) + ":";
                if (minute < 10) {
                    time.push_back('0');
                }
                time += to_string(minute);
                ans.push_back(time);
            }
        }
        return ans;
    }

    void hdfs(int idx, int left, vector<int>& hvis, vector<int>& hresult) {
        if(left == 0) {
            int h = 0;
            for(int i=0; i<4; i++) {
                if(hvis[i] == true) {
                    h |= 1 << i;
                }
            }
            if(h <  12) {
                hresult.push_back(h);
            }
            return;
        }
        if(idx == 4) {
            return;
        }

        hvis[idx] = true;
        hdfs(idx+1, left-1, hvis, hresult);
        hvis[idx] = false;
        hdfs(idx+1, left, hvis, hresult);
    }

    void mdfs(int idx, int left, vector<int>& mvis, vector<int>& mresult) {
        if(left == 0) {
            int m = 0;
            for(int i=0; i<6; i++) {
                if(mvis[i] == true) {
                    m |= 1 << i;
                }
            }
            if(m <  60) {
                mresult.push_back(m);
            }
            return;
        }
        if(idx == 6) {
            return;
        }

        mvis[idx] = true;
        mdfs(idx+1, left-1, mvis, mresult);
        mvis[idx] = false;
        mdfs(idx+1, left, mvis, mresult);
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> ans;
        for(int hour = 0; hour<=turnedOn; hour++) {
            int min = turnedOn - hour;
            if(hour > 4 || min > 6) continue;
            // 小时有hour个bit亮，分钟有min个bit亮
            vector<int> hresult, mresult;
            vector<int> hvis(4, false);
            vector<int> mvis(6, false);
            hdfs(0, hour, hvis, hresult);
            mdfs(0, min, mvis, mresult);
            for(auto h: hresult) {
                for(auto m: mresult) {
                    string time = "";
                    time += to_string(h);
                    time.push_back(':');
                    if(m < 10) time.push_back('0');
                    time += to_string(m);

                    ans.push_back(time);
                }
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 1\n
// @lcpr case=end

// @lcpr case=start
// 9\n
// @lcpr case=end

 */

