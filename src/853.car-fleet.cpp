/*
 * @lc app=leetcode.cn id=853 lang=cpp
 * @lcpr version=30204
 *
 * [853] 车队
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
class Solution {
    int carFleetOpt(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, double>> cars;
        cars.reserve(n);

        for(int i = 0; i < n; i++) {
            double time = (double)(target - position[i]) / speed[i];
            cars.push_back({position[i], time});
        }
        sort(cars.begin(), cars.end(), greater<pair<int, double>>());

        int fleets = 0;
        double slowestTime = 0.0;
        for(auto [pos, time]: cars) {
            if(time > slowestTime) {
                // 从离终点最近的车往后看，只有到达时间更晚才会形成新车队。
                fleets++;
                slowestTime = time;
            }
        }

        return fleets;
    }

public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n=position.size();
        vector<pii> car;
        for(int i=0; i<n; i++) {
            car.push_back({position[i], speed[i]});
        }
        sort(car.begin(), car.end());

        stack<double> st;
        for(int i=0; i<n; i++) {
            double t = (double)(target - car[i].first) / car[i].second;
            while(!st.empty() && t >= st.top()) {
                st.pop();
            }
            st.push(t);
        }
        return st.size();

    }
};
// @lc code=end



/*
// @lcpr case=start
// 12\n[10,8,0,5,3]\n[2,4,1,1,3]\n
// @lcpr case=end

// [0, 3, 5, 8, 10]\n[1, 3, 1, 4, 2]



// @lcpr case=start
// 10\n[3]\n[3]\n
// @lcpr case=end

// @lcpr case=start
// 100\n[0,2,4]\n[4,2,1]\n
// @lcpr case=end

 */

