/*
 * @lc app=leetcode.cn id=84 lang=cpp
 * @lcpr version=30204
 *
 * [84] 柱状图中最大的矩形
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int largestRectangleAreaOpt(vector<int>& heights) {
        vector<int> indexes;
        indexes.push_back(-1);
        int ans = 0;

        for(int i = 0; i <= (int)heights.size(); i++) {
            int currentHeight = (i == (int)heights.size()) ? 0 : heights[i];
            while(indexes.back() != -1 && heights[indexes.back()] > currentHeight) {
                int heightIndex = indexes.back();
                indexes.pop_back();
                int width = i - indexes.back() - 1;
                // 当前柱子右侧遇到更矮高度，heightIndex 的最大宽度已经确定。
                ans = max(ans, heights[heightIndex] * width);
            }
            indexes.push_back(i);
        }

        return ans;
    }

public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        heights.insert(heights.begin(), 0);
        stack<int> st;
        st.push(0);
        int ans=0;
        for(int i=1; i<heights.size(); i++) {
            while(!st.empty() && heights[st.top()] > heights[i]) {
                int mid=st.top();
                st.pop();
                if(!st.empty()) {
                    int left=st.top();
                    int right=i;
                    int w=right-left-1;
                    int h=heights[mid];
                    ans =max(ans, h*w);
                }
            }
            st.push(i);
        }
        return ans;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,1,5,6,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [2,4]\n
// @lcpr case=end

 */

