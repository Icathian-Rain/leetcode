/*
 * @lc app=leetcode.cn id=37 lang=cpp
 * @lcpr version=30204
 *
 * [37] 解数独
 */


// @lcpr-template-start
#include"../header.h"
#include <cstring>
// @lcpr-template-end
// @lc code=start
class Solution {
    bool line[9][9];
    bool column[9][9];
    bool block[3][3][9];
    bool valid;
    vector<pair<int, int>> spaces;

    void solveSudokuOpt(vector<vector<char>>& board) {
        bool rows[9][10] = {};
        bool cols[9][10] = {};
        bool boxes[3][3][10] = {};
        vector<pair<int, int>> blanks;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '.') {
                    blanks.push_back({row, col});
                } else {
                    int digit = board[row][col] - '0';
                    rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = true;
                }
            }
        }

        function<bool(int)> dfs = [&](int index) {
            if (index == static_cast<int>(blanks.size())) {
                return true;
            }

            auto [row, col] = blanks[index];
            for (int digit = 1; digit <= 9; ++digit) {
                if (rows[row][digit] || cols[col][digit] || boxes[row / 3][col / 3][digit]) {
                    continue;
                }
                rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = true;
                board[row][col] = static_cast<char>('0' + digit);
                if (dfs(index + 1)) {
                    return true;
                }
                board[row][col] = '.';
                rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = false; // 回溯时恢复棋盘和约束表。
            }
            return false;
        };

        dfs(0);
    }


    void dfs(vector<vector<char>>& board, int pos) {
        if(pos == spaces.size()) {
            valid = true;
            return ;
        }

        auto [i, j] = spaces[pos];

        for(int digit=0; digit<9 && (valid == false); digit++) {
            if(!line[i][digit] && !column[j][digit] && !block[i/3][j/3][digit]) {
                line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos+1);
                line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = false;
            }
        }

    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(line, false, sizeof(line));
        memset(column, false, sizeof(column));
        memset(block, false, sizeof(block));

        valid = false;

        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                if(board[i][j] == '.') {
                    spaces.push_back(make_pair(i, j));
                } else {
                    int digit = board[i][j] - '0' - 1;
                    line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = true;
                }
            }
        }

        cout << spaces.size() << endl;

        dfs(board, 0);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]\n
// @lcpr case=end

 */

