/*
 * @lc app=leetcode.cn id=130 lang=cpp
 * @lcpr version=30204
 *
 * [130] 被围绕的区域
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    void dfs(int x, int y, vector<vector<bool>>& flag, vector<vector<char>>& board) {
        int m=board.size(), n=board[0].size();
        if(x < 0 || x >= m || y < 0 || y >= n || board[x][y] == 'X' || flag[x][y] == true) {
            return;
        }
        flag[x][y] = true;
        dfs(x+1, y, flag, board);
        dfs(x-1, y, flag, board);
        dfs(x, y+1, flag, board);
        dfs(x, y-1, flag, board);
        return ;
    }
    void solveOpt(vector<vector<char>>& board) {
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        // 从边界每个 O 出发：与边缘相连的区域标记 '#'（输入即标记，免 flag）
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && board[i][j] == 'O') {
                    queue<pair<int, int>> q;
                    board[i][j] = '#';
                    q.push({i, j});
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                                board[nx][ny] = '#'; // 入队即标记
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X'; // 未保护的全部翻转
                else if (board[i][j] == '#') board[i][j] = 'O'; // 恢复保护区
            }
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        int m=board.size(), n=board[0].size();
        vector<vector<bool>> flag(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i == 0 || i == m-1 || j == 0 || j == n-1) {
                    if(board[i][j] == 'O' && flag[i][j] == false) {
                        dfs(i, j, flag, board);
                    }
                }
            }
        }

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                cout << flag[i][j] << " ";
                if(board[i][j] == 'O' && flag[i][j] == false) {
                    board[i][j] = 'X';
                }
            }
            cout << endl;
        }
        return ;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [['X','X','X','X'],['X','O','O','X'],['X','X','O','X'],['X','O','X','X']]\n
// @lcpr case=end

// @lcpr case=start
// [['X']]\n
// @lcpr case=end

 */

