# 题解点评 - 235. Lowest Common Ancestor of a Binary Search Tree

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树查询与修改
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/235.lowest-common-ancestor-of-a-binary-search-tree.cpp`
- 资料来源：LeetCode 官方题目页、leetcode.ca 检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. 空节点返回 `nullptr`。
2. 如果当前节点值同时大于 `p` 和 `q`，说明两个目标都在左子树。
3. 如果当前节点值同时小于 `p` 和 `q`，说明两个目标都在右子树。
4. 否则当前节点位于两个目标之间，或等于其中一个目标，就是最近公共祖先。

## 用户解法复杂度

- 时间复杂度：`O(h)`，最坏退化为 `O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：每次只沿 BST 的一侧继续递归，递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        if(root->val > p->val && root->val > q->val) {
            // 两个目标都比当前节点小，LCA 只可能在左侧。
            return lowestCommonAncestor(root->left, p, q);
        } else if(root->val < p->val && root->val < q->val) {
            // 两个目标都比当前节点大，LCA 只可能在右侧。
            return lowestCommonAncestor(root->right, p, q);
        } else {
            // 分叉或命中其中一个目标，当前节点就是最近公共祖先。
            return root;
        }
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| BST 分叉点 | 正确把 LCA 转化成搜索路径分叉点 | 思路非常稳 | 这是 236 普通树 LCA 的 BST 简化版 |
| 目标节点可作为祖先 | `else return root` 覆盖等于 p/q | 正确 | 保持 |
| 实现形式 | 递归 | 简洁正确 | 可补迭代版省栈 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 判断完整，能直接通过 | 使用递归栈 | BST LCA 标准解 |
| 推荐最优解 | 迭代搜索分叉点，空间 `O(1)` | 代码形态稍长 | 查询路径类 BST 题 |

## 最优解法

1. 从根节点开始。
2. 如果 `p` 和 `q` 都小于当前节点，向左走。
3. 如果 `p` 和 `q` 都大于当前节点，向右走。
4. 否则当前节点就是两个搜索路径的第一个分叉点。

- 最优时间复杂度：`O(h)`，最坏 `O(n)`。
- 最优空间复杂度：`O(1)`。

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else {
                // 当前节点是分叉点，或本身就是其中一个目标。
                return root;
            }
        }
        return nullptr;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前递归节点 | 当前循环节点 | 语义相同 |
| 更新逻辑 | 递归走左/右 | 循环走左/右 | 迭代省空间 |
| 边界处理 | 空节点和命中目标覆盖 | 相同 | 正确 |
| 复杂度 | `O(h)` / `O(h)` | `O(h)` / `O(1)` | 可迁移迭代写法 |

## 下一步建议

进入下一题。你已经把普通树 LCA 和 BST LCA 的差异分清楚了。

## 后续练习

1. `701. Insert into a Binary Search Tree` - 继续沿 BST 搜索路径找到接入位置。
2. `450. Delete Node in a BST` - 练习修改后仍维持有序结构。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/235.lowest-common-ancestor-of-a-binary-search-tree.cpp`
- 新函数名：`lowestCommonAncestorOpt`
- 保留用户原实现：是
