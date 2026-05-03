/*
 * @lc app=leetcode.cn id=18 lang=cpp
 * @lcpr version=30204
 *
 * [18] 四数之和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using ll = long long;
class Solution {
    vector<vector<int>> fourSumOpt(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        int n = nums.size();
        for (int a = 0; a < n - 3; ++a) {
            if (a > 0 && nums[a] == nums[a - 1]) {
                continue;
            }
            // 排序后最小四数已经过大，后续 a 只会更大。
            if ((ll)nums[a] + nums[a + 1] + nums[a + 2] + nums[a + 3] > target) {
                break;
            }
            // 当前 a 搭配最大的三个数仍过小，只能换更大的 a。
            if ((ll)nums[a] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) {
                continue;
            }

            for (int b = a + 1; b < n - 2; ++b) {
                if (b > a + 1 && nums[b] == nums[b - 1]) {
                    continue;
                }
                if ((ll)nums[a] + nums[b] + nums[b + 1] + nums[b + 2] > target) {
                    break;
                }
                if ((ll)nums[a] + nums[b] + nums[n - 2] + nums[n - 1] < target) {
                    continue;
                }

                int c = b + 1;
                int d = n - 1;
                while (c < d) {
                    ll sum = (ll)nums[a] + nums[b] + nums[c] + nums[d];
                    if (sum < target) {
                        ++c;
                    } else if (sum > target) {
                        --d;
                    } else {
                        ans.push_back({nums[a], nums[b], nums[c], nums[d]});
                        // 固定前两位后，跳过两侧重复值避免重复四元组。
                        while (c < d && nums[c] == nums[c + 1]) {
                            ++c;
                        }
                        while (c < d && nums[d] == nums[d - 1]) {
                            --d;
                        }
                        ++c;
                        --d;
                    }
                }
            }
        }

        return ans;
    }

public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n=nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        for(int a=0; a<n; a++) {
            if(a>0 && nums[a] == nums[a-1]) continue;

            for(int b=a+1; b<n; b++) {
                if(b>a+1 && nums[b] == nums[b-1]) continue;
                ll sum = nums[a]+nums[b];

                int c=b+1, d=n-1;
                while(c < d) {
                    if(sum + nums[c] + nums[d] < target) {
                        c++;
                    } else if(sum + nums[c] + nums[d] > target) {
                        d--;
                    } else {
                        ans.push_back({nums[a], nums[b], nums[c], nums[d]});
                        while(c < d && nums[c] == nums[c+1]) c++;
                        while(c < d && nums[d] == nums[d-1]) d--;
                        c++;
                        d--;
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
// [1,0,-1,0,-2,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [2,2,2,2,2]\n8\n
// @lcpr case=end

 */

