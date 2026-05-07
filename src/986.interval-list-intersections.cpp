/*
 * @lc app=leetcode.cn id=986 lang=cpp
 * @lcpr version=30204
 *
 * [986] 区间列表的交集
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> intervalIntersectionOpt(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> ans;
        int first = 0;
        int second = 0;

        while(first < (int)firstList.size() && second < (int)secondList.size()) {
            int left = max(firstList[first][0], secondList[second][0]);
            int right = min(firstList[first][1], secondList[second][1]);
            if(left <= right) {
                ans.push_back({left, right});
            }

            // 谁的右端点更小，谁就不可能再和后续区间产生新的交集。
            if(firstList[first][1] < secondList[second][1]) {
                first++;
            } else {
                second++;
            }
        }

        return ans;
    }

public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int len1=firstList.size(), len2=secondList.size();
        int a=0, b=0;
        vector<vector<int>> ans;
        while((a<len1) && (b<len2)) {
            int l1=firstList[a][0], r1=firstList[a][1];
            int l2=secondList[b][0], r2=secondList[b][1];
            if(r1 < l2) {
                a++;
            } else if(r2 < l1) {
                b++;
            } else if(r1 >= l2 && r1 <= r2) {
                ans.push_back({max(l1, l2), r1});
                a++;
            } else if(r2 >= l1 && r2 <= r1) {
                ans.push_back({max(l1, l2), r2});
                b++;
            }
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,2],[5,10],[13,23],[24,25]]\n[[1,5],[8,12],[15,24],[25,26]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,3],[5,9]]\n[]\n
// @lcpr case=end

// @lcpr case=start
// []\n[[4,8],[10,12]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,7]]\n[[3,10]]\n
// @lcpr case=end

// @lcpr case=start
// [[3,10]]\n[[5,10]]\n
// @lcpr case=end
 */

