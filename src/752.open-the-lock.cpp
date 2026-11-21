/*
 * @lc app=leetcode.cn id=752 lang=cpp
 * @lcpr version=30204
 *
 * [752] 打开转盘锁
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int openLockOpt(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());
        if (dead.count("0000")) return -1; // 起手即锁死
        if (target == "0000") return 0;     // 起点即答案
        unordered_map<string, int> dist;    // 出现即已访问
        queue<string> q;
        dist["0000"] = 0;
        q.push("0000");
        while (!q.empty()) {
            string cur = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {          // 四个拨轮位
                for (int delta : {-1, 1}) {       // 两种拨动
                    string next = cur;
                    // 算术回绕：'0'-'9' 环形加减
                    next[i] = static_cast<char>('0' + (next[i] - '0' + delta + 10) % 10);
                    if (next == target) return dist[cur] + 1; // 扩展中判终点
                    if (!dead.count(next) && !dist.count(next)) {
                        dist[next] = dist[cur] + 1; // 入队即标记
                        q.push(next);
                    }
                }
            }
        }
        return -1;
    }

public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadset(deadends.begin(), deadends.end());
        unordered_map<string, int> dist;
        queue<string> q;
        if(deadset.count("0000") == 1) return -1;
        if(target == "0000") return 0;
        q.push("0000");
        dist["0000"] = 0;
        while(!q.empty()) {
            auto cur=q.front(); q.pop();
            for(int i=0; i<4; i++) {        
                for(int j=-1; j<=1; j+=2) {
                    string tmp = cur;
                    tmp[i] += j;
                    if(tmp[i] < '0') tmp[i] = '9';
                    if(tmp[i] > '9') tmp[i] = '0';
                    if(tmp == target) return dist[cur]+1;
                    if(deadset.count(tmp) == 0 && dist.count(tmp) == 0) {
                        dist[tmp] = dist[cur] + 1;
                        q.push(tmp);
                    }
                }
            }
        }
        return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["0201","0101","0102","1212","2002"]\n"0202"\n
// @lcpr case=end

// @lcpr case=start
// ["8888"]\n"0009"\n
// @lcpr case=end

// @lcpr case=start
// ["8887","8889","8878","8898","8788","8988","7888","9888"]\n"8888"\n
// @lcpr case=end

 */

