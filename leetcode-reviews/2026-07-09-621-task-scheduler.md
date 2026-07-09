# 题解点评 - 621. Task Scheduler

## 基本信息

- 日期：2026-07-09
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/621.task-scheduler.cpp`
- 资料来源：LeetCode 中国官方题目页标题与本地周计划；实现点评基于本地源码
- 查询日期：2026-07-09

## 用户思路概述

1. 统计 26 种任务各自出现次数。
2. 找到最高频任务出现次数 `maxCnt`。
3. 统计有多少种任务都达到了最高频，记为 `maxKinds`。
4. 用 `(maxCnt - 1) * (n + 1) + maxKinds` 计算由最高频任务撑开的最短框架。
5. 返回任务总数和框架长度中的较大值。

## 用户解法复杂度

- 时间复杂度：`O(T + 26)`，其中 `T` 是任务数量。
- 空间复杂度：`O(26)`，固定字符集下可视为 `O(1)`。
- 复杂度来源：一次统计任务频次，随后只扫描固定长度的频次数组。

## 用户代码注释版

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26, 0);
        for (char ch : tasks) {
            cnt[ch - 'A']++; // 统计每种任务出现次数。
        }

        int maxCnt = 0;
        for (int x : cnt) {
            maxCnt = max(maxCnt, x); // 找到最高频任务次数。
        }

        int maxKinds = 0;
        for (int x : cnt) {
            if (x == maxCnt) {
                maxKinds++; // 多个最高频任务会共同占据最后一组位置。
            }
        }

        int frame = (maxCnt - 1) * (n + 1) + maxKinds;
        return max((int)tasks.size(), frame); // 任务足够多时会填满所有空闲槽。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 最高频框架 | 正确使用最高频任务撑开最短长度 | 避免了复杂模拟，复杂度很稳 | 复盘时画出 `maxCnt - 1` 个完整间隔块 |
| 多个最高频任务 | 统计 `maxKinds` | 正确覆盖 `AABB` 这类并列最高频 | 记住最后一组不是只放一个任务 |
| 填槽情况 | 使用 `max(tasks.size(), frame)` | 覆盖其他任务足够多时无 idle 的情况 | 这是本题最容易漏的一步 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 公式直接，时间空间都优 | 不输出具体调度序列，只返回最短时间 | 本题只要求最短间隔数 |
| 堆模拟 | 更贴近“每次选当前最高频任务”的直觉 | 实现更长，还要处理冷却队列 | 需要构造具体序列或规则更复杂时 |

## 最优解法

1. 统计所有任务频次。
2. 找到最高频次数 `maxFreq`。
3. 统计达到最高频的任务种类数 `maxKinds`。
4. 由最高频任务构造最短框架 `(maxFreq - 1) * (n + 1) + maxKinds`。
5. 答案是框架长度和任务总数的较大值。

- 最优时间复杂度：`O(T + 26)`
- 最优空间复杂度：`O(26)`

### 最优解代码

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            ++freq[task - 'A'];
        }

        int maxFreq = 0;
        for (int count : freq) {
            maxFreq = max(maxFreq, count);
        }

        int maxKinds = 0;
        for (int count : freq) {
            if (count == maxFreq) {
                ++maxKinds;
            }
        }

        // 最高频任务决定最少框架长度；任务足够多时，答案就是任务总数。
        int frame = (maxFreq - 1) * (n + 1) + maxKinds;
        return max(static_cast<int>(tasks.size()), frame);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt`、`maxCnt`、`maxKinds` | `freq`、`maxFreq`、`maxKinds` | 当前清晰，命名可更统一 |
| 更新逻辑 | 两次扫描频次数组 | 同样逻辑 | 当前稳定 |
| 边界处理 | `n = 0` 时公式也能覆盖 | 同样覆盖 | 可口述无冷却时答案等于任务数 |
| 复杂度 | `O(T)` | `O(T)` | 已经是最优级别 |

## 下一步建议

做跟练题。你已经掌握“只求长度时用频次公式”的入口，下一步要练需要真正构造序列的相邻限制题。

## 后续练习

1. `767. Reorganize String` - 从只求长度切换到构造合法字符串。
2. `358. Rearrange String k Distance Apart` - 在更严格距离约束下维护暂时不可用的候选。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/621.task-scheduler.cpp`
- 新函数名：`leastIntervalOpt`
- 保留用户原实现：是。
