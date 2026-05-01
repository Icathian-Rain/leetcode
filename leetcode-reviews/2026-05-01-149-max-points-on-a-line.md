# 题解点评 - 149. Max Points on a Line

## 基本信息

- 日期：2026-05-01
- 主题：数组与哈希 - 复杂哈希建模与模拟面试
- 难度：困难
- 本次结果：通过（用户反馈已完成，本地语法检查通过）
- 对应源码：`src/149.max-points-on-a-line.cpp`
- 资料来源：LeetCode 官方题页（题号和题名）+ LeetCode Wiki（题意、约束、难度与典型解法）
- 查询日期：2026-05-01

## 用户思路概述

你枚举每个点作为锚点 `i`，再枚举它之后的点 `j`，用 `(my, mx)` 表示从 `i` 到 `j` 的斜率方向。为了让同一条斜率落到同一个 key，你对横线、竖线和普通斜率分别做了归一化：竖线统一成 `(1, 0)` 的效果，横线统一成 `(0, 1)` 的效果，普通斜率用最大公约数约分，并把符号归到同一侧。每个锚点下，相同斜率的点数加一就是经过该锚点的同线点数。

这是本题常见的 `O(n^2)` 哈希斜率做法。

## 主要问题

- 整体算法正确，当前 LeetCode 约束说明所有点唯一，所以不需要额外统计重合点。
- `mp[my + mx * 20001]` 这个整数 key 能在当前坐标范围内工作，但依赖 `[-10000, 10000]` 这个约束。面试里更推荐用 `(dx, dy)` pair 或字符串 key，避免魔法常数。
- 符号归一写得基本稳，但读者需要跟着多个分支推演。把“竖线、横线、普通斜率约分、统一 dx 符号”封装成一个小函数，会更容易复盘。

## 做得好的地方

- 正确意识到浮点数斜率不适合做哈希 key，改用整数比值规避精度问题。
- 用 `gcd(abs(mx), abs(my))` 约分，保证同一斜率不会因为比例不同而分散到多个 key。
- 外层的提前退出条件能减少一些无意义枚举，说明你已经在关注本题的复杂度边界。

## 最优解法

推荐最优解仍然是枚举锚点 + 规范化方向向量。关键不变量是：对固定锚点 `i`，任意点 `j` 与 `i` 形成的归一化方向 `(dx, dy)` 相同，当且仅当它们和 `i` 在同一条直线上。每个锚点统计一次斜率频次，最大频次加一就是包含锚点的最多点数。

- 时间复杂度：`O(n^2)`
- 空间复杂度：`O(n)`

## 最优解代码

```cpp
class Solution {
    struct PairHash {
        size_t operator()(const pair<int, int>& p) const {
            long long key = (static_cast<long long>(p.first) << 32) ^ (p.second & 0xffffffffLL);
            return hash<long long>()(key);
        }
    };

    int gcdInt(int a, int b) {
        return b == 0 ? a : gcdInt(b, a % b);
    }

    pair<int, int> normalize(int dx, int dy) {
        if (dx == 0) {
            return {0, 1};
        }
        if (dy == 0) {
            return {1, 0};
        }

        int g = gcdInt(abs(dx), abs(dy));
        dx /= g;
        dy /= g;

        if (dx < 0) {
            dx = -dx;
            dy = -dy;
        }

        return {dx, dy};
    }

public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }

        int ans = 1;
        for (int i = 0; i < n; ++i) {
            unordered_map<pair<int, int>, int, PairHash> count;

            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                pair<int, int> slope = normalize(dx, dy);
                ans = max(ans, ++count[slope] + 1);
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

你的解法已经抓住了最难的点：斜率必须离散化成可哈希的规范 key。主要改进是把 key 的构造从“依赖坐标范围的整数编码”换成“语义明确的 pair”，这样题目约束变化时也不容易埋雷。

## 下一步建议

建议把当前题的斜率 key 规范化函数单独重写一遍，并补三个边界测试：竖线、横线、负斜率。做到这一步，本周的复杂哈希建模目标就很完整了。

## 后续练习

1. `447. Number of Boomerangs` - 继续枚举锚点，用距离平方作为哈希 key。
2. `939. Minimum Area Rectangle` - 用点集和坐标组合做几何哈希，适合迁移本题的 key 设计意识。
