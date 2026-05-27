# 题解点评 - 658. Find K Closest Elements

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 7 天综合复盘与设计迁移
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/658.find-k-closest-elements.cpp`
- 资料来源：leetcode.ca、既有本地点评
- 查询日期：2026-05-27

## 用户思路概述

1. 先二分找到第一个大于等于 `x` 的插入位置。
2. 从插入位置左右两侧扩张，每次选距离 `x` 更近的一侧。
3. 距离相等时选择左侧，满足题目中较小值优先的规则。
4. 扩张 `k` 次后返回中间连续区间。

## 用户解法复杂度

- 时间复杂度：`O(log n + k)`
- 空间复杂度：`O(k)`，用于返回答案；不计返回值为 `O(1)`。
- 复杂度来源：一次二分定位，加上 `k` 次双向扩张。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n=arr.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(arr[m] >= x) r = m; // 找第一个 >= x 的位置。
            else l = m+1;
        }

        int left=l-1, right=l; // 从插入点两侧向外扩张。
        for(int i=0; i<k; i++) {
            if(left >= 0 && right < n) {
                if(x-arr[left] <= arr[right]-x) left--; // 平局选更小元素。
                else right++;
            } else if(left < 0) {
                right++;
            } else {
                left--;
            }
        }

        vector<int> ans;
        for(int i=left+1; i<right; i++) ans.push_back(arr[i]);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 插入点 | 定位准确 | 能快速找到答案附近区域 | 保留为直观解释版本 |
| 平局规则 | 使用 `<=` 选择左侧 | 正确处理同距离时较小值优先 | 这是本题最容易错的比较符 |
| 连续窗口 | 源码已有窗口左端二分 `Opt` | 已掌握更模板化写法 | 复盘时把答案视为长度为 `k` 的窗口 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 直观，容易解释，边界处理完整 | 分支略多 | 适合先写出稳定可接受解 |
| 推荐最优解 | 直接二分窗口左端，表达更紧凑 | 比较式需要手推理解 | 适合本周“结果区间边界”迁移 |

## 最优解法

1. 答案一定是排序数组中的一段长度为 `k` 的连续窗口。
2. 二分窗口左端，范围是 `[0, n-k]`。
3. 比较 `arr[middle]` 与 `arr[middle+k]` 哪个离 `x` 更远；左侧更远就整体右移，否则保留当前左端。

- 最优时间复杂度：`O(log(n-k)+k)`
- 最优空间复杂度：`O(k)`，不计返回值为 `O(1)`。

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
| 状态定义 | 插入点两侧扩张 | 窗口左端 | 识别“答案是连续区间” |
| 更新逻辑 | 每次选一个元素 | 每次排除一批窗口左端 | 从局部扩张升级为边界查找 |
| 边界处理 | 手动处理左右越界 | 搜索范围天然保护 | 优先让区间定义消化越界 |
| 复杂度 | `O(log n+k)` | `O(log(n-k)+k)` | 两者都可接受 |

## 下一步建议

保留双向扩张作为解释版本，面试或复盘时优先补充窗口左端二分。

## 后续练习

1. `540. Single Element in a Sorted Array` - 继续看结构变化如何决定边界。
2. `981. Time Based Key-Value Store` - 把边界查找迁移到设计题时间轴。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/658.find-k-closest-elements.cpp`
- 新函数名：`findClosestElementsOpt`
- 保留用户原实现：是
