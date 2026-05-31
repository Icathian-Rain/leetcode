# 题解点评 - 701. Insert into a Binary Search Tree

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树查询与修改
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/701.insert-into-a-binary-search-tree.cpp`
- 资料来源：LeetCode Wiki / leetcode.ca 检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. 如果当前子树为空，说明已经找到插入位置，创建新节点并返回。
2. 如果当前节点值大于待插入值，把新值插入左子树。
3. 否则把新值插入右子树。
4. 每层递归都把修改后的子树根重新接回当前节点。
5. 返回原根节点，保持整棵树结构可达。

## 用户解法复杂度

- 时间复杂度：`O(h)`，最坏退化为 `O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：每次根据大小关系只进入一侧子树；递归栈深度为树高 `h`。

## 用户代码注释版

```cpp
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // 空位置就是新节点应该接入的位置。
        if(root == nullptr) return new TreeNode(val);
        if(root->val > val) root->left = insertIntoBST(root->left, val);
        else root->right = insertIntoBST(root->right, val);
        // 返回当前子树根，保证父节点能接住修改后的子树。
        return root;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 插入位置 | 找到空子树时创建节点 | 正确命中 BST 插入本质 | 保持 |
| 子树回接 | 递归结果重新赋给左右孩子 | 能处理插入发生在深层的情况 | 这是树修改题的关键 |
| 实现形式 | 使用递归 | 正确但占用递归栈 | 可补迭代版，空间 `O(1)` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 简洁，直接表达“在空位插入” | 递归栈空间 `O(h)` | 适合提交和理解 |
| 推荐最优解 | 迭代沿搜索路径找到空孩子，空间 `O(1)` | 需要维护当前节点指针 | 高频 BST 修改模板 |

## 最优解法

1. 如果根为空，直接返回新节点。
2. 从根开始沿 BST 搜索路径移动。
3. 如果 `val` 更小，尝试进入左孩子；左孩子为空就接入。
4. 如果 `val` 更大，尝试进入右孩子；右孩子为空就接入。
5. 返回原根节点。

- 最优时间复杂度：`O(h)`，最坏 `O(n)`。
- 最优空间复杂度：`O(1)`。

### 最优解代码

```cpp
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        TreeNode* cur = root;
        while (true) {
            if (val < cur->val) {
                if (cur->left == nullptr) {
                    cur->left = new TreeNode(val);
                    break;
                }
                cur = cur->left;
            } else {
                if (cur->right == nullptr) {
                    cur->right = new TreeNode(val);
                    break;
                }
                cur = cur->right;
            }
        }
        return root;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前递归子树根 | 当前搜索节点 | 语义一致 |
| 更新逻辑 | 递归回接左右子树 | 找到空孩子后直接连接 | 迭代省栈 |
| 边界处理 | 空树直接新建根 | 相同 | 正确 |
| 复杂度 | `O(h)` / `O(h)` | `O(h)` / `O(1)` | 可迁移迭代模板 |

## 下一步建议

进入下一题。插入题已经稳定，接下来重点练删除时如何恢复 BST 结构。

## 后续练习

1. `450. Delete Node in a BST` - 练习删除后重新连接子树。
2. `669. Trim a Binary Search Tree` - 继续练保留合法范围内的子树结构。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/701.insert-into-a-binary-search-tree.cpp`
- 新函数名：`insertIntoBSTOpt`
- 保留用户原实现：是
