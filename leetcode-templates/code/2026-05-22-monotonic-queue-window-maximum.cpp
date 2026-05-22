#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> candidates;
        vector<int> ans;

        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            while (!candidates.empty() && candidates.front() <= right - k) {
                candidates.pop_front(); // 队首已经离开当前窗口。
            }
            while (!candidates.empty() && nums[candidates.back()] <= nums[right]) {
                candidates.pop_back(); // 当前值更靠右且不小，旧候选失去价值。
            }

            candidates.push_back(right);
            if (right >= k - 1) {
                ans.push_back(nums[candidates.front()]);
            }
        }

        return ans;
    }
};

static void printVector(const vector<int>& values) {
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
}

int main() {
    Solution solution;

    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    cout << "maxSlidingWindow k=3 = ";
    printVector(solution.maxSlidingWindow(nums1, 3)); // 期望输出：3 3 5 5 6 7

    vector<int> nums2 = {4, 2, 12};
    cout << "maxSlidingWindow k=1 = ";
    printVector(solution.maxSlidingWindow(nums2, 1)); // 期望输出：4 2 12

    return 0;
}
