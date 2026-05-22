#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> daysUntilWarmer(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(), 0);
        vector<int> waiting;

        for (int i = 0; i < static_cast<int>(temperatures.size()); ++i) {
            while (!waiting.empty() && temperatures[waiting.back()] < temperatures[i]) {
                int previous = waiting.back();
                waiting.pop_back();
                ans[previous] = i - previous; // 题目要距离，所以用当前下标减等待下标。
            }
            waiting.push_back(i);
        }

        return ans;
    }

    vector<int> nextGreaterCircular(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        vector<int> waiting;

        for (int i = 0; i < 2 * n; ++i) {
            int index = i % n;
            while (!waiting.empty() && nums[waiting.back()] < nums[index]) {
                ans[waiting.back()] = nums[index];
                waiting.pop_back();
            }
            if (i < n) {
                waiting.push_back(index);
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

    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    cout << "daysUntilWarmer = ";
    printVector(solution.daysUntilWarmer(temperatures)); // 期望输出：1 1 4 2 1 1 0 0

    vector<int> nums = {1, 2, 1};
    cout << "nextGreaterCircular = ";
    printVector(solution.nextGreaterCircular(nums)); // 期望输出：2 -1 2

    return 0;
}
