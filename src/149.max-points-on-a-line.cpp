/*
 * @lc app=leetcode.cn id=149 lang=cpp
 * @lcpr version=30204
 *
 * [149] 直线上最多的点数
 */

// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int gcd(int a, int b) {
        return b ? gcd(b, a%b): a;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        // 确定一个点a, 再确定一个斜率k即可确定一条直线
        // 斜率k = my/mx, 可以通过(my, mx)来定义斜率
        int n=points.size();
        if(n <= 2) {
            return n;
        }

        int ans=0;
        for(int i=0; i<n; i++) {
            if(ans >= n-i || ans > n/2) {
                break;
            }
            unordered_map<int, int> mp;
            for(int j=i+1; j<n; j++) {
                int my=points[j][1]-points[i][1];
                int mx=points[j][0]-points[i][0];
                if(mx == 0) {
                    my = 1;
                } else if(my == 0) {
                    mx = 1;
                } else {
                    if(my < 0) {
                        mx = -mx;
                        my = -my;
                    }
                    int gcdxy = gcd(abs(mx), abs(my));
                    mx /= gcdxy, my/=gcdxy;
                }
                mp[my+mx*20001]++;
            }
            for(auto [_, num]:mp) {
                ans =max(ans, num+1);
            }
        }
        return ans;
    }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,1],[2,2],[3,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]\n
// @lcpr case=end

 */
