/*
 * @lc app=leetcode.cn id=1011 lang=cpp
 * @lcpr version=30204
 *
 * [1011] 在 D 天内送达包裹的能力
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int shipWithinDaysOpt(vector<int>& weights, int days) {
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);

        auto canShip = [&](int capacity) {
            int usedDays = 1;
            int currentLoad = 0;
            for (int weight : weights) {
                if (currentLoad + weight > capacity) {
                    ++usedDays; // 当前包裹必须放到下一天。
                    currentLoad = 0;
                }
                currentLoad += weight;
                if (usedDays > days) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canShip(middle)) {
                right = middle; // 当前容量可行，继续尝试更小容量。
            } else {
                left = middle + 1;
            }
        }

        return left;
    }

public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n=weights.size();
        int sum=0, mx=0;
        for(int i=0; i<n; i++) {
            sum+=weights[i];
            mx=max(mx, weights[i]);
        }
        auto check = [&](int m) {
            int left=m;
            int cnt=1;
            for(int i=0; i<n; i++) {
                if(left >= weights[i]) {
                    left -=weights[i];
                } else {
                    cnt+=1;
                    left = m-weights[i];
                }
                if(cnt > days) {
                    return false;
                }
            }
            return true;
        };

        int l=mx, r=sum+1;
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
// [1,2,3,4,5,6,7,8,9,10]\n5\n
// @lcpr case=end

// @lcpr case=start
// [3,2,2,4,1,4]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,1,1]\n4\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,1,1]\n4\n
// @lcpr case=end

 */

