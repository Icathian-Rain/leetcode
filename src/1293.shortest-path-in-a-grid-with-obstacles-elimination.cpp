/*
 * @lc app=leetcode.cn id=1293 lang=cpp
 * @lcpr version=30204
 *
 * [1293] 网格中的最短路径
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
const int DIRECT[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
using ti = tuple<int, int, int>;
class Solution {
    int shortestPathOpt(vector<vector<int>>& grid, int k) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        // 额度至少够平推一路：答案封顶曼哈顿距离 m+n-2
        if (k >= m + n - 2) return m + n - 2;
        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};
        vector<vector<int>> best(m, vector<int>(n, -1)); // 该格最大剩余额度
        queue<ti> q;
        best[0][0] = k;
        q.emplace(0, 0, k);
        for (int steps = 0; !q.empty(); steps++) { // 层计数：层号即步数
            for (int cnt = static_cast<int>(q.size()); cnt > 0; cnt--) {
                auto [x, y, re] = q.front(); q.pop();
                if (x == m - 1 && y == n - 1) return steps;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    int nxt = re - grid[nx][ny]; // 障碍扣额度
                    if (nxt <= best[nx][ny]) continue; // 支配剪枝：不更充裕则弃
                    best[nx][ny] = nxt;
                    q.emplace(nx, ny, nxt);
                }
            }
        }
        return -1;
    }

public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m=grid.size(), n=grid[0].size();
        vector<vector<int>> best(m, vector<int>(n, -1));
        queue<ti> q;
        best[0][0] = k;
        q.push({0, 0, k});
        for(int steps=0; !q.empty(); steps++) {
            for(int count=q.size(); count>0; count--) {
                auto [x, y, re] = q.front(); q.pop();
                if(x == m-1 && y == n-1) return steps;
                for(int i=0; i<4; i++) {
                    int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                    if(nx<0 || nx>=m || ny<0 || ny >=n) continue;
                    int next=re-grid[nx][ny];
                    if(next <= best[nx][ny]) continue;
                    best[nx][ny] = next;
                    q.push({nx, ny, next});
                }
            }
        }
        return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]]\n1\n
// @lcpr case=end

// @lcpr case=start
// [[0,1,1],[1,1,1],[1,0,0]]\n1\n
// @lcpr case=end

 */

