/*
 * @lc app=leetcode.cn id=744 lang=cpp
 * @lcpr version=30204
 *
 * [744] 寻找比目标字母大的最小字母
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    char nextGreatestLetterOpt(vector<char>& letters, char target) {
        int left = 0;
        int right = static_cast<int>(letters.size());

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (letters[middle] <= target) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        // 如果所有字母都不大于 target，按题意回绕到第一个字母。
        return left == static_cast<int>(letters.size()) ? letters[0] : letters[left];
    }

public:
    char s1(vector<char>& letters, char target) {
        // 寻找第一个大于target的字符
        int n=letters.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(letters[m] <= target) {
                l=m+1;
            } else {
                r=m;
            }
        }
        return l==n ? letters[0]: letters[l];
    }
    char s2(vector<char>& letters, char target) {
        int n=letters.size();
        int m=upper_bound(letters.begin(), letters.end(), target) - letters.begin();
        return m==n ? letters[0]: letters[m];
    }
    char nextGreatestLetter(vector<char>& letters, char target) {
        // return s1(letters, target);
        return s2(letters, target);
    }
};
// @lc code=end



/*
// @lcpr case=start
// ['c', 'f'\n'a'\n
// @lcpr case=end

// @lcpr case=start
// ['c','f','j']\n'c'\n
// @lcpr case=end

// @lcpr case=start
// ['x','x','y','y']\n'z'\n
// @lcpr case=end

 */
