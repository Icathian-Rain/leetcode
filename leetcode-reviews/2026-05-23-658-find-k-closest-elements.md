# 题解点评 - 658. Find K Closest Elements

## 基本信息

- 日期：2026-05-23
- 主题：二分查找 - 综合复盘与设计迁移加练
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/658.find-k-closest-elements.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 先在有序数组中二分找到第一个大于等于 `x` 的位置。
2. 把该位置左侧作为 `left`，该位置本身作为 `right`，形成从插入点向两侧扩张的候选区间。
3. 每次比较 `arr[left]` 与 `arr[right]` 到 `x` 的距离，选择更近的一侧纳入答案范围。
4. 如果一侧越界，就只能从另一侧继续扩张。
5. 扩张 `k` 次后，返回 `(left, right)` 中间的连续区间。

## 用户解法复杂度

- 时间复杂度：`O(log n + k)`
- 空间复杂度：`O(k)`，用于返回答案；不计返回值时为 `O(1)`
- 复杂度来源：先做一次二分定位插入点，再向两侧扩张 `k` 次，最后复制 `k` 个元素。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n=arr.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(arr[m] >= x) {
                r = m; // 找第一个 >= x 的位置，作为右侧候选起点。
            } else {
                l = m+1;
            }
        }
        int left, right;
        left=l-1, right=l; // 从插入点两侧向外选择更近元素。
        for(int i=0; i<k; i++) {
            if(left >= 0 && right < n) {
                if(x-arr[left] <= arr[right]-x) {
                    left--; // 距离相等时选左边，符合题目要求较小元素优先。
                } else {
                    right++;
                }
            } else if(left < 0) {
                right++; // 左侧用完，只能取右侧。
            } else {
                left--; // 右侧用完，只能取左侧。
            }
        }
        vector<int> ans;
        for(int i=left+1; i<right; i++) {
            ans.push_back(arr[i]);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 插入点定位 | 正确使用第一个 `>= x` 的边界 | 能把答案范围定位到目标附近 | 保留这个思路，适合解释直观 |
| 平局规则 | 距离相等时选择左侧 | 符合题目要求较小元素优先 | 这是本题容易错的核心边界 |
| 最优窗口 | 当前写法是 `O(log n + k)` | 已经可接受且很清晰 | 进一步掌握对窗口左端二分的 `O(log(n-k)+k)` 写法 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路直观，平局规则正确，边界处理完整 | 需要手动维护左右越界分支 | 适合先从“插入点扩张”理解本题 |
| 推荐最优解 | 直接二分长度为 `k` 的答案窗口左端，代码更短 | 比较式 `x - arr[mid] > arr[mid+k] - x` 初看不直观 | 适合作为有序数组中连续答案段的标准模板 |

## 最优解法

1. 最终答案一定是原数组中的一段长度为 `k` 的连续窗口。
2. 因此只需要二分窗口左端，范围是 `[0, n - k]`。
3. 对于候选左端 `middle`，比较窗口左外侧 `arr[middle]` 和右外侧 `arr[middle + k]` 哪边离 `x` 更远。
4. 如果左侧更远，答案窗口应右移；否则当前窗口仍可能是最靠左的最优窗口。

- 最优时间复杂度：`O(log(n - k) + k)`
- 最优空间复杂度：`O(k)`，用于返回答案；不计返回值时为 `O(1)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - k;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (x - arr[middle] > arr[middle + k] - x) {
                left = middle + 1; // 左端太远，答案窗口应整体右移。
            } else {
                right = middle; // 当前窗口仍可能是最靠左的最优窗口。
            }
        }

        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 插入点两侧扩张 | 二分答案窗口左端 | 继续训练“答案是一段连续区间”这个建模 |
| 更新逻辑 | 每次选左右更近元素 | 每次排除一批不可能的窗口左端 | 面试中可以先讲扩张，再给窗口二分优化 |
| 边界处理 | 手动处理左右越界 | 搜索范围 `[0, n-k]` 天然避免越界 | 窗口二分代码更紧凑 |
| 复杂度 | `O(log n + k)` | `O(log(n-k) + k)` | 两者都可接受，窗口二分更模板化 |

## 下一步建议

做跟练题或保留两种写法都可以。当前实现已经稳定，下一步重点是把“连续答案段”识别成可二分窗口左端的信号。

## 后续练习

1. `34. Find First and Last Position of Element in Sorted Array` - 继续巩固边界和连续答案段。
2. `540. Single Element in a Sorted Array` - 练习用结构变化定位答案位置。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/658.find-k-closest-elements.cpp`
- 新函数名：`findClosestElementsOpt`
- 保留用户原实现：是
