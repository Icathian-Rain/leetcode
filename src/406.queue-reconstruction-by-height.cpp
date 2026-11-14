/*
 * @lc app=leetcode.cn id=406 lang=cpp
 * @lcpr version=30204
 *
 * [406] 根据身高重建队列
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> reconstructQueueOpt(vector<vector<int>>& people) {
        // 身高降序、同高 k 升序：先放的人对后放的人全部算"更高的前置者"
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] > b[0];
            return a[1] < b[1];
        });
        vector<vector<int>> ans;
        for (const auto& person : people) {
            // 已放的人都 >= 当前身高，k 即最终下标，直接插入
            ans.insert(ans.begin() + person[1], person);
        }
        return ans;
    }

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n=people.size();
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
        });
        vector<vector<int>> ans(n);
        for(auto person: people) {
            int spaces = person[1] + 1;
            for(int i=0; i<n; i++) {
                if(ans[i].empty()) {
                    spaces--;
                    if(!spaces) {
                        ans[i] = person;
                        break;
                    }
                }
            }
        }
        return ans;
    }

};
// @lc code=end



/*
// @lcpr case=start
// [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]\n
// @lcpr case=end

 */

