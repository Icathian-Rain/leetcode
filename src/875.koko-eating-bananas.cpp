/*
 * @lc app=leetcode.cn id=875 lang=cpp
 * @lcpr version=30204
 *
 * [875] 爱吃香蕉的珂珂
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minEatingSpeedOpt(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        auto canFinish = [&](int speed) {
            long long hours = 0;
            for (int pile : piles) {
                hours += (pile + speed - 1) / speed; // 整数上取整，避免浮点误差。
                if (hours > h) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canFinish(middle)) {
                right = middle; // 当前速度可行，继续尝试更小速度。
            } else {
                left = middle + 1;
            }
        }

        return left;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n=piles.size();
        int l=1, r=0;
        for(int i=0; i<n; i++) {
            r = max(r, piles[i]);
        }
        r++;

        auto check=[&](int m) {
            int total=0;
            for(int i=0; i<n; i++) {
                total += ceil(1.0*piles[i]/m);
                if(total > h) {
                    return false;
                }
            }
            return true;
        };

        while(l<r) {
            int m=l+(r-l)/2;
            if(check(m)) {
                r=m;
            } else {
                l=m+1;
            }
        }
        return l;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,6,7,11]\n8\n
// @lcpr case=end

// 1, 2, 2, 3

// @lcpr case=start
// [30,11,23,4,20]\n5\n
// @lcpr case=end

// @lcpr case=start
// [30,11,23,4,20]\n6\n
// @lcpr case=end

 */

