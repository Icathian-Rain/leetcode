# 题解点评 - 77. Combinations

## 基本信息

- 日期：2026-06-05
- 主题：回溯 / 固定长度组合边界
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/77.combinations.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/combinations/`
- 查询日期：2026-06-05

## 用户思路概述

1. 用 `comb` 维护当前已经选择的数字，用 `ans` 收集所有长度为 `k` 的组合。
2. `dfs(n, k, idx)` 表示下一次从 `idx` 开始向后选择，递归进入下一层时传入 `i + 1`，保证组合按升序生成。
3. 当 `comb.size() == k` 时收集当前路径并返回。
4. 用 `need = k - comb.size()` 计算还需要选择几个数，并把循环上界控制在 `n - need + 1`，剪掉剩余数量不足的分支。

## 用户解法复杂度

- 时间复杂度：`O(C(n, k) * k)`
- 空间复杂度：`O(k)`，不计返回结果
- 复杂度来源：每个合法组合会被生成一次，复制进答案时需要 `O(k)`；递归路径最长为 `k`。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> comb;

    void dfs(int n, int k, int idx) {
        if (comb.size() == k) {
            ans.push_back(comb); // 当前路径长度够了，形成一个合法组合。
            return;
        }

        int need = k - comb.size(); // 还需要选择的数字个数。
        for (int i = idx; i <= n - need + 1; i++) {
            comb.push_back(i);     // 选择当前数字。
            dfs(n, k, i + 1);      // 下一层只能从更大的数字继续选，避免重复组合。
            comb.pop_back();       // 回到同层，尝试下一个数字。
        }
    }

    vector<vector<int>> combine(int n, int k) {
        dfs(n, k, 1);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 起点含义 | `idx` 表示下一次可选择的最小数字 | 能自然避免 `[1,2]` 和 `[2,1]` 这种重复顺序 | 保持“组合题只向后选”的习惯 |
| 剪枝边界 | 使用 `n - need + 1` | 可以避免剩余数字不够时继续递归 | 下次手推 `n=4,k=3` 验证 `+1` 的含义 |
| 状态存放 | `ans/comb` 是成员变量 | 单次提交一般可过，但多次调用同一对象会残留 | 更推荐把结果和路径放在入口局部变量里 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 递归参数清楚，剪枝边界正确 | 成员变量没有在入口清空，复用时不够稳 | 适合本题和固定长度组合题 |
| 推荐最优解 | 状态局部化，调用间互不污染，保留同样剪枝 | 需要熟悉 lambda 捕获写法 | 适合 LeetCode 提交和后续模板迁移 |

## 最优解法

1. 在入口函数内定义 `result` 和 `path`，避免成员变量残留。
2. 递归函数只维护下一次选择起点 `start`。
3. 当路径长度达到 `k` 时收集答案。
4. 每层根据剩余需要数量收紧循环上界。

- 最优时间复杂度：`O(C(n, k) * k)`
- 最优空间复杂度：`O(k)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;

        function<void(int)> dfs = [&](int start) {
            if (static_cast<int>(path.size()) == k) {
                result.push_back(path);
                return;
            }

            // 剩余位置不足时提前停止，避免进入必然无解的分支。
            int need = k - static_cast<int>(path.size());
            for (int value = start; value <= n - need + 1; ++value) {
                path.push_back(value);
                dfs(value + 1);
                path.pop_back();
            }
        };

        dfs(1);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员变量保存答案和路径 | 入口局部变量保存答案和路径 | 减少调用间状态污染 |
| 更新逻辑 | 选择、递归、撤销完整 | 选择、递归、撤销完整 | 当前逻辑可以保留 |
| 边界处理 | 固定长度和数量剪枝正确 | 同样保留数量剪枝 | 继续巩固上界推导 |
| 复杂度 | `O(C(n,k)*k)` | `O(C(n,k)*k)` | 主要优化点是稳定性而非数量级 |

## 下一步建议

进入同一主题的目标和约束组合题。重点观察：当递归参数除了起点，还要同时表达“剩余数量”和“剩余目标”时，终止条件应该怎么排先后。

## 后续练习

1. `216. Combination Sum III` - 固定长度之外再加入目标和限制。
2. `40. Combination Sum II` - 在输入有重复值时练习结果唯一性。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/77.combinations.cpp`
- 新函数名：`combineOpt`
- 保留用户原实现：是
