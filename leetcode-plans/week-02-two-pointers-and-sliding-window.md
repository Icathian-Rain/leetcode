# 第 02 周 - 双指针与滑动窗口

## 本周目标

学会用两个可解释的指针缩小搜索空间：在有序数组里用左右指针排除不可能答案，在原地数组题里用快慢指针维护可写区域，在字符串和子数组题里用滑动窗口维护“当前窗口是否合法”。到本周结束时，你应该能先说清楚指针移动的依据，再写代码，而不是靠样例试探。

当前进度：已完成第 6 天训练，其中 `1004`、`76` 已在 2026-05-05 提前加练并总结，2026-05-06 补齐 `713`。下一步进入第 7 天综合迁移与模拟面试。

资料校准：题号、英文题名和难度已按 LeetCode Wiki 题页校准；查询日期：2026-05-01。

## 与第 1 周衔接

第 1 周最后的 `30. Substring with Concatenation of All Words` 已经暴露出一个很适合第 2 周处理的点：窗口算法不只是在移动左右边界，更重要的是说清楚“窗口合法”的不变量。本周会把频次窗口、非法状态清空、过量状态收缩、恰好 K 个状态等模式拆开练。

## 前置知识

- 数组和字符串的下标边界
- 排序后双指针的单调性
- 快慢指针原地覆盖
- 哈希表 / 频次数组维护窗口状态
- 固定窗口、可变窗口、覆盖型窗口和 `atMost(k)` 技巧

## 每日计划

### 第 1 天 - 相向双指针与移动依据

1. `125. Valid Palindrome` (`简单`) - 用相向指针跳过无效字符，练习边界收缩和字符判断。
2. `167. Two Sum II - Input Array Is Sorted` (`中等`) - 在有序数组里根据和的大小移动左右指针。
3. `11. Container With Most Water` (`中等`) - 训练“移动短板”的贪心依据，而不是盲目枚举。

### 第 2 天 - 快慢指针与原地覆盖

1. `26. Remove Duplicates from Sorted Array` (`简单`) - 练习慢指针维护已写入的去重前缀。
2. `977. Squares of a Sorted Array` (`简单`) - 用相向指针从大到小填充答案，处理负数平方。
3. `80. Remove Duplicates from Sorted Array II` (`中等`) - 把原地覆盖从“最多一次”扩展到“最多两次”。

### 第 3 天 - 排序去重与组合搜索

1. `15. 3Sum` (`中等`) - 排序后固定一个数，再用双指针找补集并处理去重。
2. `16. 3Sum Closest` (`中等`) - 在双指针移动中维护最接近目标的答案。
3. `18. 4Sum` (`中等`) - 把固定层数和去重逻辑扩展到四数之和。

### 第 4 天 - 可变窗口入门

1. `209. Minimum Size Subarray Sum` (`中等`) - 在正数数组里用窗口和判断何时收缩左边界。
2. `3. Longest Substring Without Repeating Characters` (`中等`) - 用窗口内去重状态维护最长合法子串。
3. `904. Fruit Into Baskets` (`中等`) - 把窗口合法性从“无重复”改成“最多两类元素”。

### 第 5 天 - 固定窗口与频次窗口

1. `438. Find All Anagrams in a String` (`中等`) - 用固定长度窗口匹配字符频次。
2. `567. Permutation in String` (`中等`) - 继续练固定窗口频次，并对比和 `438` 的输出差异。
3. `424. Longest Repeating Character Replacement` (`中等`) - 用窗口长度和最高频字符判断替换次数是否超限。

### 第 6 天 - 覆盖需求与窗口收缩

1. `713. Subarray Product Less Than K` (`中等`) - 用乘积窗口统计所有合法子数组数量。
2. `1004. Max Consecutive Ones III` (`中等`) - 把“最多 K 次修改”转成窗口内零的数量约束。
3. `76. Minimum Window Substring` (`困难`) - 练覆盖型窗口：满足需求后尽量收缩，直到刚好失效。

### 第 7 天 - 综合迁移与模拟面试

1. `986. Interval List Intersections` (`中等`) - 用两个列表指针按右端点推进，训练区间交集判断。
2. `42. Trapping Rain Water` (`困难`) - 用左右最大值解释双指针移动，避免只背公式。
3. `992. Subarrays with K Different Integers` (`困难`) - 用 `atMost(k) - atMost(k - 1)` 处理“恰好 K 个不同整数”。

## 本周关注清单

- 写双指针前，先说明左指针和右指针各代表什么。
- 每次移动指针都能给出单调性或合法性理由。
- 滑动窗口题先定义窗口状态，再写扩张、收缩和记录答案的时机。
- 频次窗口里区分“固定长度匹配”“最多 K 个”“至少覆盖需求”“恰好 K 个”。
- 遇到困难窗口题时，不急着套模板，先判断它是哪一种合法性约束。

## 进度更新 - 2026-05-01

- 今日完成：`125. Valid Palindrome`、`167. Two Sum II - Input Array Is Sorted`、`11. Container With Most Water`
- 当前主题：双指针与滑动窗口 - 相向双指针与移动依据
- 暴露问题：整体能正确使用左右指针；后续需要继续强化“为什么移动这个指针”的口头证明，尤其是贪心排除边界时的依据。
- 下一步安排：进入第 2 天快慢指针与原地覆盖，重点练习慢指针维护可写区域的不变量。

## 进度更新 - 2026-05-02

- 今日完成：`26. Remove Duplicates from Sorted Array`、`977. Squares of a Sorted Array`、`80. Remove Duplicates from Sorted Array II`
- 当前主题：第 2 天 - 有序数组的原地整理与结果构造

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `26. Remove Duplicates from Sorted Array` | 待提交验证，源码逻辑检查通过 | 写入位置维护清楚，比较对象选得稳定，能自然处理连续重复段。 | 复盘时重点说清返回长度与有效前缀之间的关系，避免把数组尾部残留值纳入结果。 | [查看](../leetcode-reviews/2026-05-02-26-remove-duplicates-from-sorted-array.md) |
| `977. Squares of a Sorted Array` | 待提交验证，源码逻辑检查通过 | 能先找到正负分界，再从两侧按绝对值构造递增结果，思路完整。 | 分支较多，后续要确认全负数、全非负数、含 0 的边界都能自然落入同一套逻辑。 | [查看](../leetcode-reviews/2026-05-02-977-squares-of-a-sorted-array.md) |
| `80. Remove Duplicates from Sorted Array II` | 待提交验证，源码逻辑检查通过 | 从允许保留两个元素的规则出发，短数组提前返回，主体逻辑简洁。 | 判断条件可以进一步抽象成“当前值是否还能写入”，复盘时要把最多保留两次的判定讲清楚。 | [查看](../leetcode-reviews/2026-05-02-80-remove-duplicates-from-sorted-array-ii.md) |

- 暴露问题：`26` 和 `80` 的代码能稳定维护写入位置，短数组边界也处理到位；`977` 选择了从中间向两侧合并的写法，正确性没问题，但实现分支偏多，复盘时要重点说清每个边界分支为什么安全。
- 下一步安排：进入第 3 天组合类数组题，先保证去重边界和返回结果格式稳定，再观察多层选择时是否还能保持清晰的推进顺序。

## 加练记录 - 2026-05-02

- 今日加练：`27. Remove Element`、`88. Merge Sorted Array`
- 当前主题：原地数组整理与有序数组合并

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `27. Remove Element` | 待提交验证，源码逻辑检查通过 | 能稳定维护有效前缀，原地过滤逻辑简洁。 | 复盘时重点说明返回长度与数组尾部残留值无关。 | [查看](../leetcode-reviews/2026-05-02-27-remove-element.md) |
| `88. Merge Sorted Array` | 待提交验证，源码逻辑检查通过 | 从后向前写入，避免覆盖 `nums1` 中尚未比较的有效元素。 | 可以进一步减少 `nums2` 用完后的无效自赋值，理解何时能提前停止。 | [查看](../leetcode-reviews/2026-05-02-88-merge-sorted-array.md) |

- 暴露问题：加练题整体延续了第 2 天的原地写入能力；`88` 的分支覆盖完整，但还可以利用“剩余 `nums1` 已在原位”来让控制流更紧。
- 下一步安排：保持进入第 3 天组合类数组题的节奏，同时把“从后往前写避免覆盖”作为后续有序数组题的可迁移经验。

## 进度更新 - 2026-05-03

- 今日完成：`15. 3Sum`、`16. 3Sum Closest`、`18. 4Sum`
- 当前主题：第 3 天 - 排序去重与组合搜索

### 通用解题模板

```cpp
class Solution {
public:
    vector<vector<int>> kSumLike(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        // 组合类双指针题通常先固定前若干位。
        for (int first = 0; first + 2 < (int)nums.size(); ++first) {
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }

            int left = first + 1;
            int right = (int)nums.size() - 1;
            while (left < right) {
                long long sum = (long long)nums[first] + nums[left] + nums[right];
                if (sum < target) {
                    ++left;
                } else if (sum > target) {
                    --right;
                } else {
                    ans.push_back({nums[first], nums[left], nums[right]});
                    // 命中一个组合后，跳过两侧重复值，防止重复答案。
                    while (left < right && nums[left] == nums[left + 1]) {
                        ++left;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        --right;
                    }
                    ++left;
                    --right;
                }
            }
        }

        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `15. 3Sum` | 待提交验证，源码逻辑检查通过 | 排序、固定首位、左右收缩和三处去重都完整，已经抓住组合搜索的核心节奏。 | 外层边界可以更精确地写成还剩两个数；复盘时重点说明每次指针移动的依据。 | [查看](../leetcode-reviews/2026-05-03-15-3sum.md) |
| `16. 3Sum Closest` | 待提交验证，源码逻辑检查通过 | 能把精确命中题迁移到“维护最接近答案”，并保留提前返回。 | `ans = 1e7` 属于哨兵值，推荐用真实三元组初始化；答案更新时机可以前置到移动指针之前。 | [查看](../leetcode-reviews/2026-05-03-16-3sum-closest.md) |
| `18. 4Sum` | 待提交验证，源码逻辑检查通过 | 两层固定加左右指针的整体模板正确，固定层和命中后的去重都处理到了。 | 类型提升可以更早写成 `(long long)nums[a] + nums[b]`；四数题还要复盘上下界剪枝。 | [查看](../leetcode-reviews/2026-05-03-18-4sum.md) |

- 暴露问题：今天的主线完成得很扎实，已经能把“排序后固定若干位，再用左右指针收缩”的模式迁移到三数、最接近三数和四数；主要风险集中在循环边界表达、答案初始化的稳健性，以及 `4Sum` 类型提升和剪枝边界的模板化。
- 下一步安排：进入第 4 天可变窗口入门，重点从“组合搜索的去重边界”切换到“窗口是否合法、何时收缩左边界”的判断。

## 进度更新 - 2026-05-04

- 今日完成：`209. Minimum Size Subarray Sum`、`3. Longest Substring Without Repeating Characters`、`904. Fruit Into Baskets`
- 当前主题：第 4 天 - 可变窗口入门

### 通用解题模板

- 适用条件：题目要求在连续区间内维护某种合法性，并且右边界扩张后可以通过左边界单调右移恢复合法或优化答案。
- 核心骨架：右指针逐步纳入元素，维护窗口状态；当窗口满足收缩条件或变成非法时移动左指针；在窗口达标或恢复合法的时机更新答案。
- 关键边界：先明确答案是在收缩前更新还是收缩后更新；计数类窗口中，元素数量归零后要删除对应状态；空输入或无答案时要有稳定返回值。
- 复杂度：时间 `O(n)`，空间通常为 `O(1)` 或 `O(k)`，取决于窗口状态需要保存多少种元素。

```cpp
class Solution {
public:
    int slidingWindowTemplate(vector<int>& nums) {
        int left = 0;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            // 1. 把 nums[right] 加入当前窗口，并更新窗口状态。

            while (/* 当前窗口需要收缩 */) {
                // 2. 如果当前窗口已经是候选答案，先记录再收缩。
                // 3. 移出 nums[left]，并保持窗口状态准确。
                ++left;
            }

            // 4. 如果收缩后窗口合法，在这里记录最长或最优答案。
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `209. Minimum Size Subarray Sum` | 待提交验证，源码逻辑检查通过 | 能在窗口和达标后立刻记录长度，并持续收缩左边界寻找更短答案。 | 复盘时重点说清“为什么正数数组可以这样单调收缩”，以及答案必须在移出左端前更新。 | [查看](../leetcode-reviews/2026-05-04-209-minimum-size-subarray-sum.md) |
| `3. Longest Substring Without Repeating Characters` | 待提交验证，源码逻辑检查通过 | 用频次数组维护无重复窗口，重复时只围绕新加入字符收缩，逻辑直接。 | `128` 字符表依赖常见 ASCII 输入；复盘时要说明加入前窗口已经合法，所以只需要处理 `s[r]` 的重复。 | [查看](../leetcode-reviews/2026-05-04-3-longest-substring-without-repeating-characters.md) |
| `904. Fruit Into Baskets` | 待提交验证，源码逻辑检查通过 | 能把篮子限制转成窗口内类型数量限制，并在计数归零时删除类型。 | `ans=1` 依赖非空输入；后续模板化建议从 `0` 初始化，让边界更稳。 | [查看](../leetcode-reviews/2026-05-04-904-fruit-into-baskets.md) |

- 暴露问题：今天整体已经抓住可变窗口的核心节奏；主要需要继续强化三件事：窗口合法性的口头定义、答案更新是在收缩前还是收缩后、计数状态归零后的清理。
- 下一步安排：进入第 5 天固定窗口与频次窗口，重点观察窗口长度固定后，状态比较和结果记录时机如何变化。

## 进度更新 - 2026-05-05

- 今日完成：`438. Find All Anagrams in a String`、`567. Permutation in String`、`424. Longest Repeating Character Replacement`
- 当前主题：第 5 天 - 固定窗口与频次窗口

### 通用解题模板

- 适用条件：题目要求比较一个连续窗口与目标频次是否一致，或要求在窗口中根据字符频次判断当前长度是否合法。
- 核心骨架：用固定大小数组维护窗口频次或频次差值；右端加入新字符，窗口超长时移出左端；用一个聚合状态避免每轮重新比较整张频次表。
- 关键边界：固定窗口题必须等窗口长度达到目标长度后再判断；差值为 `0` 的种类变化要在每次加减前后同步更新；最长窗口题要说清最高频状态是否需要回退。
- 复杂度：时间 `O(n)`，空间 `O(1)`，其中字符集大小固定为 26。

```cpp
class Solution {
public:
    bool fixedFrequencyWindow(string target, string text) {
        vector<int> diff(26, 0);
        int different = 0;

        auto addDiff = [&](int idx, int delta) {
            int before = diff[idx];
            int after = before + delta;
            if (before == 0 && after != 0) {
                ++different;
            } else if (before != 0 && after == 0) {
                --different;
            }
            diff[idx] = after;
        };

        for (char ch : target) {
            addDiff(ch - 'a', 1);
        }

        int windowSize = target.size();
        for (int right = 0; right < (int)text.size(); ++right) {
            addDiff(text[right] - 'a', -1);
            if (right >= windowSize) {
                // 固定窗口只保留和目标串等长的字符。
                addDiff(text[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                return true;
            }
        }

        return false;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `438. Find All Anagrams in a String` | 待提交验证，源码逻辑检查通过 | 用 `cnt + num` 维护频次差值，能在常数时间判断固定窗口是否匹配。 | `num` 的增减依赖差值跨过 `0` 的瞬间，复盘时要把正数、零、负数三种含义讲清。 | [查看](../leetcode-reviews/2026-05-05-438-find-all-anagrams-in-a-string.md) |
| `567. Permutation in String` | 待提交验证，源码逻辑检查通过 | 很好地迁移了 `438` 的固定窗口模板，并把记录所有答案改成命中即返回。 | 建议显式处理 `s1` 长于 `s2` 的边界，提升代码表达稳定性。 | [查看](../leetcode-reviews/2026-05-05-567-permutation-in-string.md) |
| `424. Longest Repeating Character Replacement` | 待提交验证，源码逻辑检查通过 | 能用窗口长度和最高频字符数判断替换次数是否超限，代码达到常见最优复杂度。 | 重点复盘 `maxCnt` 不随左边界回退的正确性，以及为什么超限时移动一次左边界即可。 | [查看](../leetcode-reviews/2026-05-05-424-longest-repeating-character-replacement.md) |

- 暴露问题：今天频次窗口迁移做得很好，`438` 和 `567` 已经形成同一套差值模板；主要复盘点是把 `num/different` 的语义讲成“差值不为零的字符种类数”，以及理解 `424` 中历史最高频不回退的原因。
- 下一步安排：进入第 6 天覆盖需求与窗口收缩，重点从“窗口是否等长匹配”切换到“什么时候已经满足需求、满足后如何尽量缩短或计数”。

## 加练记录 - 2026-05-05

- 今日加练：`1004. Max Consecutive Ones III`、`76. Minimum Window Substring`
- 当前主题：可变窗口的合法性维护与覆盖型收缩

### 通用解题模板

- 适用条件：题目围绕连续区间提问，右端扩张后可以用一个聚合状态判断窗口是否合法、是否已满足需求，左端再单调右移恢复合法或缩短候选答案。
- 核心骨架：右指针纳入新元素并更新窗口状态；当窗口非法或已经满足目标时，根据题目要求移动左指针；最长合法窗口在恢复合法后记录答案，最短覆盖窗口在移出左端前记录答案。
- 关键边界：先明确状态里的“缺少、超限、冗余”分别是什么；覆盖型窗口要处理重复需求；记录答案的时机不能和收缩顺序写反。
- 复杂度：时间 `O(n)`，空间通常为 `O(1)` 或 `O(C)`，其中 `C` 是字符集或状态种类大小。

```cpp
class Solution {
public:
    int variableWindowTemplate(vector<int>& nums, int limit) {
        int left = 0;
        int state = 0;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            // 右端进入窗口，更新 state。

            while (/* 当前窗口需要收缩 */) {
                // 收缩前或收缩后更新答案，取决于题目要最短覆盖还是最长合法。
                // 移出 nums[left]，并同步修正 state。
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `1004. Max Consecutive Ones III` | 待提交验证，源码逻辑检查通过 | 能把翻转次数准确转成窗口内 `0` 的数量，非法后持续收缩到重新合法。 | 复盘时重点说清“窗口内 0 的个数就是需要使用的修改次数”，以及为什么合法后更新最长答案。 | [查看](../leetcode-reviews/2026-05-05-1004-max-consecutive-ones-iii.md) |
| `76. Minimum Window Substring` | 待提交验证，源码逻辑检查通过 | 用 `diff + different` 维护覆盖需求，满足后先记录再收缩，已经抓住困难窗口题的关键节奏。 | 重点复盘 `diff > 0` 表示仍缺字符、`diff < 0` 表示窗口冗余；另外注意 C++ 中字符下标建议转成 `unsigned char`。 | [查看](../leetcode-reviews/2026-05-05-76-minimum-window-substring.md) |

- 暴露问题：今天加练整体很强，`1004` 的最长合法窗口和 `76` 的最短覆盖窗口都写到了线性复杂度；主要需要复盘的是“答案在收缩前还是收缩后更新”这件事，因为这正是两类窗口最容易混淆的分界。
- 下一步安排：补齐 `713. Subarray Product Less Than K`，把第 6 天的计数型窗口也串上；完成后再整体比较最长、最短、计数三种窗口题的记录时机。

## 进度更新 - 2026-05-06

- 今日完成：`713. Subarray Product Less Than K`
- 已提前完成且昨日已总结：`1004. Max Consecutive Ones III`、`76. Minimum Window Substring`
- 当前主题：第 6 天 - 覆盖需求与窗口收缩

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `713. Subarray Product Less Than K` | 待提交验证，源码逻辑检查通过 | 能维护乘积窗口，并在恢复合法后一次性统计以右端点结尾的所有合法子数组。 | 建议显式处理 `k <= 1`；复盘时重点说明为什么正数约束支持左端单调收缩，以及为什么贡献是 `r - l + 1`。 | [查看](../leetcode-reviews/2026-05-06-713-subarray-product-less-than-k.md) |

- 暴露问题：`713` 的核心计数逻辑已经正确，主要改进点是把无解边界前置，让代码表达更稳；今天不重复总结昨天已经处理过的 `1004` 和 `76`。
- 下一步安排：进入第 7 天综合迁移与模拟面试，重点把本周的相向双指针、区间推进、困难窗口计数放在同一天里做模式辨析。

## 第 7 天 - 综合迁移与模拟面试

今天承接：第 6 天已经补齐“计数、最长、最短”三类窗口记录时机，接下来重点训练先辨题型、再选择推进方式。

1. `986. Interval List Intersections` (`中等`) - 先做区间列表题，练习根据当前交叠关系推进边界。
2. `42. Trapping Rain Water` (`困难`) - 用空间压缩后的边界信息解释每一步移动，避免只记公式。
3. `992. Subarrays with K Different Integers` (`困难`) - 作为窗口计数拔高题，训练把目标数量拆成更容易统计的形式。

完成后重点复盘：每题先写出“当前状态代表什么”和“移动哪一侧的依据”，再对照代码检查答案记录时机是否一致。
