# 题解点评 - 295. Find Median from Data Stream

## 基本信息

- 日期：2026-11-04
- 主题：第 9 周第 5 天，堆与优先队列 / 动态有序分段
- 难度：困难
- 本次结果：本地对拍通过；未读取到 LeetCode 提交结果，不标记官方 AC。
- 对应源码：[src/295.find-median-from-data-stream.cpp](../src/295.find-median-from-data-stream.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/find-median-from-data-stream/)；算法分析与验证基于本地源码。
- 查询日期：2026-11-04
- 约束核对：查询前至少有一个元素，数值在 ±10^5 内。

## 用户思路概述

1. `low` 用大根堆保存较小一半，`high` 用小根堆保存较大一半。
2. 新数先放入 `low`，再把 `low` 最大值移入 `high`，维护左右有序关系。
3. 若右侧元素更多，把右侧最小值移回左侧，令左侧等大或多一个。
4. 奇数取左堆顶，偶数取两个堆顶的浮点平均值。

## 用户解法复杂度

- `addNum`：单次时间 `O(log(n + 1))`；`findMedian`：`O(1)`。
- 插入 `n` 个元素总时间 `O(n log(n + 1))`，空间 `O(n)`。
- 每次只做常数次堆操作，两个堆合计保存全部已插入元素。

## 用户代码注释版

> 以下仅在文档中为原代码添加说明；源码中的原实现保持不变。

```cpp
class MedianFinder {
    // 小顶堆, 存大于mid的数
    priority_queue<int, vector<int>, greater<int>> high;

    // 大顶堆, 存小于mid的数
    priority_queue<int, vector<int>, less<int>> low;
public:
    MedianFinder(){

    }

    void addNum(int num) {
        // 先经过左段最大值，再把它送入右段，保持值域顺序。
        low.push(num);
        high.push(low.top());
        low.pop();
        // 左段和右段等大，或左段恰好多一个。
        if(high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        if(low.size() > high.size()) {
            return low.top();
        } else {
            // 乘 1.0 发生在加法前，避免整数相加溢出。
            return (1.0*low.top()+high.top())/2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 值域顺序 | 通过先左后右的搬运维持 `max(low)<=min(high)` | 堆顶才代表中间边界 | 单独说明顺序不变量，不能只讲数量 |
| 数量平衡 | `low.size()` 等于 `high.size()` 或多一 | 奇偶查询统一 | 用归纳说明每轮最多补一次 |
| 空状态与溢出 | 官方保证查询前非空，且已在加法前转浮点 | 当前边界处理正确 | 不必为题目不允许的空查询增加额外接口 |
| 注释语义 | 原注释写“小于/大于 mid” | 重复值可同时存在于两侧，严格不等描述不准确 | 复盘时称“较小/较大一半”，允许相等 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 更新短，查询常数时间 | 保存所有元素，需解释跨堆搬运 | 仅追加的数据流 |
| 推荐解法 | 同算法，明确两个不变量 | 没有渐近提速 | 通用动态中位数基础 |

## 可能的最优解法

1. 沿用用户双堆方案；它已经是当前主题下标准高效写法，无需更换算法。
2. 始终保持 `low.size()==high.size()` 或 `low.size()==high.size()+1`，以及左侧所有值不大于右侧所有值。
3. 插入先经过左段最大值再进入右段；若数量失衡，从右段最小值补回。
4. 按奇偶返回一个或两个边界值，平均数加法前转换为 `double`。

- 推荐复杂度：插入 `O(log(n+1))`，查询 `O(1)`，空间 `O(n)`。
- 这是通用比较模型下适合本周的标准方案；有限值域还可做计数结构，本次不展开。

### 推荐 C++20 提交代码

> 本题是设计题，LeetCode 要求类名 `MedianFinder`；保留官方接口，不套用 `class Solution`。

```cpp
class MedianFinder {
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;
public:
    MedianFinder() = default;

    void addNum(int num) {
        // low 保存较小的一半；跨堆搬运保证 low 中的数不大于 high。
        low.push(num);
        high.push(low.top());
        low.pop();
        if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        // low 的大小等于 high 或多一个；加法前转浮点数。
        if (low.size() > high.size()) return low.top();
        return (static_cast<double>(low.top()) + high.top()) / 2.0;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态与更新 | 两堆及跨边界搬运 | 相同 | 已达标准高效方案 |
| 边界 | 浮点求和，依赖非空查询约束 | 相同并加注释 | 解释前提即可 |
| 时间 | 插入 `O(log(n+1))`，查询 `O(1)` | 相同 | 重点在证明而非改写 |
| 空间 | `O(n)` | `O(n)` | 数据持续增长时不能按窗口估计 |

## 本地验证

原实现与推荐实现共同通过 45,009 次前缀中位数核对，覆盖官方示例、负数、零、重复值、升降交错与固定随机种子生成的数据。基准为每个前缀重新排序。三题测试均以 C++20 编译，并开启 AddressSanitizer 与 UndefinedBehaviorSanitizer，未发现错误。测试入口和可执行文件放在临时目录，未加入仓库。

## 下一步建议

无需重写原算法。先脱离代码说明“有序关系”和“大小关系”分别由哪一步保证，再回看今天的 480，把仅追加扩展到插入与删除。

## 后续练习

继续周计划第 6 天：`239. Sliding Window Maximum`（旧题回顾）、`1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit`、`218. The Skyline Problem`。保留原题单顺序，分别训练持续更新下的结果维护、约束判断和复杂状态整合。

## 代码同步

- 已在原 `MedianFinder` 的 `public:` 之前添加私有推荐函数：`addNumOpt`、`findMedianOpt`。
- 原公开接口、用户解法及其注释均保持不变；推荐函数用于对照阅读，当前提交入口仍运行用户原实现。
- 推荐方法沿用原成员状态，没有创建第二套持久化数据。
