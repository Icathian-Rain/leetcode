/*
 * @lc app=leetcode.cn id=763 lang=cpp
 * @lcpr version=30204
 *
 * [763] 划分字母区间
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> partitionLabelsOpt(string s) {
        int n = static_cast<int>(s.size());
        int last[26];
        for (int i = 0; i < 26; i++) last[i] = -1;
        for (int i = 0; i < n; i++) last[s[i] - 'a'] = i; // 每个字母最后出现位置
        vector<int> ans;
        int segStart = 0, segEnd = 0;
        // segEnd：当前片段必须延伸到的最远下标
        for (int i = 0; i < n; i++) {
            segEnd = max(segEnd, last[s[i] - 'a']);
            if (i == segEnd) {          // 扫到必然终点，立即切分保证片段数最多
                ans.push_back(segEnd - segStart + 1);
                segStart = segEnd + 1;
            }
        }
        return ans;
    }

public:
    vector<int> partitionLabels(string s) {
        int n=s.length();
        vector<int> rightMost(26, -1);
        for(int i=0; i<n; i++) {
            rightMost[s[i]-'a'] = i;
        }
        int pre = 0;
        int far = 0;
        vector<int> ans;
        for(int i=0; i<n; i++) {
            far = max(far, rightMost[s[i]-'a']);
            if(i == far) {
                ans.push_back(far-pre+1);
                pre = far+1;
            }
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// "ababcbacadefegdehijhklij"\n
// @lcpr case=end

// @lcpr case=start
// "eccbbbbdec"\n
// @lcpr case=end

 */

