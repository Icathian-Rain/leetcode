# 算法模板 - 单调队列窗口最大值

## 基本信息

- 日期：2026-05-22
- 主题：第 3 周栈与队列
- 目标：在滑动窗口中维护仍可能成为最大值的候选下标
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-monotonic-queue-window-maximum.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-monotonic-queue-window-maximum.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目要求每个固定窗口内的最大值或最小值
- 窗口右移时，旧下标会过期，新元素可能覆盖一批旧候选
- 需要比堆更直接地处理过期下标

## 核心思路

1. 队列里保存下标，队首始终是当前窗口最大值的下标。
2. 每次处理新下标前，先清理已经离开窗口的队首。
3. 新值进入前，从队尾删除不可能再成为最大值的候选。
4. 窗口形成后，读取队首对应的值作为当前答案。

## 关键边界

- 过期条件是 `index <= right - k`
- 维护最大值时，队尾小于等于当前值都可以弹出；维护最小值则反过来
- `k == 1` 时每个元素自己就是答案
- 保存值也能做部分题，但保存下标更利于判断过期和迁移

## 复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(k)`

## 模板代码

```cpp
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
```

## 运行样例

### 样例 1

- 输入：`nums = [1,3,-1,-3,5,3,6,7], k = 3`
- 输出：`[3,3,5,5,6,7]`
- 说明：队首下标始终指向当前窗口最大值。

### 样例 2

- 输入：`nums = [4,2,12], k = 1`
- 输出：`[4,2,12]`
- 说明：每个窗口只有一个元素，过期清理和入队仍然自然成立。

## 套用提醒

- 先清理过期，再维护单调性，最后入队和记录答案，这个顺序最稳。
- 如果题目要求最小值，把第二个 `while` 的比较符改成 `>=`。
- 单调队列是“候选集合”，不是保存窗口全部元素。
