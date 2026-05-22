# 算法模板 - 可变窗口最多 K 类

## 基本信息

- 日期：2026-05-22
- 主题：第 2 周双指针与滑动窗口
- 目标：维护一个满足“最多 K 类/次/成本”的最长合法窗口，并支持恰好 K 的差分计数
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-variable-window-at-most.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-variable-window-at-most.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目围绕连续子数组或子串，限制窗口内最多出现 `K` 种状态
- 右端扩张后，如果窗口非法，可以通过左端单调右移恢复合法
- “恰好 K”可以转成“最多 K - 最多 K - 1”

## 核心思路

1. 右指针逐步纳入元素，并更新窗口频次。
2. 当窗口状态超过限制时，持续移出左端直到重新合法。
3. 合法后，窗口内以当前右端结尾的所有起点都可贡献答案。
4. 恰好 `K` 的数量用 `atMost(K) - atMost(K - 1)` 得到。

## 关键边界

- `K < 0` 时，最多 K 个不同元素的窗口不存在，返回 `0`
- 频次归零后必须删除对应 key，否则不同种类数会偏大
- 最长窗口在收缩后更新；最短覆盖窗口通常在收缩前更新，别混用
- 计数贡献是 `right - left + 1`，不是只加 `1`

## 复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(k)` 到 `O(n)`，取决于窗口中可能出现多少种状态

## 模板代码

```cpp
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
```

## 运行样例

### 样例 1

- 输入：`nums = [1, 2, 1, 2, 3], k = 2`
- 输出：`7`
- 说明：恰好 2 类的子数组数量等于最多 2 类数量减去最多 1 类数量。

### 样例 2

- 输入：`nums = [1, 2, 1, 3, 4], k = 2`
- 输出：`3`
- 说明：最长合法窗口可以是 `[1, 2, 1]`。

## 套用提醒

- 这个模板适合“最多 K”与“恰好 K 的数量”，不适合最短覆盖需求。
- 如果限制不是不同种类，而是零的数量、乘积、替换成本，只需要替换窗口状态和非法条件。
- 每次写完都检查：加入、收缩、记录答案三个动作的顺序是否符合题目目标。
