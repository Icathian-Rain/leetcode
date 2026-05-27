# 题解点评 - 1011. Capacity To Ship Packages Within D Days

## 基本信息

- 日期：2026-05-26
- 主题：二分查找 - 答案范围与可行性检查
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/1011.capacity-to-ship-packages-within-d-days.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 把船容量作为二分答案，最小容量至少是最大单个包裹重量，最大容量可以是所有包裹总和。
2. 写 `check(m)` 模拟容量为 `m` 时需要多少天送完。
3. 每天从当前剩余容量 `left` 中装包裹，装不下就开启新一天。
4. 如果天数超过 `days`，说明容量不可行；否则容量可行。
5. 二分寻找第一个可行容量。

## 用户解法复杂度

- 时间复杂度：`O(n log S)`，其中 `S = sum(weights) - max(weights)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次检查扫描所有包裹，二分容量范围。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n=weights.size();
        int sum=0, mx=0;
        for(int i=0; i<n; i++) {
            sum+=weights[i];
            mx=max(mx, weights[i]); // 容量至少能装下最大包裹。
        }
        auto check = [&](int m) {
            int left=m;
            int cnt=1;
            for(int i=0; i<n; i++) {
                if(left >= weights[i]) {
                    left -=weights[i];
                } else {
                    cnt+=1; // 当前天装不下，换下一天。
                    left = m-weights[i];
                }
                if(cnt > days) {
                    return false;
                }
            }
            return true;
        };

        int l=mx, r=sum+1;
        while(l<r) {
            int m=l+(r-l)/2;
            if(check(m)) {
                r=m; // 容量可行，继续尝试更小容量。
            } else {
                l=m+1;
            }
        }
        return l;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 上下界 | 用最大包裹和总重量确定范围 | 正确且紧凑 | 这是本题最关键的前置边界 |
| 可行性模拟 | 按顺序装载，超容量开新天 | 正确保留包裹顺序约束 | 复盘时强调不能重排包裹 |
| 状态表达 | 用剩余容量 `left` 模拟 | 正确但命名和 `left` 边界变量容易混淆 | 可改成 `currentLoad`，更贴合装载量 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | `check` 正确，提前退出，边界合理 | `left` 既像剩余容量又像常见二分左边界，复盘略绕 | 可直接提交 |
| 推荐最优解 | 用当前载重模拟，语义更直观 | 本质复杂度相同 | 作为容量类答案二分模板 |

## 最优解法

1. 最小容量为最大包裹重量，最大容量为总重量。
2. 对候选容量 `capacity`，从左到右模拟装包裹。
3. 如果当前天装不下下一个包裹，就开启新一天。
4. 使用天数不超过 `days` 时，容量可行，继续找更小容量。

- 最优时间复杂度：`O(n log S)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);

        auto canShip = [&](int capacity) {
            int usedDays = 1;
            int currentLoad = 0;
            for (int weight : weights) {
                if (currentLoad + weight > capacity) {
                    ++usedDays; // 当前包裹必须放到下一天。
                    currentLoad = 0;
                }
                currentLoad += weight;
                if (usedDays > days) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canShip(middle)) {
                right = middle; // 当前容量可行，继续尝试更小容量。
            } else {
                left = middle + 1;
            }
        }

        return left;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 剩余容量 `left` | 当前载重 `currentLoad` | 后者更直观 |
| 更新逻辑 | 装不下则开新天 | 相同 | 已掌握 |
| 边界处理 | `[max, sum+1)` | `[max, sum]` | 两种都可，注意返回语义 |
| 复杂度 | `O(n log S)` / `O(1)` | 相同 | 已达最优 |

## 下一步建议

进入下一题。建议把这题和 `875` 对照：都是最小可行值，但一个 `check` 是累加小时数，一个 `check` 是顺序分天装载。

## 后续练习

1. `410. Split Array Largest Sum` - 与本题高度相似，只是目标换成分割数组。
2. `1283. Find the Smallest Divisor Given a Threshold` - 继续练习阈值型可行性检查。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/1011.capacity-to-ship-packages-within-d-days.cpp`
- 新函数名：`shipWithinDaysOpt`
- 保留用户原实现：是
