# 题解点评 - 875. Koko Eating Bananas

## 基本信息

- 日期：2026-05-26
- 主题：二分查找 - 答案范围与可行性检查
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/875.koko-eating-bananas.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 把吃香蕉速度 `m` 作为二分答案，最小速度为 `1`，最大速度为最大堆香蕉数。
2. 写 `check(m)` 计算用速度 `m` 吃完所有堆需要的小时数。
3. 如果总小时数不超过 `h`，说明速度 `m` 可行，可以继续尝试更小速度。
4. 如果总小时数超过 `h`，说明速度太慢，需要增大左边界。
5. 循环结束返回第一个可行速度。

## 用户解法复杂度

- 时间复杂度：`O(n log M)`，其中 `M = max(piles)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次二分检查都扫描所有香蕉堆，答案范围长度与最大堆大小有关。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n=piles.size();
        int l=1, r=0;
        for(int i=0; i<n; i++) {
            r = max(r, piles[i]); // 最大速度取最大堆香蕉数即可。
        }
        r++; // 使用左闭右开区间 [1, max + 1)。

        auto check=[&](int m) {
            int total=0;
            for(int i=0; i<n; i++) {
                total += ceil(1.0*piles[i]/m); // 计算每堆需要小时数；可改成整数上取整。
                if(total > h) {
                    return false; // 提前退出，避免无意义累加。
                }
            }
            return true;
        };

        while(l<r) {
            int m=l+(r-l)/2;
            if(check(m)) {
                r=m; // m 可行，保留它继续找更小可行速度。
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
| 答案单调性 | 能把速度越大越容易完成建模成单调判断 | 正确命中答案二分核心 | 每道答案二分题先写出“可行区间”方向 |
| 上界选择 | 使用最大堆作为可行上界 | 合理且紧 | 保持先找上下界再写循环的习惯 |
| 上取整 | 当前用浮点 `ceil` | 通常能过，但整数题更推荐纯整数计算 | 使用 `(pile + speed - 1) / speed` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 二分范围和 `check` 方向正确，有提前退出 | 浮点 `ceil` 不如整数上取整稳 | 可通过本题，适合当前训练目标 |
| 推荐最优解 | 全程整数计算，变量命名更语义化 | 本质复杂度相同 | 作为答案二分题标准写法 |

## 最优解法

1. 在速度范围 `[1, maxPile]` 中二分。
2. `canFinish(speed)` 计算当前速度下总小时数。
3. 总小时数不超过 `h` 时，速度可行，右边界收缩到 `speed`。
4. 否则速度不可行，左边界移动到 `speed + 1`。

- 最优时间复杂度：`O(n log M)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        auto canFinish = [&](int speed) {
            long long hours = 0;
            for (int pile : piles) {
                hours += (pile + speed - 1) / speed; // 整数上取整，避免浮点误差。
                if (hours > h) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canFinish(middle)) {
                right = middle; // 当前速度可行，继续尝试更小速度。
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
| 状态定义 | `l/r` 表示速度范围 | `left/right` 表示速度范围 | 命名展开更利于复盘 |
| 更新逻辑 | 可行收右，不可行收左 | 相同 | 已掌握 |
| 边界处理 | `[1, max+1)` 半开区间 | `[1, max]` 闭合可行范围 | 两种都可以，统一自己熟悉的模板 |
| 复杂度 | `O(n log M)` / `O(1)` | 相同 | 已达最优 |

## 下一步建议

做跟练题即可。重点把 `check` 函数写成纯整数逻辑，并在写循环前说清“可行速度区间在右侧”。

## 后续练习

1. `1011. Capacity To Ship Packages Within D Days` - 同样是找最小可行值，`check` 改成模拟装载。
2. `1283. Find the Smallest Divisor Given a Threshold` - 同样有整数上取整和阈值约束。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/875.koko-eating-bananas.cpp`
- 新函数名：`minEatingSpeedOpt`
- 保留用户原实现：是
