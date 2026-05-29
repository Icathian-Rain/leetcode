# 题解点评 - 236. Lowest Common Ancestor of a Binary Tree

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 3 天 - 高度、平衡与公共祖先
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/236.lowest-common-ancestor-of-a-binary-tree.cpp`
- 资料来源：LeetCode 官方题目页、leetcode.ca 检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 空节点返回 `nullptr`。
2. 当前节点等于 `p` 或 `q` 时，直接返回当前节点。
3. 递归搜索左子树，如果左子树已经返回一个既不是 `p` 也不是 `q` 的节点，就认为已经找到 LCA 并提前返回。
4. 再递归搜索右子树，同样处理已找到 LCA 的情况。
5. 如果只有一侧命中，就把那一侧结果向上返回；如果左右都命中，则当前节点是最近公共祖先。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`
- 复杂度来源：每个节点最多被递归访问一次；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        // 当前节点命中目标时，向父节点报告“这里找到了一个目标”。
        if(root == p || root == q) return root;
        auto l = lowestCommonAncestor(root->left, p, q);
        // 如果左子树已经返回真正的 LCA，可以提前向上传播。
        if(l!=nullptr && l!=p && l!=q) return l;
        auto r = lowestCommonAncestor(root->right, p, q);
        if(r!=nullptr && r!=p && r!=q) return r;
        // 只有一侧命中时向上传播命中节点；两侧都命中时当前节点是交汇点。
        if(l == nullptr) return r;
        else if(r == nullptr) return l;
        return root;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 返回值语义 | 返回目标节点、LCA 或空 | 正确但分支稍复杂 | 可统一成“子树里找到的有效结果” |
| 当前节点是祖先 | `root == p/q` 直接返回 | 覆盖 p 是 q 祖先的情况 | 很关键，保持 |
| 早返回判断 | 通过 `l != p && l != q` 识别 LCA | 正确但依赖题设节点存在且唯一 | 标准写法可不区分返回的是目标还是 LCA |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确处理目标节点本身是祖先的场景，也有提前返回 | 分支多，判断含义不够直观 | 可通过，但复盘成本稍高 |
| 推荐最优解 | 三段式：命中当前、搜左右、合并左右 | 不能提前剪掉另一侧，但仍是 `O(n)` | 面试最常见，最容易讲清 |

## 最优解法

1. 如果当前节点为空、等于 `p` 或等于 `q`，直接返回当前节点。
2. 分别在左右子树中查找。
3. 如果左右都返回非空，说明两个目标分布在当前节点两侧，当前节点就是 LCA。
4. 如果只有一侧非空，向父节点返回那一侧结果。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 左右各命中一个目标时，当前节点就是最低交汇点。
        if (left != nullptr && right != nullptr) {
            return root;
        }
        return left != nullptr ? left : right;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 区分目标节点和已找到 LCA | 统一返回子树有效结果 | 简化分支判断 |
| 更新逻辑 | 左侧可能提前返回，再搜右侧 | 左右都搜完后统一合并 | 标准模板更好背诵和迁移 |
| 边界处理 | 空节点、命中 p/q 都覆盖 | 相同 | 正确 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已是最优 |

## 下一步建议

进入下一题。你已经能写出正确的 LCA 递归，下一步建议把标准四分支模板背成肌肉记忆：空/命中、搜左、搜右、合并。

## 后续练习

1. `235. Lowest Common Ancestor of a Binary Search Tree` - 对比普通树和 BST 中定位祖先的不同依据。
2. `572. Subtree of Another Tree` - 继续练“子树返回结果如何向父节点传播”。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/236.lowest-common-ancestor-of-a-binary-tree.cpp`
- 新函数名：`lowestCommonAncestorOpt`
- 保留用户原实现：是
