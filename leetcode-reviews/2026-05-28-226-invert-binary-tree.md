# 题解点评 - 226. Invert Binary Tree

## 基本信息

- 日期：2026-05-28
- 主题：第 6 周树与二叉搜索树 - 第 1 天基础递归与双树比较
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/226.invert-binary-tree.cpp`
- 资料来源：LeetCode 官方题目页、leetcode.ca
- 查询日期：2026-05-28

## 用户思路概述

1. 空节点直接返回 `nullptr`，作为递归终止条件。
2. 递归翻转左子树和右子树，分别保存返回后的根节点。
3. 在当前节点交换左右子树指针，并返回当前节点。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`，其中 `h` 是树高
- 复杂度来源：每个节点访问一次，递归调用栈取决于树高。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr; // 空树翻转后仍为空。
        auto left = invertTree(root->left); // 先翻转原左子树。
        auto right = invertTree(root->right); // 再翻转原右子树。
        root->right = left;
        root->left = right;
        return root; // 返回当前子树新的根。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 递归返回值 | 明确返回翻转后的当前子树根 | 正确性稳定 | 继续保持先定义返回值的习惯 |
| 空节点处理 | 开头直接处理 `nullptr` | 覆盖空树和叶子子节点 | 树题优先写空节点分支 |
| 指针交换 | 先保存左右递归结果再交换 | 避免覆盖原子树指针 | 这比先 `swap` 再递归更容易手推 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 简洁、正确，递归语义清楚 | 极端链状树时递归栈较深 | 适合本题直接提交 |
| 推荐最优解 | 与用户解法等价，仅命名和注释更明确 | 无明显更优复杂度 | 适合作为基础树递归模板 |

## 最优解法

1. 空节点返回空。
2. 递归获得左右子树翻转后的结果。
3. 交换当前节点左右指针，返回当前节点。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;  // 左右子树已经各自翻转，再交换到当前节点两侧。
        root->right = left;
        return root;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前函数返回翻转后的子树根 | 相同 | 已掌握 |
| 更新逻辑 | 后序处理后交换 | 相同 | 可继续练前序交换版本做对照 |
| 边界处理 | 空节点直接返回 | 相同 | 已覆盖 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已最优 |

## 下一步建议

进入 `104. Maximum Depth of Binary Tree`，重点从“修改子树”切换到“合并左右子树返回值”。

## 后续练习

1. `104. Maximum Depth of Binary Tree` - 练习左右子树结果合并。
2. `101. Symmetric Tree` - 练习镜像关系下的双侧比较。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/226.invert-binary-tree.cpp`
- 新函数名：`invertTreeOpt`
- 保留用户原实现：是
