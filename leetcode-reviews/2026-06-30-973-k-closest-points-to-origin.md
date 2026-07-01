# 题解点评 - 973. K Closest Points to Origin

## 基本信息

- 日期：2026-06-30
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/973.k-closest-points-to-origin.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-06-30，信息待官方页面复核

## 用户思路概述

1. 遍历每个点，计算它到原点的平方距离 `x * x + y * y`。
2. 把 `{distance, index}` 放入堆中，用下标回到原始点坐标。
3. 堆大小超过 `k` 时弹出堆顶，使堆里只保留当前距离最近的 `k` 个点。
4. 最后把堆中保存的下标转换回坐标，组成答案。

## 用户解法复杂度

- 时间复杂度：`O(n log k)`
- 空间复杂度：`O(k)`
- 复杂度来源：每个点最多入堆一次，堆大小被控制在 `k`。

## 用户代码注释版

```cpp
using pii = pair<int, int>;
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n=points.size();
        auto cmp = [](const pii& a, const pii& b) -> bool{
            return a.first < b.first; // 距离大的 pair 会成为堆顶，方便超过 k 时淘汰。
        };

        priority_queue<pii, vector<pii>, decltype(cmp)> pq;
        for(int i=0; i<n; i++) {
            int x = points[i][0], y=points[i][1];
            int distance = x*x+y*y; // 用平方距离即可比较远近，不需要开方。
            pq.push({distance, i});
            while(pq.size() > k) {
                pq.pop(); // 弹出当前保留集合中最远的点。
            }
        }

        vector<vector<int>> ans;
        while(!pq.empty()) {
            auto [_, idx] = pq.top(); pq.pop();
            ans.push_back({points[idx][0], points[idx][1]});
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 优先级建模 | 用平方距离作为比较依据 | 正确避免了浮点数和开方 | 继续保持“只比较大小，不必算真实距离”的习惯 |
| 固定大小堆 | 超过 `k` 就弹出最远点 | 正确命中 Top K 模式 | 复盘时明确堆顶是“最差保留候选” |
| 答案顺序 | 直接输出堆中点 | 本题允许任意顺序，因此可行 | 遇到要求排序的 Top K 题时，要额外处理输出顺序 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 不需要全量排序，堆大小控制清晰 | 自定义比较器方向需要解释清楚 | `k` 小于 `n`，只关心最近 `k` 个结果 |
| 推荐最优解 | 同样使用固定大小堆，写法更直接 | 理论上也可用快速选择达到平均 `O(n)` | 本周堆主题下最适合迁移的稳定写法 |

## 最优解法

1. 对每个点计算平方距离。
2. 用大根堆保留当前距离最小的 `k` 个点。
3. 当堆大小超过 `k`，弹出距离最大的点。
4. 遍历结束后，堆中剩下的就是答案集合。

- 最优时间复杂度：堆方案 `O(n log k)`；快速选择平均可达 `O(n)`
- 最优空间复杂度：堆方案 `O(k)`

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, int>> heap;
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0], y = points[i][1];
            int distance = x * x + y * y;
            heap.push({distance, i});
            // 保留当前距离最小的 k 个点，堆顶是其中最远的候选。
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<vector<int>> ans;
        while (!heap.empty()) {
            int index = heap.top().second;
            heap.pop();
            ans.push_back(points[index]);
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `{distance, index}` | `{distance, index}` | 当前定义清晰 |
| 更新逻辑 | 入堆后超过 `k` 就弹出 | 同样逻辑 | 可把 `while` 简化成 `if`，因为每次只新增一个元素 |
| 边界处理 | 依赖题目保证 `k` 合法 | 同样依赖题目保证 | 注意本题答案顺序不要求固定 |
| 复杂度 | `O(n log k)` | `O(n log k)` | 能进一步对比全量排序 `O(n log n)` |

## 下一步建议

做跟练题。你已经能把数值 Top K 迁移到距离 Top K，下一步重点是多关键字比较。

## 后续练习

1. `692. Top K Frequent Words` - 在频次之外加入字典序规则。
2. `658. Find K Closest Elements` - 继续比较不同方案下的 Top K 取舍。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/973.k-closest-points-to-origin.cpp`
- 新函数名：`kClosestOpt`
- 保留用户原实现：是。
