/*
 * @lc app=leetcode.cn id=554 lang=cpp
 * @lcpr version=30204
 *
 * [554] 砖墙
 */

// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using ll = long long;
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int n=wall.size();

        unordered_map<ll, int> cnt;
        for(int i=0; i<n; i++) {
            ll l=0;
            for(int j=0; j<wall[i].size()-1; j++) {
                ll r = l+wall[i][j];
                cnt[r]++;
                l = r;
            }
        }

        int ans=n;
        for(auto [pos, num]: cnt) {
            ans=min(ans, n-num);
        }
        return ans;
    }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[1],[1],[1]]\n
// @lcpr case=end

// @lcpr case=start
// [[2147483647,2147483647,2147483647,2147483647]]\n
// @lcpr case=end
 */
