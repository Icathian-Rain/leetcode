/*
 * @lc app=leetcode.cn id=79 lang=cpp
 * @lcpr version=30204
 *
 * [79] 单词搜索
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool existOpt(vector<vector<char>>& board, string word) {
        int rows = static_cast<int>(board.size());
        int cols = static_cast<int>(board[0].size());
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        function<bool(int, int, int)> dfs = [&](int x, int y, int index) {
            if (board[x][y] != word[index]) {
                return false;
            }
            if (index == static_cast<int>(word.size()) - 1) {
                return true;
            }

            visited[x][y] = true;
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || visited[nx][ny]) {
                    continue;
                }
                if (dfs(nx, ny, index + 1)) {
                    visited[x][y] = false; // 成功返回前也恢复现场，保持函数副作用干净。
                    return true;
                }
            }
            visited[x][y] = false;
            return false;
        };

        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if (dfs(x, y, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    vector<vector<int>> DIRCET = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> vis;
    bool dfs(vector<vector<char>>& board, string &word, int x, int y, int idx) {
        if(board[x][y] != word[idx]) {
            return false;
        }
        if(idx == word.size()-1) {
            return true;
        }
        vis[x][y] = true;
        int m=board.size();
        int n=board[0].size();
        


        for(int k=0; k<4; k++) {
            int dx=x+DIRCET[k][0], dy=y+DIRCET[k][1];
            if(dx>=0 && dx<m && dy>=0 && dy<n && vis[dx][dy] == false) {
                if(dfs(board, word, dx, dy, idx+1) == true) {
                    return true;
                }
            }
        }
        vis[x][y] = false;
        return false;
    }


    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                vis.assign(m, vector<bool>(n, false));
                if(dfs(board, word, x, y, 0) == true) {
                    cout << x << " " << y << endl;
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]\n"ABCCED"\n
// @lcpr case=end

// @lcpr case=start
// [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]\n"SEE"\n
// @lcpr case=end

// @lcpr case=start
// [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]\n"ABCB"\n
// @lcpr case=end



 */

