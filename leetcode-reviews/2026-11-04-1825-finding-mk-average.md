# 题解点评 - 1825. Finding MK Average

## 基本信息

- 日期：2026-11-04
- 主题：第 9 周第 5 天，堆与优先队列 / 动态有序分段
- 难度：困难
- 本次结果：本地对拍通过；未读取到 LeetCode 提交结果，不标记官方 AC。
- 对应源码：[src/1825.finding-mk-average.cpp](../src/1825.finding-mk-average.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/finding-mk-average/)；算法分析与验证基于本地源码。
- 查询日期：2026-11-04
- 约束核对：3<=m<=10^5，1<=k 且 2k<m，输入为不超过 10^5 的正整数。

## 用户思路概述

1. 队列保存到达顺序，三个 `multiset` 保存最小 `k` 个、中间 `m-2k` 个、最大 `k` 个元素。
2. 预热期先把所有元素放入 `mid`，首次收满 `m` 个后集中剥离两端。
3. 后续先从对应段删除最旧值，再根据两端边界插入新值。
4. 先把两端多余元素移入中段，再用中段极值补齐两端；跨越中段时同步维护 `sum`。
5. 不满窗口返回 `-1`，否则用 `sum / (m-2*k)` 返回平均值。

## 用户解法复杂度

- 一般插入和窗口填满后的更新：单次 `O(log m)`。
- 第一次凑满 `m` 个元素：单次 `O((k+1) log m)`，因为额外搬移 `2k` 个元素。
- 连续 `t` 次插入的总时间 `O(t log m)`，摊还每次 `O(log m)`；首次搬移在 `t>=m` 时由 `k<m/2` 吸收。
- 查询 `O(1)`，空间 `O(m)`；队列与三段集合都只保留最近窗口。

## 用户代码注释版

> 以下仅在文档中为原代码添加说明；源码中的原实现保持不变。

```cpp
using ll = long long;
class MKAverage {
    // low: 最小的k个数
    // mid: 中间m-2*k个数
    // high: 最大的k个数
    multiset<int> low, mid, high;
    ll sum; // 只记录 mid 的和，最多约 10^10，必须用 64 位。
    queue<int> q;
    int m, k;

public:
    MKAverage(int m, int k): m(m), k(k), sum(0) {

    }

    void addElement(int num) {
        q.push(num);
        // 预热期全部放 mid，第一次成窗时再切出两端。
        if(q.size()<=m) {
            mid.insert(num);
            sum += num;
            if(q.size() == m) { // 此次需要额外搬移 2k 个数。
                for(int i=0; i<k; i++) {
                    int x = *mid.begin();
                    mid.erase(mid.find(x));
                    sum -= x;
                    low.insert(x);
                }
                for(int i=0; i<k; i++) {
                    int x = *mid.rbegin();
                    mid.erase(mid.find(x));
                    sum -= x;
                    high.insert(x);
                }
            }
            return ;
        }
        int old = q.front();
        q.pop();
        // 等值元素可任选一段删一个，随后恢复各段大小。
        if(low.find(old) != low.end()) {
            low.erase(low.find(old));
        } else if(high.find(old) != high.end()) {
            high.erase(high.find(old));
        } else {
            mid.erase(mid.find(old));
            sum -= old;
        }

        if(!low.empty() && num <= *low.rbegin()) {
            low.insert(num);
        } else if(!high.empty() && num >= *high.begin()) {
            high.insert(num);
        } else {
            mid.insert(num);
            sum += num;
        }

        // 先缩减过大的两端，再用 mid 补足两端缺额。
        while(low.size() > k) {
            int x = *low.rbegin();
            low.erase(prev(low.end()));
            mid.insert(x);
            sum += x;
        }
        while(high.size() > k) {
            int x = *high.begin();
            high.erase(high.begin());
            mid.insert(x);
            sum += x;
        }
        while(low.size() < k) {
            int x = *mid.begin();
            mid.erase(mid.find(x));
            sum -= x;
            low.insert(x);
        }
        while(high.size() < k) {
            int x = *mid.rbegin();
            mid.erase(mid.find(x));
            sum -= x;
            high.insert(x);
        }
    }

    int calculateMKAverage() {
        if(q.size() < m) return -1;
        return sum / (m-2*k); // 输入为正数，截断等于向下取整。
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 三段不变量 | 满窗后两端各 `k` 个且段间有序 | 中段恰是应保留部分 | 同时验证大小、顺序和总和 |
| 首次成窗 | 集中搬移 `2k` 个数 | 单次时间存在尖峰，但总体复杂度合格 | 区分最坏单次与摊还复杂度 |
| 重复元素 | 按 low、high、mid 顺序找旧值，只删一个 | 等值副本可互换，之后恢复分段即可 | 不需要为每个副本绑定原始下标 |
| 中段求和 | `long long` 且迁入加、迁出减 | 查询可保持 `O(1)`，避免总和溢出 | 把每次跨中段搬运当成一次记账 |
| 缩减再补足 | 先处理两端超额，再补不足 | 补位前中段有足够候选 | 保留处理顺序，说明 `m>2k` 的作用 |
| 取整 | 正整数除法 | 与题目要求的向下取整一致 | 若迁移到负数场景，C++ 截断不等于 floor |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 满窗后更新高效，查询常数时间 | 首次切分有 O(k log m) 搬移 | 当前约束完全可用 |
| 推荐解法 | 预热与满窗统一，每次更新都有界 | 需理解预热期目标大小 | 更关注单次操作上界的流式维护 |

## 可能的最优解法

1. 沿用三段集合与中段求和，改为从第一个元素起逐次分段。
2. 令当前元素数为 `s`：左段目标 `min(k,s)`，右段目标 `min(k,s-leftTarget)`，剩余归中段。满窗后自动变成 `k, m-2k, k`。
3. 按值域边界插入；若超过 `m`，从队列弹出最旧值，并从任意含该值的段删除一个副本。
4. 先将两端超过目标的边界值送入中段，再从中段两端补足缺额。每次中段变化都同步 `sum`。
5. 每轮仅增加一个元素、最多删除一个元素，两个目标也只变化常数，因此所有平衡循环合计只搬移常数个元素。
6. 保持段间有序、两端大小达到目标、`sum` 恰等于中段之和。少于 `m` 仍返回 `-1`。

- 推荐复杂度：每次插入最坏 `O(log m)`，查询 `O(1)`，空间 `O(m)`。
- 提升在于消除首次成窗的操作尖峰，整体渐近复杂度与用户方案相同。有限值域的计数及前缀和结构也能实现，本次选择更贴近本周且可迁移的分段方案。

### 推荐 C++20 提交代码

> 本题是设计题，LeetCode 要求类名 `MKAverage`；保留官方接口，不套用 `class Solution`。

```cpp
class MKAverage {
    multiset<int> low, mid, high;
    long long sum = 0;
    queue<int> q;
    int m, k;
public:
    MKAverage(int m, int k) : m(m), k(k) {}

    void addElement(int num) {
        q.push(num);
        if (!low.empty() && num <= *low.rbegin()) low.insert(num);
        else if (!high.empty() && num >= *high.begin()) high.insert(num);
        else {
            mid.insert(num);
            sum += num;
        }
        if (q.size() > static_cast<size_t>(m)) {
            int old = q.front();
            q.pop();
            auto it = low.find(old);
            if (it != low.end()) low.erase(it);
            else if (auto highIt = high.find(old); highIt != high.end()) {
                high.erase(highIt);
            } else {
                mid.erase(mid.find(old));
                sum -= old;
            }
        }
        // 预热期也逐次分段，避免首次凑满 m 个时集中搬移 2k 个数。
        size_t lowTarget = min(static_cast<size_t>(k), q.size());
        size_t highTarget = min(static_cast<size_t>(k), q.size() - lowTarget);
        // 先把两侧多余元素送入 mid，再补足两侧，保证补位时有候选。
        while (low.size() > lowTarget) {
            auto it = prev(low.end());
            int value = *it;
            low.erase(it);
            mid.insert(value);
            sum += value;
        }
        while (high.size() > highTarget) {
            auto it = high.begin();
            int value = *it;
            high.erase(it);
            mid.insert(value);
            sum += value;
        }
        while (low.size() < lowTarget) {
            auto it = mid.begin();
            int value = *it;
            mid.erase(it);
            sum -= value;
            low.insert(value);
        }
        while (high.size() < highTarget) {
            auto it = prev(mid.end());
            int value = *it;
            mid.erase(it);
            sum -= value;
            high.insert(value);
        }
    }

    int calculateMKAverage() {
        // 题目数值均为正，整数除法就是向下取整。
        if (q.size() < static_cast<size_t>(m)) return -1;
        return static_cast<int>(sum / (m - 2 * k));
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 预热状态 | 全部暂存 mid，首次满窗批量切分 | 每轮按当前数量分段 | 将一次大搬运分摊到各次插入 |
| 最坏单次插入 | `O((k+1) log m)` | `O(log m)` | 消除首次成窗尖峰 |
| t 次插入总时间 | `O(t log m)` | `O(t log m)` | 总体复杂度相同 |
| 查询与空间 | `O(1)` / `O(m)` | 相同 | 已具备稳定查询能力 |
| 数值安全 | `long long sum`，正数整数除法 | 相同 | 保持迁入加、迁出减 |

## 本地验证

原实现与推荐实现共同通过 592,403 次更新核对。包含长度 8、值域 {1,2,3} 的全部 6,561 个序列，对 m=3..7 和全部合法 k 验证；另有随机长序列、全相等、首次满窗、最小中段，以及总和超过 int 上限的测试。推荐实现还逐次检查各段大小、段间顺序和中段总和。三题测试均以 C++20 编译，并开启 AddressSanitizer 与 UndefinedBehaviorSanitizer，未发现错误。测试入口和可执行文件放在临时目录，未加入仓库。

## 下一步建议

原实现可保留作为阶段化写法。对照推荐版本手推一次从空状态到满窗的过程，再说明每条 sum 更新为何正确；继续下一天前能区分最坏单次与摊还复杂度即可。

## 后续练习

继续周计划第 6 天：`239. Sliding Window Maximum`（旧题回顾）、`1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit`、`218. The Skyline Problem`。保留原题单顺序，分别训练持续更新下的结果维护、约束判断和复杂状态整合。

## 代码同步

- 已在原 `MKAverage` 的 `public:` 之前添加私有推荐函数：`addElementOpt`。
- 原公开接口、用户解法及其注释均保持不变；推荐函数用于对照阅读，当前提交入口仍运行用户原实现。
- 设计题推荐方法沿用原成员状态；初始化后选择原更新方法或 Opt 更新方法独立使用，勿在两套预热规则之间切换。
