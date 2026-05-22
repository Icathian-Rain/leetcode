# 算法模板 - Binary Search First True

## 基本信息

- 日期：2026-05-22
- 主题：二分查找
- 目标：把一类问题统一转成 `false...false true...true`，并找到第一个 `true`
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-binary-search-first-true.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-binary-search-first-true.cpp`

## 适用信号

- 题目本质是在找“第一个满足条件的位置”
- 当前位置之前都不合法，某个位置开始全部合法，存在单调分界线
- 题目可以改写成 `check(index)`，并且 `false -> true` 只会发生一次

## 核心思路

1. 把问题抽象成长度为 `n` 的搜索区间，区间内满足 `false...false true...true`。
2. 使用左闭右开区间 `[left, right)`，这样答案可以自然落在 `n`，表示“不存在 true”。
3. 若 `check(middle)` 为 `true`，说明 `middle` 可能就是第一个 `true`，保留它并收缩右边界。
4. 若 `check(middle)` 为 `false`，说明 `middle` 和它左侧都不可能是答案，直接推进左边界。
5. 循环结束时返回 `left`；若 `left == n`，说明整个区间都没有 `true`。

## 关键边界

- `n == 0` 时，循环不会进入，直接返回 `0`
- `left == n` 表示不存在 `true`，调用方要决定这是报错、返回 `-1`，还是映射到别的答案
- `check(middle) == true` 时必须写 `right = middle`，因为 `middle` 仍可能是第一个 `true`
- `check(middle) == false` 时必须写 `left = middle + 1`，因为 `middle` 已经确认不能作为答案

## 复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`，不计 `check` 闭包本身捕获的外部数据

## 模板代码

```cpp
class Solution {
private:
    int firstTrue(int n, const function<bool(int)>& check) {
        int left = 0;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (check(middle)) {
                right = middle; // middle 可能是第一个 true，保留。
            } else {
                left = middle + 1; // middle 是 false，连同左侧一起排除。
            }
        }

        return left; // left == n 表示不存在 true。
    }

public:
    int searchInsert(vector<int>& nums, int target) {
        return firstTrue(static_cast<int>(nums.size()), [&](int index) {
            return nums[index] >= target;
        });
    }

    char nextGreatestLetter(vector<char>& letters, char target) {
        int index = firstTrue(static_cast<int>(letters.size()), [&](int i) {
            return letters[i] > target;
        });

        return index == static_cast<int>(letters.size()) ? letters[0] : letters[index];
    }
};
```

## 运行样例

### 样例 1

- 输入：`nums = [1, 3, 5, 6], target = 5`
- 输出：`2`
- 说明：把条件写成 `nums[index] >= target`，第一个 `true` 出现在下标 `2`

### 样例 2

- 输入：`letters = ['c', 'f', 'j'], target = 'j'`
- 输出：`0`
- 说明：把条件写成 `letters[index] > target`，整个区间都没有 `true`，返回 `n` 后再按题意回绕到 `0`

## 套用提醒

- 当题目是在问“第一个大于等于”“第一个大于”“第一个满足限制”的位置时，优先套这个模板
- 真正需要改的通常不是二分骨架，而是 `check(index)` 的定义和 `left == n` 之后的返回语义
- 如果你要把它沉淀成长期复用的代码，建议像这里一样把 `firstTrue` 收进 `class Solution` 的私有辅助函数，再给具体题目暴露公开接口
- 它和“查找具体值”的普通二分最容易混淆的地方是：这里目标不是命中某个值，而是定位分界线
