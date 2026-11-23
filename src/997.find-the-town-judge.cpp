/*
 * @lc app=leetcode.cn id=997 lang=cpp
 * @lcpr version=30204
 *
 * [997] 找到小镇的法官
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findJudgeOpt(int n, vector<vector<int>>& trust) {
        vector<int> in(n, 0), out(n, 0);
        for (const auto& t : trust) {
            out[t[0] - 1]++; // t[0] 信任别人：出度
            in[t[1] - 1]++;  // t[1] 被信任：入度
        }
        for (int i = 0; i < n; i++) {
            // 法官：全员信任我（入度 n-1）且我不信任任何人（出度 0）
            if (in[i] == n - 1 && out[i] == 0) return i + 1;
        }
        return -1;
    }

public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> inDig(n, 0), outDig(n, 0);
        for(auto t: trust) {
            int u=t[0]-1, v=t[1]-1;
            outDig[u]++;
            inDig[v]++;
        }
        for(int i=0; i<n; i++) {
            if(inDig[i] == n-1 && outDig[i] == 0) {
                return i+1;
            }
        }
        return -1;

    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n[[1,2]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,3],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,3],[2,3],[3,1]]\n
// @lcpr case=end

 */

