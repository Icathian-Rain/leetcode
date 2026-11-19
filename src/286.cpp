/*
 * @lc app=leetcode.cn id=286 lang=cpp
 * @lcpr version=30204
 *
 * [286] 墙与门
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
const int INF=2147483647;
const int DIRECT[][2]={{1,0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
    void wallsAndGatesOpt(vector<vector<int>>& rooms) {
        int m = static_cast<int>(rooms.size());
        int n = static_cast<int>(rooms[0].size());
        // INF 兼作未访问标记：填充后不再等于 INF，天然防重复入队
        queue<pii> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) q.push({i, j}); // 多源：全部门同时入队
            }
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + DIRECT[d][0], ny = y + DIRECT[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && rooms[nx][ny] == INF) {
                    rooms[nx][ny] = rooms[x][y] + 1; // 首次到达即最近距离
                    q.push({nx, ny});
                }
            }
        }
    }

public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m=rooms.size(), n=rooms[0].size();
        queue<pii> q;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        while(!q.empty()) {
            auto [i, j] = q.front(); q.pop();
            for(int d=0; d<4; d++) {
                int ni=i+DIRECT[d][0], nj=j+DIRECT[d][1];
                if(ni>=0 && ni<m && nj>=0 && nj<n && rooms[ni][nj]==INF) {
                    rooms[ni][nj]=rooms[i][j]+1;
                    q.push({ni, nj});
                }
            }
        }
        return ; 
    }
};
// @lc code=end