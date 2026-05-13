# 题解点评 - 84. Largest Rectangle in Histogram

## 基本信息

- 日期：2026-05-13
- 主题：栈与队列 - 单调结构与区间贡献
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/84.largest-rectangle-in-histogram.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 在高度数组首尾各加入高度 `0` 的哨兵，减少空栈和尾部清算的特殊处理。
2. 用栈保存高度递增的柱子下标。
3. 扫描到更矮的柱子时，持续弹出比当前柱子高的柱子。
4. 对每个弹出的柱子 `mid`，当前下标 `i` 是右侧第一个更矮位置，弹出后新的栈顶是左侧第一个更矮位置。
5. 用 `heights[mid] * (right - left - 1)` 更新最大面积。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个柱子最多入栈、出栈一次；栈保存尚未确定右边界的柱子下标。

## 用户代码注释版

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        heights.insert(heights.begin(), 0); // 左右哨兵，方便统一结算。
        stack<int> st;
        st.push(0);
        int ans=0;
        for(int i=1; i<heights.size(); i++) {
            while(!st.empty() && heights[st.top()] > heights[i]) {
                int mid=st.top();
                st.pop();
                if(!st.empty()) {
                    int left=st.top(); // 左侧第一个更矮位置。
                    int right=i;       // 右侧第一个更矮位置。
                    int w=right-left-1;
                    int h=heights[mid];
                    ans =max(ans, h*w);
                }
            }
            st.push(i);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 边界结算 | 能在遇到更矮柱子时结算被弹柱子的最大矩形。 | 命中本题核心。 | 复盘时说清弹出瞬间左右边界都已经确定。 |
| 哨兵处理 | 首尾插入 `0` 简化边界。 | 正确，但会修改输入数组。 | LeetCode 可接受；通用函数可用虚拟哨兵避免改输入。 |
| 单调栈含义 | 栈中下标对应高度递增。 | 正确支持线性复杂度。 | 注意相等高度时用 `>` 或 `>=` 都可，但边界归属不同。 |

## 左侧哨兵与无哨兵的区别

左侧哨兵的作用不是改变算法本质，而是把“左边没有更矮柱子”这个特殊情况统一成一个普通边界。

| 写法 | 左边界含义 | 宽度公式 | 需要额外判断空栈吗 | 主要取舍 |
| --- | --- | --- | --- | --- |
| 有左侧哨兵 `-1` 或高度 `0` 的下标 | 栈底永远代表矩形左边界前一位 | `i - st.top() - 1` | 不需要，只要不弹出哨兵 | 公式统一，代码更稳 |
| 无左侧哨兵 | 弹出后如果栈空，说明矩形可以延伸到下标 `0` | 栈空时 `i`，否则 `i - st.top() - 1` | 需要 | 少一个哨兵，但分支更多 |

无左侧哨兵时，弹出柱子后宽度通常要这样写：

```cpp
int heightIndex = st.top();
st.pop();
int width = st.empty() ? i : i - st.top() - 1;
ans = max(ans, heights[heightIndex] * width);
```

有左侧哨兵时，`st.top()` 始终存在，并且在没有真实左边界时等于 `-1`，所以宽度自然变成 `i - (-1) - 1 = i`。你的当前写法是在数组开头插入高度 `0`，推荐写法是在栈里放 `-1`，两者本质都是让“空栈宽度”变成统一公式。

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 经典单调栈，正确处理首尾边界。 | 直接修改 `heights`；`insert(begin)` 有线性搬移但总复杂度仍为线性。 | 适合本题提交。 |
| 推荐最优解 | 使用虚拟末尾高度和 `-1` 哨兵，不修改输入。 | 代码里的虚拟下标需要解释清楚。 | 更适合长期复用。 |

## 最优解法

1. 栈中保存高度递增的柱子下标，初始放入 `-1` 作为左边界哨兵。
2. 扫描每个下标，并在最后额外使用一个高度 `0` 的虚拟柱子触发清算。
3. 当当前高度小于栈顶高度时，弹出栈顶柱子并计算以它为最低高度的最大矩形。
4. 弹出后栈顶是左侧第一个更矮柱子，当前下标是右侧第一个更矮柱子。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> indexes;
        indexes.push_back(-1);
        int ans = 0;

        for (int i = 0; i <= (int)heights.size(); ++i) {
            int currentHeight = (i == (int)heights.size()) ? 0 : heights[i];
            while (indexes.back() != -1 && heights[indexes.back()] > currentHeight) {
                int heightIndex = indexes.back();
                indexes.pop_back();
                int width = i - indexes.back() - 1;
                // 当前柱子右侧遇到更矮高度，heightIndex 的最大宽度已经确定。
                ans = max(ans, heights[heightIndex] * width);
            }
            indexes.push_back(i);
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 栈保存递增高度下标。 | 同样保存递增高度下标。 | 状态已经正确。 |
| 更新逻辑 | 首尾插入哨兵后统一扫描。 | 用 `-1` 和虚拟末尾高度，不改输入。 | 推荐掌握不修改参数的写法。 |
| 边界处理 | 左右哨兵覆盖开头和尾部清算，宽度公式统一。 | 左侧 `-1` 哨兵覆盖空栈宽度，虚拟末尾高度触发尾部清算。 | 已经抓住困难点；下一步理解无哨兵时为什么要特判空栈。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优。 |

## 下一步建议

这题建议再手推一次 `[2,1,5,6,2,3]`，重点看 `6` 和 `5` 分别在什么时候被弹出、宽度怎么算。

## 后续练习

1. `85. Maximal Rectangle` - 把柱状图最大矩形迁移到二维矩阵。
2. `42. Trapping Rain Water` - 对比“遇到边界结算水量”和本题“遇到更矮结算面积”。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/84.largest-rectangle-in-histogram.cpp`
- 新函数名：`largestRectangleAreaOpt`
- 保留用户原实现：是
