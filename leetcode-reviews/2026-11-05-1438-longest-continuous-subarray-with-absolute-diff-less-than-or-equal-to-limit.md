# 题解点评 - 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

## 基本信息

- 日期：2026-11-05
- 主题：第 9 周第 6 天，窗口与有效候选维护
- 难度：中等
- 本次结果：通过（用户确认已通过测试）；按用户要求，本次未编译、运行、对拍或重复验证答案。
- 对应源码：[src/1438.longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit.cpp](../src/1438.longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit.cpp)
- 资料来源：[LeetCode 中国官方题目页](https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)；思路与复杂度分析基于本地源码。
- 查询日期：2026-11-05
- 关键约束：元素为 1..10^9，limit 为 0..10^9，数组长度最多 10^5。

## 用户思路概述

1. 用窗口 `[l,r]` 枚举右端点；`maxq` 与 `minq` 分别保存最大值、最小值候选的下标。
2. 新数进入时，从两条队列的队尾淘汰不可能再成为极值的候选。
3. 用 `max-min<=limit` 判断整个窗口任意两数的差是否达标。
4. 不满足时持续右移左边界，移除过期队首，直到恢复合法。
5. 更新当前合法窗口长度的最大值。

## 用户解法复杂度

- 时间 `O(n)`：左右边界都只向右，每个下标在每条队列中至多进入、离开一次。
- 辅助空间 `O(w)`，其中 `w` 为扫描中候选所在的最大窗口长度；最坏为 `O(n)`。当前实现保留相等下标，全相等数组可达到该上界。
- 没有长度为 `n` 的输出数组，返回值只占 `O(1)`。

## 用户代码注释版

> 保留用户原解法结构，只在文档中增加说明，不将这些注释写回原实现。

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n=nums.size();
        int ans = 0;
        // minq: 单调递增队列,队首存储最小值下标
        // maxq: 单调递减队列,队首是存储最大值下标
        deque<int> minq, maxq;
        for(int l=0, r=0; r<n; r++) {
            // 从队尾永久淘汰被新元素支配的候选。
            while(!maxq.empty() && nums[maxq.back()] < nums[r]) {
                maxq.pop_back();
            }
            maxq.push_back(r);
            while(!minq.empty() && nums[minq.back()] > nums[r]) {
                minq.pop_back();
            }
            minq.push_back(r);
            // 任意两数的最大绝对差等于整个窗口的最大值减最小值。
            while(nums[maxq.front()] - nums[minq.front()] > limit) {
                // l 逐个前进，下标恰好等于 l 的队首本轮过期。
                if(maxq.front() == l) maxq.pop_front();
                if(minq.front() == l) minq.pop_front();
                l++;
            }
            ans = max(ans, r-l+1); // 恢复合法后再统计以 r 结尾的最长窗口。
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 复盘重点 |
| --- | --- | --- | --- |
| 全局条件 | 用窗口最大值减最小值 | 等价覆盖任意两数，不局限于相邻差 | 先化简条件，再选择维护状态 |
| 收缩时机 | 使用 while 直到合法 | 可连续越过多个不合法左边界 | 仅在恢复合法后记录长度 |
| 过期判断 | 队首下标等于 l 时删除 | l 每次只加一，判断足够 | 若以后一次跳跃多格，则用 `<left` 清理 |
| 重复值 | 两条队列都保留相等下标 | 正确，可能保留更多候选 | 下标版本可删除旧同值，只保留更新的下标 |
| 整数范围 | 原代码用 int 计算差值 | 本题正数上界 10^9，最大差不足 10^9，当前安全 | 推荐转 long long 仅为迁移更宽数值范围，不是修错 |

## 算法优缺点

| 方案 | 优点 | 取舍 | 适用情况 |
| --- | --- | --- | --- |
| 用户双队列 | 条件化简正确，更新线性 | 同值下标可能较多，但不影响复杂度上界 | 维护连续区间的双极值约束 |
| 推荐双队列 | 同值淘汰与过期语义更统一 | 最坏空间仍可能线性 | 向更多下标窗口题迁移 |

## 可能的最优解法

1. 沿用双单调队列，分别维护最大值与最小值候选下标。
2. 两条队列均只保留更新的同值下标，减少冗余候选；不改变最坏渐近复杂度。
3. 新右端点入队后，只要极差超限就持续移动左端点，并移除过期队首。
4. 不变量为：候选下标在窗口内且递增，最大队列值递减、最小队列值递增；统计答案时窗口已经合法。
5. 每个右端点收缩到的 left 是当前最早合法起点，因为向右扩张不可能让之前已经不合法的更早起点重新合法。

- 推荐时间 `O(n)`，最坏空间 `O(n)`；更精确地说队列空间受当前候选窗口长度约束。
- 用户算法已经最优。推荐版本只统一命名、去掉旧同值候选并拓宽差值运算类型。

### 推荐 C++20 提交代码

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> minIndexes, maxIndexes;
        int left = 0, best = 0;
        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            // 保存下标时，同值只保留更晚过期的候选即可。
            while (!maxIndexes.empty() && nums[maxIndexes.back()] <= nums[right]) {
                maxIndexes.pop_back();
            }
            maxIndexes.push_back(right);
            while (!minIndexes.empty() && nums[minIndexes.back()] >= nums[right]) {
                minIndexes.pop_back();
            }
            minIndexes.push_back(right);
            // 窗口中任意两数的最大绝对差就是 max - min。
            while (static_cast<long long>(nums[maxIndexes.front()])
                   - nums[minIndexes.front()] > limit) {
                ++left;
                if (maxIndexes.front() < left) maxIndexes.pop_front();
                if (minIndexes.front() < left) minIndexes.pop_front();
            }
            best = max(best, right - left + 1);
        }
        return best;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 推荐代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态 | minq、maxq 保存下标 | 相同 | 已正确建模 |
| 同值处理 | 保留全部同值下标 | 只保留更新下标 | 减少冗余但最坏空间不变 |
| 差值类型 | int，本题范围安全 | long long | 为更宽输入范围便于复用 |
| 时间 / 最坏空间 | `O(n)` / `O(n)` | 相同 | 当前已最优 |

## 下一步建议

可以进入下一题。复盘时先证明“任意两数差”为什么只需最大值与最小值，再证明左边界不会回退；不需要为了复盘重跑答案测试。

## 后续安排

继续周计划第 7 天既定题单：658（旧题热身）、451（核心）、895（拔高）。目标分别为方案取舍、输出规则理解和动态操作整合；具体顺序与难度见周计划，不另扩展题单。

## 代码同步

- 私有函数：`longestSubarrayOpt`，位于原 `class Solution` 的 `public:` 之前。
- 已新增推荐函数，原公开提交函数及用户实现逐字保留；默认提交入口仍调用原实现。
- 本次仅整理源码与文档，不提供新增版本的运行验证结论。
