# 题解点评 - 450. Delete Node in a BST

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树查询与修改
- 难度：中等
- 本次结果：待提交验证，源码逻辑正确但复杂度可优化
- 对应源码：`src/450.delete-node-in-a-bst.cpp`
- 资料来源：leetcode.ca、LeetCode 题目资料检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. 空节点直接返回空，表示没有要删除的目标。
2. 找到目标节点后，按三种情况处理：无孩子、只有一个孩子、左右孩子都存在。
3. 无孩子时删除当前节点并返回空。
4. 只有一个孩子时，用唯一孩子替代当前节点。
5. 左右孩子都存在时，找到右子树最左节点，把左子树接到它的左侧，然后用右子树替代当前节点。
6. 如果当前节点不是目标，递归处理左右子树后返回当前根。

## 用户解法复杂度

- 时间复杂度：当前实现最坏为 `O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：未命中当前节点时同时递归左右子树，没有利用 BST 大小关系只走一侧；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return root;
        if(root->val == key) {
            if(root->left == nullptr && root->right == nullptr) {
                // 叶子节点删除后，父节点应接回 nullptr。
                delete root;
                return nullptr;
            } else if(root->left == nullptr || root->right == nullptr) {
                // 单孩子节点可直接用唯一孩子替代。
                auto newroot = root->left != nullptr ? root->left : root->right;
                delete root;
                return newroot;
            } else {
                // 双孩子节点：用右子树作为新根，并把左子树接到右子树最小节点左侧。
                auto cur = root->right;
                while(cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = root->left;
                auto newroot = root->right;
                delete root;
                return newroot;
            }
        }

        // 这里没有利用 BST 性质，实际只需要根据 key 大小递归一侧。
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 删除三分类 | 叶子、单孩子、双孩子都覆盖 | 正确性基础很好 | 保持这种分情况意识 |
| 双孩子重接 | 把左子树接到右子树最小节点下 | 能保持中序顺序 | 这是可接受的删除策略 |
| 搜索方向 | 未命中时递归左右两侧 | 正确但退化成整树搜索 | 根据 `key` 和 `root->val` 只递归一侧 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 删除节点后的结构恢复思路正确 | 没用 BST 搜索方向，最坏 `O(n)` | 小树可过，但不是最佳 BST 写法 |
| 推荐最优解 | 搜索阶段只走一侧，删除阶段局部重接 | 双孩子情况需要小心保持中序顺序 | 标准 BST 删除模板 |

## 最优解法

1. 如果当前节点为空，返回空。
2. 如果 `key` 小于当前值，只在左子树删除，并把结果接回左孩子。
3. 如果 `key` 大于当前值，只在右子树删除，并把结果接回右孩子。
4. 找到目标节点后，如果缺少左子树，返回右子树；如果缺少右子树，返回左子树。
5. 如果左右子树都有，找到右子树最小节点，把左子树接到它的左侧，再返回右子树作为新根。

- 最优时间复杂度：`O(h)`，最坏 `O(n)`。
- 最优空间复杂度：`O(h)`。

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
            return root;
        }
        if (key > root->val) {
            root->right = deleteNode(root->right, key);
            return root;
        }

        if (root->left == nullptr) {
            return root->right;
        }
        if (root->right == nullptr) {
            return root->left;
        }

        TreeNode* successor = root->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        // 右子树最小节点大于左子树所有节点，适合接住左子树。
        successor->left = root->left;
        return root->right;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前递归子树根 | 当前递归子树根 | 相同 |
| 更新逻辑 | 未命中时左右都递归 | 按大小只递归一侧 | 这是主要优化点 |
| 边界处理 | 三类删除情况完整 | 三类删除情况完整 | 正确 |
| 复杂度 | `O(n)` / `O(h)` | `O(h)` / `O(h)` | 利用 BST 搜索路径 |

## 下一步建议

重写当前题的搜索部分。删除节点的结构处理已经掌握，重点把“没找到目标时只走一侧”练成条件反射。

## 后续练习

1. `669. Trim a Binary Search Tree` - 继续练 BST 范围剪枝和子树回接。
2. `108. Convert Sorted Array to Binary Search Tree` - 从有序结构反向构造 BST。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/450.delete-node-in-a-bst.cpp`
- 新函数名：`deleteNodeOpt`
- 保留用户原实现：是
