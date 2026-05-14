# 题解点评 - 239. Sliding Window Maximum

## 基本信息

- 日期：2026-05-14
- 主题：栈与队列 - 队列窗口与模拟面试
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/239.sliding-window-maximum.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 在 `maxSlidingWindow` 内定义一个辅助队列 `MyQueue`。
2. `push(val)` 时，弹出队尾所有小于 `val` 的值，让队列保持从大到小。
3. `pop(val)` 时，如果当前窗口移出的值等于队首最大值，就弹出队首。
4. `front()` 返回当前队首，也就是窗口最大值。
5. 先放入前 `k` 个元素得到第一个窗口最大值，再每次加入新元素、移出旧元素并记录最大值。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(k)`
- 复杂度来源：每个元素最多进入和离开辅助队列一次；队列只保存窗口候选最大值。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        class MyQueue {
            private:
                deque<int> q; // 保存候选值，队首最大。
            public:
                void push(int val) {
                    while (!q.empty() && q.back() < val)
                    {
                        q.pop_back(); // 比新值小的候选不可能再成为最大值。
                    }
                    q.push_back(val);
                }
                void pop(int val) {
                    if(q.front() == val) {
                        q.pop_front(); // 移出窗口的值如果正是最大值，才需要同步弹出。
                    }
                }
                int front() {
                    return q.front();
                }
        };

        MyQueue q;
        vector<int> ans;
        for(int i=0;i<k;i++) {
            q.push(nums[i]);
        }
        ans.push_back(q.front());
        for(int i=k; i<nums.size(); i++) {
            q.push(nums[i]);
            q.pop(nums[i-k]);
            ans.push_back(q.front());
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 候选维护 | 用单调队列保存窗口最大值候选。 | 正确命中本题核心。 | 复盘时说清队列中不是窗口全部元素，而是仍可能成为最大值的元素。 |
| 值队列写法 | 通过 `pop(nums[i-k])` 同步过期值。 | 在常见解法中可行，但依赖值与队首比较来间接处理过期。 | 推荐掌握下标队列，过期判断更直接。 |
| 更新顺序 | 当前先 `push` 新值，再 `pop` 旧值。 | 对值队列通常仍可工作，但解释成本更高。 | 下标队列建议先清过期，再维护单调性，再记录答案。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 代码简洁，体现了单调队列思想。 | 保存值不保存下标，过期窗口语义不够显式。 | 可以提交，但复盘时要补下标版本。 |
| 推荐最优解 | 保存下标，队首是否过期一眼可见。 | 代码稍长。 | 更适合面试和迁移到其他窗口题。 |

## 最优解法

1. 用双端队列保存候选最大值的下标。
2. 每次先移除队首中过期的下标。
3. 再从队尾移除所有值小于等于当前值的下标。
4. 当前下标入队。
5. 当窗口形成后，队首下标对应的值就是当前窗口最大值。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(k)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> indexes;
        vector<int> ans;

        for (int i = 0; i < (int)nums.size(); ++i) {
            while (!indexes.empty() && indexes.front() <= i - k) {
                indexes.pop_front();
            }
            while (!indexes.empty() && nums[indexes.back()] <= nums[i]) {
                indexes.pop_back();
            }
            indexes.push_back(i);

            if (i >= k - 1) {
                // 队首下标始终对应当前窗口最大值。
                ans.push_back(nums[indexes.front()]);
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 队列保存候选值。 | 队列保存候选下标。 | 下标能同时表达值和是否过期。 |
| 更新逻辑 | 加新值后按旧值尝试弹队首。 | 先删过期下标，再维护单调性。 | 推荐下标模板，边界更直观。 |
| 边界处理 | `k=1`、重复最大值通常可处理。 | 重复值和过期窗口都显式处理。 | 下标版本更好证明。 |
| 复杂度 | `O(n)` / `O(k)` | `O(n)` / `O(k)` | 已达到最优。 |

## 下一步建议

建议用下标队列重写一遍。第 3 周收束时，把这题和 `739` 放一起复盘：一个回填等待天数，一个读取窗口最大值，本质都依赖下标状态。

## 后续练习

1. `862. Shortest Subarray with Sum at Least K` - 更高阶的单调队列前缀和题。
2. `1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit` - 双队列维护窗口最大最小值。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/239.sliding-window-maximum.cpp`
- 新函数名：`maxSlidingWindowOpt`
- 保留用户原实现：是
