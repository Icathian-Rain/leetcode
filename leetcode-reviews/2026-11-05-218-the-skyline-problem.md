# 题解点评 - 218. The Skyline Problem

## 基本信息

- 日期：2026-11-05
- 主题：第 9 周第 6 天，窗口与有效候选维护
- 难度：困难
- 本次结果：通过（用户确认已通过测试）；按用户要求，本次未编译、运行、对拍或重复验证答案。
- 对应源码：[src/218.the-skyline-problem.cpp](../src/218.the-skyline-problem.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/the-skyline-problem/)；思路与复杂度分析基于本地源码。
- 查询日期：2026-11-05
- 关键约束：建筑左右端点满足 left<right，高度为正；同高或相接建筑均需按题意合并输出。

## 用户思路概述

1. 每座建筑拆成两个事件：左端点配负高度表示进入，右端点配正高度表示离开。
2. 对全部事件排序，用 `multiset` 保存当前有效建筑的高度及一个地面高度 0。
3. 一次处理完同一横坐标的全部事件，再读取集合中的最大高度。
4. 若当前高度与上一段不同，就记录关键点；否则不输出，从而合并连续等高段。

## 用户解法复杂度

- 设建筑数为 `n`，事件数为 `2n`。时间 `O(n log n)`，来自事件排序及每座建筑一次插入、一次删除。
- 辅助空间 `O(n)`，保存事件和有效高度；答案至多 `O(n)` 个关键点，含输出总空间仍为 `O(n)`。
- 读取 `*s.rbegin()` 为 `O(1)`；删除包含 `find` 的查找开销为 `O(log n)`。

## 用户代码注释版

> 保留用户原解法结构，只在文档中增加说明，不将这些注释写回原实现。

```cpp
using pii = pair<int, int>;
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pii> events;
        for(auto &b: buildings) {
            events.push_back({b[0], -b[2]}); // 负高度标记建筑进入。
            events.push_back({b[1], b[2]}); // 正高度标记建筑离开。
        }
        sort(events.begin(), events.end());
        multiset<int> s;
        s.insert(0); // 地面哨兵，所有建筑离开后仍可读到高度 0。
        vector<vector<int>> ans;
        int pre = 0, n = events.size();
        for(int i=0; i<n;) {
            int x=events[i].first;
            // 处理同一位置横坐标的点
            while(i<n && events[i].first == x) {
                int h=events[i].second;
                if(h<0) {
                    s.insert(-h);
                } else {
                    s.erase(s.find(h)); // 同高建筑可能有多座，只删除一个副本。
                }
                i++;
            }
            int cur = *s.rbegin(); // 同坐标整组更新后才读取高度。
            if(cur != pre) { // 只有高度变化才产生关键点，合并连续等高段。
                ans.push_back({x, cur});
                pre = cur;
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 复盘重点 |
| --- | --- | --- | --- |
| 同坐标事件 | 先批量更新，再读取一次高度 | 不产生零宽的中间关键点 | 解释同点“进入、离开”的整体含义 |
| 同高建筑 | multiset 保存多个同值，按迭代器删除一个 | 一座离开不会误删其他同高建筑 | 不可改成 `erase(height)` 删除全部副本 |
| 地面状态 | 集合初始包含 0 | 无建筑覆盖时自然读到地面高度 | 哨兵不会收到删除事件，因为建筑高度为正 |
| 关键点压缩 | 高度与 pre 不同才输出 | 满足连续等高段合并要求 | 比较整组事件更新后的最终高度 |
| 候选保留 | 被较高建筑遮住的建筑仍在集合中 | 最高建筑离开后可以恢复次高值 | 高度更大并不保证更晚结束，不能照搬单调队列淘汰 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户扫描线 | 同点分组清晰，精确增删同高副本 | 需事件排序，树容器有常数开销 | 静态区间共同形成上轮廓 |
| 推荐扫描线 | 相同算法，状态命名便于证明 | 没有渐近提速 | 稳定维护有效高度与关键点 |

## 可能的最优解法

1. 保留用户的扫描线与有序多重集合方案，这是通用比较模型下的标准最优级方案。
2. 将每个建筑视为 `[left,right)` 的有效覆盖区间，在左边界加入高度，在右边界删除一个副本。
3. 不变量：处理完整个横坐标事件组后，集合中的非零高度恰好对应该位置及右侧紧邻区间仍有效的建筑。
4. 以最大高度作为当前轮廓，与上次输出高度比较，仅在变化时追加关键点。
5. 事件使用 pair 默认排序很方便，但由于已经按横坐标分组，输出正确性的核心是整组处理后再查询，无须依靠同坐标内部高度次序产生答案。

- 推荐时间 `O(n log n)`，辅助空间及含输出总空间均为 `O(n)`。
- 与用户方案复杂度相同，主要补清命名、预留事件容量和不变量。堆延迟删除、分治合并也可行，本次不展开。

### 推荐 C++20 提交代码

```cpp
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> events;
        events.reserve(buildings.size() * 2);
        for (const auto& building : buildings) {
            events.push_back({building[0], -building[2]});
            events.push_back({building[1], building[2]});
        }
        sort(events.begin(), events.end());
        multiset<int> activeHeights{0}; // 地面哨兵保证可随时读取最大高度。
        vector<vector<int>> result;
        int previousHeight = 0;
        for (size_t i = 0; i < events.size();) {
            int x = events[i].first;
            // 同一横坐标的增删全部完成后，再输出该位置的最终高度。
            while (i < events.size() && events[i].first == x) {
                int height = events[i].second;
                if (height < 0) activeHeights.insert(-height);
                else activeHeights.erase(activeHeights.find(height));
                ++i;
            }
            int currentHeight = *activeHeights.rbegin();
            if (currentHeight != previousHeight) {
                result.push_back({x, currentHeight});
                previousHeight = currentHeight;
            }
        }
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 事件语义 | 负高度进入，正高度离开 | 相同 | 名称明确事件与有效高度 |
| 输出时机 | 同 x 整组处理完再输出 | 相同 | 已处理核心边界 |
| 重复高度 | 删除一个迭代器 | 相同 | 保留副本计数 |
| 时间 / 空间 | `O(n log n)` / `O(n)` | 相同 | reserve 只减少分配常数 |

## 下一步建议

可以进入第 7 天。重点手推同坐标建筑交接、同高重叠和中间地面这三类事件含义，说明为什么低建筑不能被永久丢弃。

## 后续安排

继续周计划第 7 天既定题单：658（旧题热身）、451（核心）、895（拔高）。目标分别为方案取舍、输出规则理解和动态操作整合；具体顺序与难度见周计划，不另扩展题单。

## 代码同步

- 私有函数：`getSkylineOpt`，位于原 `class Solution` 的 `public:` 之前。
- 已新增推荐函数，原公开提交函数及用户实现逐字保留；默认提交入口仍调用原实现。
- 本次仅整理源码与文档，不提供新增版本的运行验证结论。
