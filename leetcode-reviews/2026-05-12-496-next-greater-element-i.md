# 题解点评 - 496. Next Greater Element I

## 基本信息

- 日期：2026-05-12
- 主题：栈与队列 - 下一个更大与温度等待
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/496.next-greater-element-i.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 从右向左扫描 `nums2`，用栈保存当前位置右侧仍可能成为下一个更大值的候选值。
2. 对当前值 `nums2[i]`，不断弹出栈顶中比它小的值，因为这些值不可能成为它左侧元素的更优候选。
3. 弹出结束后，如果栈为空，当前值没有下一个更大值；否则栈顶就是当前值右侧第一个更大值。
4. 把每个 `nums2` 元素到其下一个更大值的映射写入 `mp`。
5. 最后按 `nums1` 的顺序查询映射，得到答案。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`
- 空间复杂度：`O(n)`
- 复杂度来源：`nums2` 每个元素最多入栈和出栈一次；哈希表保存 `nums2` 中每个值的答案。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n1=nums1.size(), n2=nums2.size();
        unordered_map<int, int> mp; // 每个 nums2 元素对应的下一个更大值。
        stack<int> st;             // 保存右侧候选更大值，栈顶离当前位置最近。

        for(int i=n2-1; i>=0; i--) {
            while(!st.empty() && st.top() < nums2[i]) {
                st.pop(); // 更小的值会被当前值挡住。
            }
            if(st.empty()) {
                mp[nums2[i]] = -1;
            } else {
                mp[nums2[i]] = st.top();
            }
            st.push(nums2[i]);
        }

        vector<int> ans(n1, 0);
        for(int i=0; i<n1; i++) {
            ans[i] = mp[nums1[i]];
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 候选值维护 | 从右向左维护右侧更大候选。 | 正确命中单调栈核心。 | 复盘时说清被弹出的值为什么永远不会再成为答案。 |
| 存值还是存下标 | 本题保存值即可。 | 因为 `nums2` 元素互不相同，且答案要求返回值。 | 和 `739` 对比：需要距离时必须保存下标。 |
| 比较条件 | 使用 `<` 弹出更小值。 | 本题无重复元素，正确。 | 遇到可能重复的题，要重新检查是否应弹出 `<=`。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 复杂度最优，映射构建清晰。 | 从右向左写法需要解释栈顶为什么是“第一个”更大值。 | 适合本题直接提交。 |
| 推荐最优解 | 从左向右结算等待元素，更贴近“等待被更大值解决”的通用模板。 | 本质复杂度相同。 | 更容易迁移到回填答案类题。 |

## 最优解法

1. 用一个栈保存还没有找到下一个更大值的元素。
2. 从左到右扫描 `nums2`，当前值如果大于栈顶，就说明当前值是栈顶元素遇到的第一个更大值。
3. 持续弹出所有被当前值解决的元素，并记录映射。
4. 扫描结束后，仍在栈中的元素没有更大值，映射为 `-1`。
5. 按 `nums1` 查询映射。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        vector<int> decreasing;

        for (int value : nums2) {
            while (!decreasing.empty() && decreasing.back() < value) {
                // 当前 value 是这些等待元素遇到的第一个更大值。
                nextGreater[decreasing.back()] = value;
                decreasing.pop_back();
            }
            decreasing.push_back(value);
        }

        while (!decreasing.empty()) {
            nextGreater[decreasing.back()] = -1;
            decreasing.pop_back();
        }

        vector<int> ans;
        ans.reserve(nums1.size());
        for (int value : nums1) {
            ans.push_back(nextGreater[value]);
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 栈保存右侧候选更大值。 | 栈保存等待被当前值解决的元素。 | 两种都正确，左到右版本更像通用回填模板。 |
| 更新逻辑 | 当前值弹出右侧更小候选，再记录当前答案。 | 当前值解决栈中更小元素。 | 复盘两种方向，理解单调性本质。 |
| 边界处理 | 无更大值映射为 `-1`。 | 扫描结束统一标记 `-1`。 | 都稳定。 |
| 复杂度 | `O(n+m)` / `O(n)` | `O(n+m)` / `O(n)` | 已达到最优。 |

## 下一步建议

进入环形数组版本。重点观察：当数组变成环形时，扫描次数和入栈次数不能混在一起。

## 后续练习

1. `503. Next Greater Element II` - 把等待更大值扩展到环形数组。
2. `739. Daily Temperatures` - 把返回更大值迁移成返回下标距离。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/496.next-greater-element-i.cpp`
- 新函数名：`nextGreaterElementOpt`
- 保留用户原实现：是
