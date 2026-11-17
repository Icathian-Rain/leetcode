/*
 * @lc app=leetcode.cn id=733 lang=cpp
 * @lcpr version=30204
 *
 * [733] 图像渲染
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
const int DIRECT[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
class Solution {
    vector<vector<int>> floodFillOpt(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = static_cast<int>(image.size());
        int n = static_cast<int>(image[0].size());
        int raw = image[sr][sc];
        if (raw == color) return image; // 原色即新色：不改图，也避免死循环
        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color; // 入队即改色，颜色即访问标记
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && image[nx][ny] == raw) {
                    image[nx][ny] = color; // 入队同时改色，防止重复入队
                    q.push({nx, ny});
                }
            }
        }
        return image;
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m=image.size(), n=image[0].size();
        int raw_color = image[sr][sc];
        if(raw_color == color) {
            return image;
        }
        queue<pii> q;
        q.emplace(sr, sc);
        image[sr][sc] = color;
        while(!q.empty()) {
            auto [px, py] = q.front(); q.pop();
            // image[px][py] = color;
            for(int i=0; i<4; i++) {
                int nx = px+DIRECT[i][0], ny = py+DIRECT[i][1];
                if(nx >= 0 && nx < m && ny >= 0 && ny < n && image[nx][ny] == raw_color) {
                    q.emplace(nx, ny);
                    image[nx][ny] = color;
                }
            }
        }
        return image;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,1,1],[1,1,0],[1,0\n1\n1\n2\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0],[0,0,0]]\n0\n0\n0\n
// @lcpr case=end

 */

