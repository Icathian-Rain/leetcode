# 题解点评 - 1283. Find the Smallest Divisor Given a Threshold

## 基本信息

- 日期：2026-05-26
- 主题：二分查找 - 答案范围与可行性检查
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/1283.find-the-smallest-divisor-given-a-threshold.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 把除数 `m` 作为二分答案，范围从 `1` 到数组最大值。
2. 写 `check(m)` 计算所有 `ceil(nums[i] / m)` 的总和。
3. 如果总和不超过 `threshold`，说明除数 `m` 可行，可以尝试更小除数。
4. 如果总和超过 `threshold`，说明除数太小，需要增大左边界。
5. 最终返回第一个可行除数。

## 用户解法复杂度

- 时间复杂度：`O(n log M)`，其中 `M = max(nums)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次二分检查都扫描数组，答案范围由最大值决定。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n=nums.size();
        int mx=0;
        for(int i=0; i<n; i++) {
            mx=max(mx, nums[i]);
        }
        auto check=[&](int m) {
            int sum=0;
            for(int i=0; i<n; i++) {
                sum += ceil(1.0*nums[i]/m); // 可以改成整数上取整，避免浮点计算。
                if(sum > threshold) {
                    return false;
                }
            }
            return true;
        };

        int l=1, r=mx+1;
        while(l<r) {
            int m=l+(r-l)/2;
            if(check(m)) {
                r=m; // 当前除数可行，保留并继续找更小值。
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
| 单调方向 | 除数越大，求和越小，越容易满足阈值 | 正确建立可行区间 | 复盘时说清可行区间在右侧 |
| 上界选择 | 最大值作为右侧可行上界 | 正确，除数为最大值时每项结果至少降到 1 | 保持这个紧上界 |
| 上取整 | 当前使用浮点 `ceil` | 思路正确，但整数题建议避免浮点 | 改成 `(value + divisor - 1) / divisor` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 二分方向正确，提前退出，边界合理 | 浮点 `ceil` 不如整数表达稳 | 可通过本题 |
| 推荐最优解 | 纯整数上取整，命名更贴合语义 | 本质复杂度相同 | 作为阈值型答案二分模板 |

## 最优解法

1. 在 `[1, max(nums)]` 中二分除数。
2. 对候选除数，使用整数上取整计算结果和。
3. 和不超过 `threshold` 时，除数可行，收缩右边界。
4. 和超过阈值时，除数太小，移动左边界。

- 最优时间复杂度：`O(n log M)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());

        auto canUse = [&](int divisor) {
            int sum = 0;
            for (int value : nums) {
                sum += (value + divisor - 1) / divisor; // 整数上取整。
                if (sum > threshold) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canUse(middle)) {
                right = middle; // 除数可行，保留并继续找更小值。
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
| 状态定义 | `l/r` 表示除数范围 | `left/right` 表示除数范围 | 命名展开即可 |
| 更新逻辑 | 可行收右，不可行收左 | 相同 | 已掌握 |
| 边界处理 | `[1, max+1)` | `[1, max]` | 都正确，统一模板即可 |
| 复杂度 | `O(n log M)` / `O(1)` | 相同 | 已达最优 |

## 下一步建议

做跟练题或进入下一组均可。当前最大收益是把 `875`、`1011`、`1283` 的 `check` 都抽象成“候选答案是否可行”。

## 后续练习

1. `875. Koko Eating Bananas` - 与本题几乎同构，都是整数上取整。
2. `410. Split Array Largest Sum` - 继续训练答案范围和分段可行性。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/1283.find-the-smallest-divisor-given-a-threshold.cpp`
- 新函数名：`smallestDivisorOpt`
- 保留用户原实现：是
