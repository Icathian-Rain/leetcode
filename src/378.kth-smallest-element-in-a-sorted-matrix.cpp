/*
 * @lc app=leetcode.cn id=378 lang=cpp
 * @lcpr version=30204
 *
 * [378] 有序矩阵中第 K 小的元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    int countLessEqual(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int row = n - 1, col = 0;
        int count = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= target) {
                // 当前列从 0 到 row 都不大于 target。
                count += row + 1;
                ++col;
            } else {
                --row;
            }
        }
        return count;
    }

    int kthSmallestOpt(vector<vector<int>>& matrix, int k) {
        int left = matrix.front().front();
        int right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (countLessEqual(matrix, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        auto cmp = [&](const pii& a, const pii& b) {
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        int m=matrix.size(), n=matrix[0].size();
        for(int i=0; i<m; i++) {
            pq.emplace(i, 0);
        }

        for(int i=0;i<k-1; i++) {
            auto [x, y] = pq.top(); pq.pop();
            if(y+1 != n) {
                pq.emplace(x, y+1);
            }
        }

        auto [x, y] = pq.top();
        return matrix[x][y];


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,5,9],[10,11,13],[12,13,15]]\n8\n
// @lcpr case=end

// @lcpr case=start
// [[-5]]\n1\n
// @lcpr case=end

 */

