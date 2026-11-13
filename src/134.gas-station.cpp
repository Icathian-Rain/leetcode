/*
 * @lc app=leetcode.cn id=134 lang=cpp
 * @lcpr version=30204
 *
 * [134] 加油站
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int s1(vector<int>& gas, vector<int>& cost) {
        int n=gas.size();
        int i=0;
        while(i < n) {
            int sumOfGas = 0, sumOfCost = 0;
            int cnt = 0;
            while(cnt < n) {
                int j=(i+cnt)%n;
                sumOfGas += gas[j];
                sumOfCost += cost[j];
                if(sumOfCost > sumOfGas) {
                    break;
                }
                cnt ++;
            }
            if(cnt == n) {
                return i;
            } else {
                i = i+cnt+1;
            }
        }
        return -1;
    }

    int s2(vector<int>& gas, vector<int>& cost) {
        int n=gas.size();
        int minBalance = 0;
        int minIndex = 0;
        int balance = 0;
        for(int i=0; i<n; i++) {
            balance = balance + gas[i]-cost[i];
            if(balance < minBalance) {
                minBalance = balance;
                minIndex = i+1;
            }
        }
        return balance >= 0 ? minIndex : -1;
    }
    int canCompleteCircuitOpt(vector<int>& gas, vector<int>& cost) {
        int n = static_cast<int>(gas.size());
        int tank = 0;   // 从当前候选起点出发的剩余油量
        int total = 0;  // 全局总盈亏，判定有解充要条件
        int start = 0;
        for (int i = 0; i < n; i++) {
            int diff = gas[i] - cost[i];
            tank += diff;
            total += diff;
            if (tank < 0) {
                // start..i 内任何起点都过不了 i，整体排除后重置
                start = i + 1;
                tank = 0;
            }
        }
        return total >= 0 ? start : -1;
    }

public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // return s1(gas, cost);
        return s2(gas, cost);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n[3,4,5,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [2,3,4]\n[3,4,3]\n
// @lcpr case=end

 */

