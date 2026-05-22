#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubarraySum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        seen[0] = 1;

        int prefix = 0;
        int ans = 0;
        for (int value : nums) {
            prefix += value;
            if (seen.count(prefix - target)) {
                ans += seen[prefix - target];
            }
            ++seen[prefix];
        }
        return ans;
    }

    int countSubarrayDivisibleByK(vector<int>& nums, int k) {
        unordered_map<int, int> seen;
        seen[0] = 1;

        int prefix = 0;
        int ans = 0;
        for (int value : nums) {
            prefix = ((prefix + value) % k + k) % k;
            ans += seen[prefix]; // 余数相同，两个前缀之间的子数组可被 k 整除。
            ++seen[prefix];
        }
        return ans;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 1, 1};
    cout << "countSubarraySum([1,1,1], 2) = "
         << solution.countSubarraySum(nums1, 2) << '\n'; // 期望输出：2

    vector<int> nums2 = {4, 5, 0, -2, -3, 1};
    cout << "countSubarrayDivisibleByK([4,5,0,-2,-3,1], 5) = "
         << solution.countSubarrayDivisibleByK(nums2, 5) << '\n'; // 期望输出：7

    return 0;
}
