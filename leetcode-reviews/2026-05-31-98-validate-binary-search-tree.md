# 题解点评 - 98. Validate Binary Search Tree

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树基础判断
- 难度：中等
- 本次结果：有边界风险，主体思路正确
- 对应源码：`src/98.validate-binary-search-tree.cpp`
- 资料来源：LeetCode 官方题目页、检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. 使用中序遍历验证 BST，因为合法 BST 的中序结果严格递增。
2. 用成员变量 `mv` 记录上一个访问到的节点值。
3. 先递归验证左子树。
4. 当前节点必须大于 `mv`，否则返回 false。
5. 更新 `mv` 后继续验证右子树。

## 用户解法复杂度

- 时间复杂度：`O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：每个节点访问一次；递归栈深度为树高。

## 用户代码注释版

```cpp
using ll=long long;
class Solution {
public:
    ll mv = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root==nullptr) return true;
        // 中序遍历先验证左子树。
        bool left = isValidBST(root->left);
        // 当前值必须严格大于上一个中序访问值。
        if(mv < root->val) mv = root->val;
        else return false;
        bool right = isValidBST(root->right);
        return left && right;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| BST 全局性质 | 用中序严格递增验证 | 思路正确，能覆盖跨祖先约束 | 这是可行最优方案 |
| 初始边界 | `mv = LONG_MIN` | 在 Windows 上 `LONG_MIN` 可能等于 `-2^31`，节点最小值会误判 | 使用 `LLONG_MIN` 或上下界递归 |
| 成员状态 | `mv` 是成员变量 | LeetCode 单次调用通常可过，多次调用会残留 | 推荐用参数或局部变量封装 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 抓住中序递增本质，代码短 | 初始值和成员状态有边界风险 | 节点值范围明确、状态能重置时 |
| 推荐最优解 | 用开区间上下界表达全局约束，无初始值撞边界 | 需要理解祖先限制会向下传递 | 验证 BST 最稳模板 |

## 最优解法

1. 对每个节点维护允许取值的开区间 `(lower, upper)`。
2. 根节点初始范围为 `(-inf, +inf)`。
3. 左子树上界收缩为当前节点值，右子树下界收缩为当前节点值。
4. 任意节点不在开区间内就返回 false。

- 最优时间复杂度：`O(n)`。
- 最优空间复杂度：`O(h)`。

### 最优解代码

```cpp
class Solution {
    bool check(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) {
            return true;
        }

        // 必须满足祖先传下来的全局开区间，而不只是父子大小关系。
        if (root->val <= lower || root->val >= upper) {
            return false;
        }
        return check(root->left, lower, root->val) &&
               check(root->right, root->val, upper);
    }

public:
    bool isValidBST(TreeNode* root) {
        return check(root, LLONG_MIN, LLONG_MAX);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 上一个中序值 `mv` | 当前节点合法开区间 | 上下界更直接表达全局约束 |
| 更新逻辑 | 中序访问后更新 `mv` | 左右子树分别收缩范围 | 避免初始哨兵撞边界 |
| 边界处理 | `LONG_MIN` 有风险 | `LLONG_MIN/LLONG_MAX` 安全 | 重点修正 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 同阶最优 |

## 下一步建议

补边界测试。特别测单节点 `[-2147483648]`，当前写法在部分平台上会误判。

## 后续练习

1. `230. Kth Smallest Element in a BST` - 继续利用中序有序性。
2. `530. Minimum Absolute Difference in BST` - 练习同样的中序相邻值模式。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/98.validate-binary-search-tree.cpp`
- 新函数名：`isValidBSTOpt`
- 保留用户原实现：是
