#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    long long atMostDistinct(const vector<int>& nums, int k) {
        if (k < 0) {
            return 0;
        }

        unordered_map<int, int> count;
        int left = 0;
        long long ans = 0;

        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            ++count[nums[right]];
            while (static_cast<int>(count.size()) > k) {
                if (--count[nums[left]] == 0) {
                    count.erase(nums[left]);
                }
                ++left;
            }

            ans += right - left + 1; // 所有以 right 结尾、起点在 [left, right] 的窗口都合法。
        }

        return ans;
    }

public:
    long long subarraysWithExactlyKDistinct(vector<int>& nums, int k) {
        return atMostDistinct(nums, k) - atMostDistinct(nums, k - 1);
    }

    int longestAtMostKDistinct(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            ++count[nums[right]];
            while (static_cast<int>(count.size()) > k) {
                if (--count[nums[left]] == 0) {
                    count.erase(nums[left]);
                }
                ++left;
            }
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 2, 1, 2, 3};
    cout << "subarraysWithExactlyKDistinct([1,2,1,2,3], 2) = "
         << solution.subarraysWithExactlyKDistinct(nums1, 2) << '\n'; // 期望输出：7

    vector<int> nums2 = {1, 2, 1, 3, 4};
    cout << "longestAtMostKDistinct([1,2,1,3,4], 2) = "
         << solution.longestAtMostKDistinct(nums2, 2) << '\n'; // 期望输出：3

    return 0;
}
