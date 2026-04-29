/*
 * @lc app=leetcode.cn id=2033 lang=cpp
 * @lcpr version=30204
 *
 * [2033] 获取单值网格的最小操作数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m=grid.size(), n=grid[0].size();
        vector<int> arr(m*n);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if((grid[i][j] - grid[0][0])%x != 0) {
                    return -1;
                }
                arr[i*n+j] = grid[i][j];
            }
        }

        sort(arr.begin(), arr.end());
        int target = arr[m*n/2];
        int ans=0;
        for(int i=0; i<m*n; i++) {
            ans += abs(arr[i]-target)/x;
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,4],[6,8]]\n2\n
// @lcpr case=end

// @lcpr case=start
// [[1,5],[2,3]]\n1\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,4]]\n2\n
// @lcpr case=end

 */

