# 题解点评 - 700. Search in a Binary Search Tree

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树基础判断
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/700.search-in-a-binary-search-tree.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki / leetcode.ca 检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. 空节点返回 `nullptr`，表示目标值不存在。
2. 当前节点值等于目标值时，直接返回当前子树根。
3. 当前节点值小于目标值时，只去右子树搜索。
4. 当前节点值大于目标值时，只去左子树搜索。

## 用户解法复杂度

- 时间复杂度：`O(h)`，最坏退化为 `O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：每次根据 BST 性质只递归进入一侧子树，递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // 搜到空节点说明目标值不存在。
        if(root == nullptr) return nullptr;
        if(root->val == val) return root;
        // val 更大，只可能出现在右子树。
        else if(root->val < val) return searchBST(root->right, val);
        // val 更小，只可能出现在左子树。
        else return searchBST(root->left, val);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| BST 查询方向 | 能根据大小关系选择单侧子树 | 正确利用有序结构 | 保持这个判断习惯 |
| 返回值 | 返回命中节点作为子树根 | 符合题意 | 复盘时说清不是返回值，而是返回节点指针 |
| 实现形式 | 使用递归 | 简洁正确，但有栈空间 | 可补迭代版作为最优模板 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 逻辑直接，复杂度正确 | 需要递归栈 | 基础 BST 查询 |
| 推荐最优解 | 迭代写法空间 `O(1)` | 代码略多一行循环 | 高频查询模板 |

## 最优解法

1. 从根节点开始。
2. 当前节点为空或命中目标时结束。
3. 如果目标值更小就走左子树，否则走右子树。
4. 返回最终节点指针。

- 最优时间复杂度：`O(h)`，最坏 `O(n)`。
- 最优空间复杂度：`O(1)`。

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != nullptr && root->val != val) {
            // 每一步只保留仍可能包含目标值的一侧。
            root = val < root->val ? root->left : root->right;
        }
        return root;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前递归节点 | 当前循环节点 | 语义相同 |
| 更新逻辑 | 递归进入单侧 | 循环移动指针 | 迭代可省栈空间 |
| 边界处理 | 空节点返回空 | 空节点返回空 | 正确 |
| 复杂度 | `O(h)` / `O(h)` | `O(h)` / `O(1)` | 可迁移迭代模板 |

## 下一步建议

进入下一题。当前题已经稳定，重点是把“只看一侧”的 BST 查询模式带到后续题。

## 后续练习

1. `98. Validate Binary Search Tree` - 从局部大小比较提升到全局范围约束。
2. `235. Lowest Common Ancestor of a Binary Search Tree` - 继续用大小关系决定搜索方向。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/700.search-in-a-binary-search-tree.cpp`
- 新函数名：`searchBSTOpt`
- 保留用户原实现：是
