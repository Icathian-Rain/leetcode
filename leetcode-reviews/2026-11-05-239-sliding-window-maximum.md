# 题解点评 - 239. Sliding Window Maximum

## 基本信息

- 日期：2026-11-05
- 主题：第 9 周第 6 天，窗口与有效候选维护
- 难度：困难
- 本次结果：通过（用户确认已通过测试）；按用户要求，本次未编译、运行、对拍或重复验证答案。
- 对应源码：[src/239.sliding-window-maximum.cpp](../src/239.sliding-window-maximum.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/sliding-window-maximum/description/)；思路与复杂度分析基于本地源码。
- 查询日期：2026-11-05
- 记录性质：旧题回顾，沿用当前源码；不是今天新增的源码实现。此前点评保留在 [2026-05-14 记录](2026-05-14-239-sliding-window-maximum.md)。

## 用户思路概述

1. 局部类 `MyQueue` 只保存仍可能成为窗口最大值的候选值，队列从前到后非递增。
2. 新值进入时，淘汰队尾严格小于它的值；相等副本全部保留。
3. 旧值离开时，只有它等于队首才弹出一个副本；不等则说明它已经被更优候选淘汰。
4. 先处理首个窗口，之后每轮加入新值、移出旧值，再读取最大值。
5. 文件中已有 `maxSlidingWindowOpt` 下标版本，本次沿用，不重复插入。

## 用户解法复杂度

- 时间 `O(n)`，每个元素至多进入、离开队列各一次。
- 辅助空间 `O(k)`；当前先加入再删除，短暂至多 `k+1` 个候选，仍为 `O(k)`。
- 输出空间 `O(n-k+1)`，计入输出后总空间 `O(n)`。
- 单次 `push` 可连续弹出多个值；`O(1)` 是摊还开销，并非每次最坏开销。

## 用户代码注释版

> 保留用户原解法结构，只在文档中增加说明，不将这些注释写回原实现。

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        class MyQueue {
            private:
                deque<int> q;
            public:
                void push(int val) {
                    // 将小于val的全部pop出来，插入val
                    // 值队列必须保留相等副本，后续才能按值移除一个。
                    while (!q.empty() && q.back() < val)
                    {
                        q.pop_back(); // 新值更大且更晚过期，旧值不会再成为最大值。
                    }
                    q.push_back(val);
                }
                void pop(int val) {
                    // 若目前最大值为val, 则pop出来
                    if(q.front() == val) {
                        q.pop_front();
                    }
                }
                int front() {
                    // front为最大值
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
            q.pop(nums[i-k]); // 旧值若曾被淘汰，此处无需额外操作。
            ans.push_back(q.front());
        }
        return ans;

    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 复盘重点 |
| --- | --- | --- | --- |
| 候选支配关系 | 较小旧值被较大新值淘汰 | 新值更优且更晚过期，淘汰是永久的 | 用这两条依据证明队尾弹出 |
| 相等值 | 入队时使用严格 `<` | 保留重复最大值的副本数 | 值队列不能直接改成 `<=` |
| 过期状态 | 按旧值与队首比较 | 正确，但只适合配合保留重复副本的值队列 | 下标版本直接判断位置，更易迁移 |
| 摊还分析 | 单次可能弹出多个元素 | 仍是总计线性时间 | 统计每个元素进出次数 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户值队列 | 封装简洁，线性时间 | 重复值与过期逻辑必须一起解释 | 固定窗口且保留同值副本 |
| 推荐下标队列 | 过期条件显式，易迁移 | 需要通过下标取值 | 固定窗口及相邻窗口变体 |

## 可能的最优解法

1. 沿用文件中已有下标单调队列：队列下标递增，对应值严格递减。
2. 先从队首删除 `index<=i-k` 的过期候选，再从队尾删除值小于等于新值的候选。
3. 相等值保留新下标即可，因为其有效期更长；这是下标写法与用户值写法的重要区别。
4. 窗口形成后，队首就是窗口最大值。

- 推荐时间 `O(n)`，辅助空间 `O(k)`，输出空间 `O(n-k+1)`。
- 用户解法已达到最优渐近复杂度；推荐版本的价值在于更直接地表达过期状态。

### 推荐 C++20 提交代码

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> indexes;
        vector<int> ans;

        for(int i = 0; i < (int)nums.size(); i++) {
            while(!indexes.empty() && indexes.front() <= i - k) {
                indexes.pop_front();
            }
            while(!indexes.empty() && nums[indexes.back()] <= nums[i]) {
                indexes.pop_back();
            }
            indexes.push_back(i);

            if(i >= k - 1) {
                // 队首下标始终对应当前窗口最大值。
                ans.push_back(nums[indexes.front()]);
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态 | 候选值与重复副本 | 候选下标 | 下标同时表达数值和有效期 |
| 同值处理 | `<`，保留全部副本 | `<=`，保留更新下标 | 比较符与状态定义绑定 |
| 过期 | 旧值等于队首时弹一个 | 直接检查下标 | 位置语义更直观 |
| 时间 / 辅助空间 | `O(n)` / `O(k)` | 相同 | 无算法级提速 |

## 下一步建议

作为今天的旧题回顾记录，重点比较值队列与下标队列的同值规则，不必重复新增 Opt 版本。结合今天的 1438 口述固定窗口如何推广到可收缩窗口。

## 后续安排

继续周计划第 7 天既定题单：658（旧题热身）、451（核心）、895（拔高）。目标分别为方案取舍、输出规则理解和动态操作整合；具体顺序与难度见周计划，不另扩展题单。

## 代码同步

- 私有函数：`maxSlidingWindowOpt`，位于原 `class Solution` 的 `public:` 之前。
- 239 已有同名推荐实现，本次复用，源码未改动。
- 本次仅整理源码与文档，不提供新增版本的运行验证结论。
