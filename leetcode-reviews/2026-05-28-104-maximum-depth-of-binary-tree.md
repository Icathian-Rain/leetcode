# 题解点评 - 104. Maximum Depth of Binary Tree

## 基本信息

- 日期：2026-05-28
- 主题：第 6 周树与二叉搜索树 - 第 1 天基础递归与双树比较
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/104.maximum-depth-of-binary-tree.cpp`
- 资料来源：LeetCode Wiki、leetcode.ca
- 查询日期：2026-05-28

## 用户思路概述

1. 空节点深度定义为 `0`。
2. 分别递归求左子树和右子树最大深度。
3. 当前节点深度等于左右子树较大值加 `1`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`
- 复杂度来源：每个节点访问一次，递归调用栈高度取决于树高。

## 用户代码注释版

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0; // 空子树深度为 0。
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return max(leftDepth, rightDepth)+1; // 当前节点贡献一层。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 返回值定义 | 返回当前子树最大深度 | 正确且可迁移 | 做每道树题前都先定义返回值 |
| 空节点含义 | 空节点返回 `0` | 覆盖空树与叶子节点 | 很稳，继续保持 |
| 合并左右结果 | 使用 `max + 1` | 命中高度题核心 | 后续 `543/110` 会继续用到这个模式 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 简洁，返回值语义清楚 | 极端树高时递归栈较深 | 适合直接提交 |
| 推荐最优解 | 与用户解法等价，注释强调当前节点贡献 | 无复杂度差异 | 适合作为树高度模板 |

## 最优解法

1. 空节点返回 `0`。
2. 分别得到左右子树深度。
3. 当前节点返回 `max(left, right) + 1`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return max(leftDepth, rightDepth) + 1; // 当前节点贡献 1 层。
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 子树最大深度 | 相同 | 已掌握 |
| 更新逻辑 | 左右结果取最大 | 相同 | 可迁移到高度、平衡和直径题 |
| 边界处理 | 空节点为 0 | 相同 | 已覆盖 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已最优 |

## 下一步建议

进入 `100. Same Tree`，重点从单树递归切到双树同步比较。

## 后续练习

1. `110. Balanced Binary Tree` - 继续使用高度返回值。
2. `543. Diameter of Binary Tree` - 练习把高度贡献和全局答案分开。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/104.maximum-depth-of-binary-tree.cpp`
- 新函数名：`maxDepthOpt`
- 保留用户原实现：是
