/*
 * @lc app=leetcode.cn id=36 lang=cpp
 * @lcpr version=30204
 *
 * [36] 有效的数独
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // 行检测
        for(int i=0; i<9; i++) {
            vector<int> f(9, 0);
            for(int j=0; j<9; j++) {
                if(board[i][j] == '.') continue;
                int num=board[i][j]-'1';
                if(f[num] == 1) {
                    return false;
                }
                f[num] = 1;
            }
        }

        // 列检测
        for(int j=0; j<9; j++) {
            vector<int> f(9, 0);
            for(int i=0; i<9; i++) {
                if(board[i][j] == '.') continue;
                int num=board[i][j]-'1';
                if(f[num] == 1) {
                    return false;
                }
                f[num] = 1;
            }
        }

        // 3x3格子检测
        for(int startI=0; startI<9; startI+=3) {
            for(int startJ=0; startJ<9; startJ+=3) {
                vector<int> f(9, 0);
                for(int i=startI; i<startI+3; i++) {
                    for(int j=startJ; j<startJ+3; j++) {
                        if(board[i][j] == '.') continue;
                        int num=board[i][j]-'1';
                        if(f[num] == 1) {
                            return false;
                        }
                        f[num] = 1;
                    }
                }
            }
        }
        return true;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]\n
// @lcpr case=end

// @lcpr case=start
// [["8","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]\n
// @lcpr case=end

 */

