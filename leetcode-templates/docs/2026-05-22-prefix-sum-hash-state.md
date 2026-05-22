# 算法模板 - 前缀和哈希状态

## 基本信息

- 日期：2026-05-22
- 主题：第 1 周数组与哈希
- 目标：把连续子数组问题转成“当前前缀需要匹配哪个旧前缀”
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-prefix-sum-hash-state.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-prefix-sum-hash-state.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目询问连续子数组的和、余数、长度或是否存在
- 暴力枚举所有左右端点会到 `O(n^2)`
- 当前子数组信息可以由两个前缀状态相减得到

## 核心思路

1. 扫描数组时维护当前前缀状态 `prefix`。
2. 对于目标和，查找旧前缀 `prefix - target` 出现过几次。
3. 对于整除问题，把前缀和压成余数，并规范化负数取模。
4. 计数题保存出现次数；长度题通常保存最早下标；存在性题保存可验证长度的下标。

## 关键边界

- 初始状态必须放入哈希表，例如前缀和 `0` 已出现 1 次
- 负数取模要写成 `(x % k + k) % k`
- 长度约束题不能只看状态相同，还要检查下标差
- 计数题更新答案应发生在记录当前前缀之前，避免把空子数组算进去

## 复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`，或余数状态下 `O(k)`

## 模板代码

```cpp
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
```

## 运行样例

### 样例 1

- 输入：`nums = [1, 1, 1], target = 2`
- 输出：`2`
- 说明：当前前缀为 `2` 和 `3` 时，分别能匹配旧前缀 `0` 和 `1`。

### 样例 2

- 输入：`nums = [4, 5, 0, -2, -3, 1], k = 5`
- 输出：`7`
- 说明：相同余数的两个前缀之间，子数组和一定能被 `5` 整除。

## 套用提醒

- “求数量”保存次数，“求最长/最短”保存下标，这个选择比代码长相更重要。
- 前缀状态不一定是和，也可以是余数、奇偶差、字符计数差等。
- 如果状态需要多个维度，优先定义结构化 key 或明确编码规则。
