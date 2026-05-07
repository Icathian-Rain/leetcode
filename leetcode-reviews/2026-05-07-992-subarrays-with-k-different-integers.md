# 题解点评 - 992. Subarrays with K Different Integers

## 基本信息

- 日期：2026-05-07
- 主题：双指针与滑动窗口 - 综合迁移与模拟面试
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/992.subarrays-with-k-different-integers.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 定义内部函数 `f(target)`，用滑动窗口统计不同整数数量至少为 `target` 的子数组个数。
2. 右指针扩张窗口，用 `unordered_map` 维护每个值出现次数。
3. 当窗口内不同整数数量 `>= target` 时，持续移动左指针，直到窗口重新变成少于 `target` 种。
4. 此时所有起点在 `0..l-1` 的子数组都满足至少 `target` 种，累加 `l`。
5. 用 `f(k) - f(k + 1)` 得到恰好 `k` 种不同整数的子数组数量。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：`f(k)` 和 `f(k+1)` 各线性扫描一次；哈希表最多保存窗口中的不同整数。

## 用户代码注释版

```cpp
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int n=nums.size();

        auto f=[&](int target)->int {
            unordered_map<int, int> cnt; // 当前窗口内每个数的出现次数。
            int ans=0;
            for(int l=0, r=0; r<n; r++) {
                cnt[nums[r]]++;
                while(l<=r && cnt.size() >= target) {
                    // 一旦窗口达到至少 target 种，就左移到刚好失效。
                    cnt[nums[l]]--;
                    if(cnt[nums[l]] == 0) {
                        cnt.erase(nums[l]);
                    }
                    l++;
                }

                // 此时 [l, r] 已少于 target 种，所有更靠左的起点都满足至少 target 种。
                ans+=l;
            }
            return ans;
        };

        return f(k)-f(k+1); // 至少 k 种 - 至少 k+1 种 = 恰好 k 种。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 恰好 K 的转化 | 使用“至少 K - 至少 K+1”。 | 数学上正确，是一个很好的等价转化。 | 复盘时也掌握更常见的“最多 K - 最多 K-1”，更容易和窗口合法性模板衔接。 |
| 计数贡献 | 窗口收缩到失效后累加 `l`。 | 逻辑正确，但比 `right-left+1` 更绕。 | 说清 `l` 代表第一个不满足至少 `target` 的起点。 |
| 哈希状态维护 | 频次归零后删除 key。 | 保证 `cnt.size()` 真实表示不同整数数量。 | 这是本题正确性的关键，后续窗口频次题继续保持。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 等价转化正确，线性复杂度，频次维护完整。 | “至少”版本的收缩和贡献值不如“最多”版本直观。 | 可通过本题，适合复盘计数差分思想。 |
| 推荐最优解 | 使用更常见的 `atMost(k) - atMost(k-1)`，窗口始终保持合法后计数。 | 本质复杂度相同，也需要理解两次扫描的差分。 | 适合沉淀成后续“恰好 K”模板。 |

## 最优解法

1. 把“恰好 `k` 种不同整数”转成“最多 `k` 种”减去“最多 `k-1` 种”。
2. `atMost(limit)` 中维护一个不同整数数量不超过 `limit` 的窗口。
3. 右端扩张后，如果不同整数数量超限，就持续移动左端直到窗口恢复合法。
4. 窗口合法时，以 `right` 结尾、起点在 `[left, right]` 的子数组都满足最多 `limit` 种，贡献 `right - left + 1`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        auto atMost = [&](int limit) -> int {
            if (limit < 0) {
                return 0;
            }

            unordered_map<int, int> count;
            int left = 0;
            int ans = 0;

            for (int right = 0; right < (int)nums.size(); ++right) {
                ++count[nums[right]];

                while ((int)count.size() > limit) {
                    --count[nums[left]];
                    if (count[nums[left]] == 0) {
                        count.erase(nums[left]);
                    }
                    ++left;
                }

                // 以 right 结尾、起点在合法窗口内的子数组都满足最多 limit 种。
                ans += right - left + 1;
            }

            return ans;
        };

        return atMost(k) - atMost(k - 1);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt.size()` 表示窗口不同整数数量。 | 同样使用频次表维护不同整数数量。 | 状态维护已经正确。 |
| 更新逻辑 | 收缩到“少于 target”，统计至少 `target` 的起点数。 | 收缩到“最多 limit”，统计合法窗口长度。 | 推荐优先使用合法窗口模板，口述更自然。 |
| 边界处理 | 本题 `k >= 1` 时稳定。 | `limit < 0` 显式返回 `0`。 | 模板化时补上差分下界。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优。 |

## 下一步建议

这题建议把两种差分都口头讲一遍：你的“至少”版本证明能力更强，推荐版本更适合作为以后快速落代码的模板。

## 后续练习

1. `1248. Count Number of Nice Subarrays` - 把“恰好 K”迁移到奇数数量统计。
2. `930. Binary Subarrays With Sum` - 继续练计数差分，也可以对比前缀和写法。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/992.subarrays-with-k-different-integers.cpp`
- 新函数名：`subarraysWithKDistinctOpt`
- 保留用户原实现：是
