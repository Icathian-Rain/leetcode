# 题解点评 - 480. Sliding Window Median

## 基本信息

- 日期：2026-11-04
- 主题：第 9 周第 5 天，堆与优先队列 / 动态有序分段
- 难度：困难
- 本次结果：本地对拍通过；未读取到 LeetCode 提交结果，不标记官方 AC。
- 对应源码：[src/480.sliding-window-median.cpp](../src/480.sliding-window-median.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/sliding-window-median/)；[国际版约束补充](https://leetcode.com/problems/sliding-window-median/description/)；算法分析与验证基于本地源码。
- 查询日期：2026-11-04
- 约束核对：1<=k<=n<=10^5，元素可覆盖完整 32 位有符号整数范围。

## 用户思路概述

1. 用两个 `multiset` 保存窗口的较小一半与较大一半。
2. 根据左侧最大值决定新元素归属；`balance` 保持左侧等大或多一个。
3. 窗口前进时按值查找旧元素，以迭代器删除一个副本，再次平衡。
4. 从左侧最大值、右侧最小值中读取中位数；公开函数委托给 `s1`。

## 用户解法复杂度

- 总时间 `O(n log(k + 1))`，单轮更新 `O(log(k + 1))`，读取中位数 `O(1)`。
- 辅助空间 `O(k)`；输出占 `O(n-k+1)`，计入输出的总空间为 `O(n)`。
- 临时至多 `k+1` 个元素，每轮插入、查找、删除和常数次边界搬运。
- 使用 `log(k+1)` 是为统一表达 `k=1`；常见写法是 `O(n log k)`。

## 用户代码注释版

> 以下仅在文档中为原代码添加说明；源码中的原实现保持不变。

```cpp
class Solution {
    vector<double> s1(vector<int>& nums, int k) {
        multiset<int> left, right;
        vector<double> ans;
        // 只跨边界搬运极值，维持左段大小等于右段或多一个。
        auto balance = [&]() {
            while(left.size() > right.size()+1) {
                auto it = prev(left.end());
                right.insert(*it);
                left.erase(it);
            }
            while(left.size() < right.size()) {
                auto it = right.begin();
                left.insert(*it);
                right.erase(it);
            }
        };
        auto add = [&](int x) {
            if(left.empty() || x <= *left.rbegin()) {
                left.insert(x);
            } else {
                right.insert(x);
            }
            balance();
        };
        auto remove = [&](int x) {
            auto it = left.find(x);
            if(it != left.end()) {
                left.erase(it); // 按迭代器只删一个副本。
            } else {
                // x 必在当前窗口中；左侧没有则右侧必有。
                right.erase(right.find(x));
            }
            balance();
        };
        int n=nums.size();
        for(int i=0; i<n; i++) {
            int x = nums[i];
            add(x); // 暂时允许 k+1 个元素，移除旧值后再读答案。
            if(i >= k) {
                remove(nums[i-k]);
            }
            if(i >= k-1) {
                if(k%2) ans.push_back(*left.rbegin());
                // 转成 double 后相加，覆盖 32 位整数边界。
                else ans.push_back(((double)*left.rbegin() + *right.begin())/2.0);
            }
        }
        return ans;

    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        return s1(nums, k);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 删除能力 | 使用可按值查找的 `multiset` | 精确删除过期值，无须额外延迟清理 | 选择结构时同时考虑插入、删除、查询 |
| 重复值 | `erase(iterator)` 只删除一个副本 | 不会误删所有同值元素 | 两侧同值时删左侧再平衡仍正确 |
| 顺序与数量 | 插入按边界归属，搬运只使用两段极值 | 同时维护有序分段和元素数 | 不能仅验证 `size` 而忽视值域交叉 |
| 整数边界 | 偶数情况先转 `double` | 避免两个 `int` 相加溢出 | 保留这个转换顺序 |
| 删除前提 | 右侧 `erase(find(x))` 未单独判断 | 依赖 x 确实在当前窗口中 | 本题前提成立；迁移成通用容器时需约定接口 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 过期元素可立即删除，空间有界 | 树容器常数开销，依赖正确平衡 | 固定窗口的精确中位数 |
| 推荐解法 | 保留优势，补不变量注释 | 算法复杂度相同 | 需要稳定 O(k) 辅助空间 |

## 可能的最优解法

1. 沿用双 `multiset`，辅助空间严格限制在 `O(k)`。
2. 插入后平衡；若有过期值，删除一个副本后再平衡；最后读取答案。
3. 顺序不变量为左段所有值不大于右段所有值，数量不变量为左段等大或多一个。
4. `k=1` 时答案只读左侧；偶数窗口先转浮点再求和。

- 推荐时间 `O(n log(k+1))`；辅助空间 `O(k)`，输出 `O(n-k+1)`。
- 用户算法已达到标准复杂度。推荐版本主要补充命名、注释与答案容量预留，不宣称算法级提速。
- 双堆延迟删除也可行，但朴素实现可能保留大量埋在堆内的过期值，不能直接声称物理空间始终是 `O(k)`；本次不展开。

### 推荐 C++20 提交代码

```cpp
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> left, right;
        vector<double> result;
        result.reserve(nums.size() - k + 1);
        auto balance = [&]() {
            // 左侧保存较小的 ceil(当前元素数 / 2) 个元素。
            while (left.size() > right.size() + 1) {
                auto it = prev(left.end());
                right.insert(*it);
                left.erase(it);
            }
            while (left.size() < right.size()) {
                auto it = right.begin();
                left.insert(*it);
                right.erase(it);
            }
        };
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (left.empty() || nums[i] <= *left.rbegin()) left.insert(nums[i]);
            else right.insert(nums[i]);
            balance();
            if (i >= k) {
                // 重复值只删一个副本，两侧同值可任选一侧删除后再平衡。
                auto it = left.find(nums[i - k]);
                if (it != left.end()) left.erase(it);
                else right.erase(right.find(nums[i - k]));
                balance();
            }
            if (i >= k - 1) {
                if (k % 2) result.push_back(*left.rbegin());
                else result.push_back((static_cast<double>(*left.rbegin())
                                       + *right.begin()) / 2.0);
            }
        }
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态与更新 | 双集合，add/remove/balance | 相同分段原则 | 提升命名与不变量说明 |
| 重复与溢出 | 单副本删除、先转浮点 | 相同 | 已正确覆盖关键边界 |
| 时间 | `O(n log(k+1))` | 相同 | `reserve` 只减少扩容常数 |
| 空间 | 辅助 `O(k)`，含输出 `O(n)` | 相同 | 分开说明容器与输出 |

## 本地验证

原实现与推荐实现共同通过 65,716 个窗口结果核对；测试对每个数组枚举全部合法 k，覆盖 k=1、k=n、奇偶窗口、重复值，以及 INT_MIN/INT_MAX。基准为窗口排序。三题测试均以 C++20 编译，并开启 AddressSanitizer 与 UndefinedBehaviorSanitizer，未发现错误。测试入口和可执行文件放在临时目录，未加入仓库。

## 下一步建议

无需为使用堆而改掉正确实现。重点口述：为什么两侧存在相同值时可以任选一侧删一个，以及为什么每轮搬运次数为常数。

## 后续练习

继续周计划第 6 天：`239. Sliding Window Maximum`（旧题回顾）、`1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit`、`218. The Skyline Problem`。保留原题单顺序，分别训练持续更新下的结果维护、约束判断和复杂状态整合。

## 代码同步

- 已在原 `Solution` 的 `public:` 之前添加私有推荐函数：`medianSlidingWindowOpt`。
- 原公开接口、用户解法及其注释均保持不变；推荐函数用于对照阅读，当前提交入口仍运行用户原实现。
