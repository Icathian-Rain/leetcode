#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<vector<int>> ans;
    vector<int> path;

    void subsetDfs(vector<int>& nums, int start) {
        // 子集类：当前路径本身就是一个合法结果。
        ans.push_back(path);

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            subsetDfs(nums, i + 1);
            path.pop_back();
        }
    }

    void chooseOrSkipSubsetDfs(vector<int>& nums, int index) {
        if (index == static_cast<int>(nums.size())) {
            ans.push_back(path);
            return;
        }

        path.push_back(nums[index]); // 选当前元素。
        chooseOrSkipSubsetDfs(nums, index + 1);
        path.pop_back();

        chooseOrSkipSubsetDfs(nums, index + 1); // 不选当前元素。
    }

    void combinationDfs(int n, int k, int start) {
        if (static_cast<int>(path.size()) == k) {
            ans.push_back(path);
            return;
        }

        int need = k - static_cast<int>(path.size());
        for (int value = start; value <= n - need + 1; ++value) {
            path.push_back(value);
            combinationDfs(n, k, value + 1);
            path.pop_back();
        }
    }

    void permutationDfs(vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (used[i]) {
                continue;
            }

            used[i] = true;
            path.push_back(nums[i]);
            permutationDfs(nums, used);
            path.pop_back();
            used[i] = false; // 回溯恢复，避免影响兄弟分支。
        }
    }

public:
    vector<vector<int>> subsetsTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        subsetDfs(nums, 0);
        return ans;
    }

    vector<vector<int>> subsetsChooseOrSkipTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        chooseOrSkipSubsetDfs(nums, 0);
        return ans;
    }

    vector<vector<int>> combinationsTemplate(int n, int k) {
        ans.clear();
        path.clear();
        combinationDfs(n, k, 1);
        return ans;
    }

    vector<vector<int>> permutationsTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        permutationDfs(nums, used);
        return ans;
    }
};

void print2D(const vector<vector<int>>& values) {
    for (const auto& row : values) {
        cout << '[';
        for (int i = 0; i < static_cast<int>(row.size()); ++i) {
            if (i > 0) {
                cout << ',';
            }
            cout << row[i];
        }
        cout << "] ";
    }
    cout << '\n';
}

int main() {
    Solution solution;

    vector<int> nums = {1, 2, 3};
    auto subsets = solution.subsetsTemplate(nums);
    print2D(subsets); // 期望输出：8 个子集，包含空集和 [1,2,3]

    auto chooseOrSkipSubsets = solution.subsetsChooseOrSkipTemplate(nums);
    print2D(chooseOrSkipSubsets); // 期望输出：8 个子集，按选/不选决策顺序生成

    auto combinations = solution.combinationsTemplate(4, 2);
    print2D(combinations); // 期望输出：[1,2] [1,3] [1,4] [2,3] [2,4] [3,4]

    auto permutations = solution.permutationsTemplate(nums);
    print2D(permutations); // 期望输出：6 个排列

    return 0;
}
