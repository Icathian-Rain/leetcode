/*
 * @lc app=leetcode.cn id=417 lang=cpp
 * @lcpr version=30204
 *
 * [417] 太平洋大西洋水流问题
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
const int DIRECT[][2]={{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
    // 从一组边界源点逆流标记可达格：邻居不低于当前即可回溯
    void bfsMark(vector<vector<int>>& h, vector<vector<char>>& mark, vector<pair<int,int>>& seeds) {
        int m = static_cast<int>(h.size());
        int n = static_cast<int>(h[0].size());
        queue<pii> q;
        for (auto& [x, y] : seeds) {
            mark[x][y] = 1;     // 入队即标记
            q.push({x, y});
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + DIRECT[d][0], ny = y + DIRECT[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                    && !mark[nx][ny] && h[nx][ny] >= h[x][y]) { // 等高可流动
                    mark[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    vector<vector<int>> pacificAtlanticOpt(vector<vector<int>>& heights) {
        int m = static_cast<int>(heights.size());
        int n = static_cast<int>(heights[0].size());
        vector<vector<char>> pac(m, vector<char>(n, 0)), atl(m, vector<char>(n, 0));
        vector<pii> pSeeds, aSeeds;
        for (int j = 0; j < n; j++) {
            aSeeds.push_back({m - 1, j});          // 下行属于大西洋
            if (j > 0) pSeeds.push_back({0, j});    // 上行属于太平洋（角点归左列）
        }
        for (int i = 0; i < m; i++) {
            pSeeds.push_back({i, 0});                     // 左列属于太平洋
            if (i != m - 1) aSeeds.push_back({i, n - 1}); // 右列属于大西洋
        }
        bfsMark(heights, pac, pSeeds);
        bfsMark(heights, atl, aSeeds);
        // 双标记交集即双洋可达格
        vector<vector<int>> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pac[i][j] && atl[i][j]) ans.push_back({i, j});
            }
        }
        return ans;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m=heights.size(), n=heights[0].size();
        vector<vector<int>> pflag(m, vector<int>(n, false)), aflag(m, vector<int>(n, false));
        // p test
        queue<pii> q;
        for(int i=0; i<m; i++) {
            pflag[i][0]=true;
            q.push({i, 0});
        }
        for(int j=1; j<n; j++) {
            pflag[0][j]=true;
            q.push({0, j});
        }
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for(int i=0; i<4; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                if(nx>=0 && nx<m && ny>=0 && ny<n && pflag[nx][ny]==false && heights[nx][ny]>=heights[x][y]) {
                    pflag[nx][ny]=true;
                    q.push({nx, ny});
                }
            }
        }

        for(int i=0; i<m; i++) {
            aflag[i][n-1]=true;
            q.push({i, n-1});
        }
        for(int j=0; j<n-1; j++) {
            aflag[m-1][j]=true;
            q.push({m-1, j});
        }
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for(int i=0; i<4; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                if(nx>=0 && nx<m && ny>=0 && ny<n && aflag[nx][ny]==false && heights[nx][ny]>=heights[x][y]) {
                    aflag[nx][ny]=true;
                    q.push({nx, ny});
                }
            }
        }
        
        vector<vector<int>> ans;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(pflag[i][j] && aflag[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;





    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[2,1],[1,2]]\n
// @lcpr case=end
// 2, 1
// 1, 2

 */

