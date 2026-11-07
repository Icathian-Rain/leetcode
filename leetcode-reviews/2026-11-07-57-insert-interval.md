# 题解点评 - 57. Insert Interval

## 基本信息

- 日期：2026-11-07
- 主题：第 10 周第 1 天，区间合并入口
- 难度：中等（本地计划记录）
- 本次结果：通过（用户确认题解均已测试通过）。
- 对应源码：[57.insert-interval.cpp](../src/57.insert-interval.cpp)
- 资料来源：本地源码、第 10 周计划，以及 [LeetCode 官方题目搜索摘要](https://leetcode.com/problems/insert-interval/)。
- 查询日期：2026-11-07。中国版及国际版页面正文访问受限；搜索摘要确认原列表按起点有序、互不重叠，以及共享端点视为相交，完整数值约束未重新联网校准。

## 用户思路概述

1. 将严格位于新区间左侧的原区间直接加入答案。
2. 用新区间初始化 `[l,r]`，依次吸收与当前范围相交的区间，并扩张左右端点。
3. 加入合并完成的当前段。
4. 将剩余右侧区间直接追加到答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`。三个循环共用只增不减的 `i`，每个原区间只处理一次。
- 辅助空间：`O(1)`，不计返回结果。
- 含返回结果的总空间：最坏 `O(n)`；答案最多包含 `n+1` 段。输入区间和新区间均未被修改。

## 用户代码注释版

> 以下只解释原解，不把注释写回源码中的原公开函数。

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n=intervals.size();
        vector<vector<int>> ans;
        int i=0;
        // 完全位于左侧：必须严格小于，端点相等仍应合并。
        while(i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }

        int l=newInterval[0], r = newInterval[1];
        // 比较最新的 r；当前段吸收一个区间后，覆盖范围可能变大。
        while(i<n && intervals[i][0] <= r) {
            l = min(l, intervals[i][0]);
            r = max(r, intervals[i][1]);
            i++;
        }
        ans.push_back({l, r}); // 即使原列表为空，也会加入新区间。
        // 停止合并后，后续区间全部严格位于当前段右侧。
        while(i<n) {
            ans.push_back(intervals[i]);
            i++;
        }
        return ans;


    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 使用输入保证 | 没有重新排序，直接单向扫描 | 达到线性时间，算法选择准确 | 说明有序且互不重叠两个前提都在发挥作用 |
| 三段划分 | 左侧复制、中间合并、右侧复制 | 分工清楚，控制流稳定 | 保持当前结构即可 |
| 端点相等 | 左侧条件 `<`，合并条件 `<=` | 闭区间相交处理正确 | 用 `[1,2]` 插入 `[2,3]` 检查比较符含义 |
| 动态边界 | 更新 `l,r` 后继续比较当前 `r` | 维护了正确的合并状态 | 不要改成始终比较原始新区间的右端点 |
| 空列表与两端插入 | 各循环检查 `i<n`，始终输出合并段 | 自然覆盖空列表、头插、尾插和全覆盖 | 本次没有发现需要修复的正确性问题 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 时间最优，常数辅助空间，不修改输入，三段语义清楚 | 依赖题目提供的有序及互不重叠保证 | 本题标准方案 |
| 推荐最优解 | 保留相同结构，使用完整变量名并标注关键边界 | 算法与复杂度没有提升 | 作为复盘参考实现 |

## 可能的最优解法

1. 继续使用原解的三段式扫描，无需替换算法。
2. 第一阶段不变量：已输出区间全部严格位于新区间左侧，可以定稿。
3. 第二阶段不变量：`[left,right]` 覆盖新区间及已吸收的全部相交区间；剩余区间按左端点有序，因此遇到起点大于 `right` 就可结束合并。
4. 合并段输出后，剩余原区间既位于其右侧，又彼此不重叠，直接复制即可。

- 时间复杂度：`O(n)`；最坏需要输出线性数量的区间，已达最优。
- 辅助空间：`O(1)`，不计结果；含结果最坏 `O(n)`。
- 先把新区间加入再统一排序合并也能求解，但会引入不必要的 `O(n log n)` 排序，本题选择直接扫描。

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        const int n = static_cast<int>(intervals.size());
        int index = 0;
        // 第一段严格位于新区间左侧，端点相等必须留给合并段。
        while (index < n && intervals[index][1] < newInterval[0]) {
            result.push_back(intervals[index++]);
        }

        int left = newInterval[0];
        int right = newInterval[1];
        // right 随合并扩张，每次都与最新右边界比较。
        while (index < n && intervals[index][0] <= right) {
            left = min(left, intervals[index][0]);
            right = max(right, intervals[index][1]);
            ++index;
        }
        result.push_back({left, right});

        // 原列表有序且互不重叠，剩余区间可直接复制。
        while (index < n) {
            result.push_back(intervals[index++]);
        }
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `i,l,r` | `index,left,right` | 原状态正确，完整名称便于复盘 |
| 更新逻辑 | 三段扫描 | 相同 | 无需增加分支或重排输入 |
| 边界 | 支持空列表、端点相等、两端插入和全覆盖 | 相同 | 解释严格分离与重叠条件的对应关系 |
| 时间复杂度 | `O(n)` | `O(n)` | 已达到最优 |
| 辅助空间 | `O(1)`，不计结果 | 相同 | 三个顺序循环共用同一指针，不是三重嵌套 |
| 含结果空间 | `O(n)` | `O(n)` | 与辅助空间区分 |

## 下一步建议

可以进入下一阶段。用原列表 `[[1,2],[3,5],[6,7],[8,10],[12,16]]`、新区间 `[4,8]` 口述为什么输出 `[[1,2],[3,10],[12,16]]`，重点说明端点 8 的相交判定和左右边界更新。

## 后续安排

与今日 56 对照输入前提；986 可回顾历史点评。下一步沿用第 2 天的 435、452、1288，不额外增加题单。

## 代码同步

- 已在原 `class Solution` 的 `public:` 前新增私有函数 `insertOpt`，含关键中文注释。
- 原公开 `insert` 及其实现保持不变，默认提交入口不变。
- 原解通过状态来自用户确认；新增函数另做 C++20 编译检查，不将其记为 LeetCode 提交通过。
