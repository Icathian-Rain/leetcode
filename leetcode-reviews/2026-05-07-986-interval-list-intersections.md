# 题解点评 - 986. Interval List Intersections

## 基本信息

- 日期：2026-05-07
- 主题：双指针与滑动窗口 - 综合迁移与模拟面试
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/986.interval-list-intersections.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `a` 和 `b` 分别指向两个区间列表中的当前区间。
2. 每轮取出两个区间 `[l1, r1]` 和 `[l2, r2]`，先判断是否完全错开。
3. 如果两个区间有交集，就根据较小的右端点构造交集，并推进这个右端点较小的区间。
4. 任一列表遍历结束后，所有可能交集已经处理完，返回答案。

## 用户解法复杂度

- 时间复杂度：`O(m + n)`
- 空间复杂度：`O(1)`，不计返回结果
- 复杂度来源：两个指针都只会向右移动，每个区间最多被处理一次。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int len1=firstList.size(), len2=secondList.size();
        int a=0, b=0; // a、b 分别指向两个列表当前待比较的区间。
        vector<vector<int>> ans;
        while((a<len1) && (b<len2)) {
            int l1=firstList[a][0], r1=firstList[a][1];
            int l2=secondList[b][0], r2=secondList[b][1];
            if(r1 < l2) {
                // 第一个区间在第二个区间左侧，已经不可能和当前或后续第二列表区间相交。
                a++;
            } else if(r2 < l1) {
                // 第二个区间在第一个区间左侧，推进第二列表。
                b++;
            } else if(r1 >= l2 && r1 <= r2) {
                // 有交集，且第一个区间右端点更早结束。
                ans.push_back({max(l1, l2), r1});
                a++;
            } else if(r2 >= l1 && r2 <= r1) {
                // 有交集，且第二个区间右端点更早结束。
                ans.push_back({max(l1, l2), r2});
                b++;
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 交集判定 | 能覆盖错开和相交两类情况。 | 正确性稳定，可以通过典型样例。 | 可统一成 `left=max(starts)`、`right=min(ends)`，减少分支。 |
| 指针推进依据 | 相交时推进右端点更小的区间。 | 抓住了区间列表题的核心单调性。 | 复盘时重点说清：较早结束的区间不可能再和对方后续区间相交。 |
| 代码表达 | 分支按具体位置关系展开。 | 可读，但条件略多，面试口述时容易漏一个覆盖场景。 | 推荐把“是否相交”和“推进谁”拆成两个稳定步骤。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 复杂度最优，推进逻辑正确。 | 相交分支写得偏细，复盘成本略高。 | 适合本题，可以通过整理表达提升稳定性。 |
| 推荐最优解 | 交集计算统一，推进规则统一。 | 本质算法相同，只是写法更紧。 | 适合直接作为区间列表模板。 |

## 最优解法

1. 同时扫描两个已经排序且互不重叠的区间列表。
2. 当前两个区间的交集左端点是两个左端点的较大值，右端点是两个右端点的较小值。
3. 如果 `left <= right`，说明存在交集，加入答案。
4. 推进右端点更小的区间，因为它不可能再和对方后续区间产生交集。

- 最优时间复杂度：`O(m + n)`
- 最优空间复杂度：`O(1)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> ans;
        int first = 0;
        int second = 0;

        while (first < (int)firstList.size() && second < (int)secondList.size()) {
            int left = max(firstList[first][0], secondList[second][0]);
            int right = min(firstList[first][1], secondList[second][1]);
            if (left <= right) {
                ans.push_back({left, right});
            }

            // 右端点更早结束的区间，后面再也不会参与新的交集。
            if (firstList[first][1] < secondList[second][1]) {
                ++first;
            } else {
                ++second;
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 两个列表指针 `a`、`b`。 | 同样使用两个列表指针。 | 当前状态定义正确。 |
| 更新逻辑 | 分四种关系判断交集和推进。 | 先统一计算交集，再统一推进较早结束区间。 | 把复杂分支压成两个判断。 |
| 边界处理 | 空列表可自然返回空答案。 | 同样自然处理空列表。 | 已覆盖关键边界。 |
| 复杂度 | `O(m+n)` / `O(1)` | `O(m+n)` / `O(1)` | 已达到最优。 |

## 下一步建议

进入下一题即可。复盘时用一句话固定模板：两个有序区间列表同时扫描，先看当前交集，再丢掉右端点更小的区间。

## 后续练习

1. `56. Merge Intervals` - 练习同类区间关系，但从双列表推进切换到单列表合并。
2. `57. Insert Interval` - 继续强化区间交叠、合并和边界推进。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/986.interval-list-intersections.cpp`
- 新函数名：`intervalIntersectionOpt`
- 保留用户原实现：是
