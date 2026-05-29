# 题解点评 - 110. Balanced Binary Tree

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 3 天 - 高度、平衡与公共祖先
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/110.balanced-binary-tree.cpp`
- 资料来源：LeetCode 官方题目页、检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 定义递归函数 `dfs`，返回一组状态：当前子树高度，以及当前子树是否平衡。
2. 空节点返回 `{0, true}`，表示高度为 0 且平衡。
3. 先递归检查左子树；如果左子树已经不平衡，提前返回 false。
4. 再递归检查右子树；如果右子树不平衡，也提前返回 false。
5. 当前节点比较左右高度差，超过 1 返回不平衡，否则返回当前高度和 true。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`
- 复杂度来源：每个节点最多访问一次；递归栈深度为树高 `h`。

## 用户代码注释版

```cpp
using pii=pair<int, int>;
class Solution {
public:
    pii dfs(TreeNode *root) {
        // 空子树高度为 0，并且天然平衡。
        if(root == nullptr) return {0, true};
        auto [leftDepth, left] = dfs(root->left);
        // 左子树已经失败时，当前子树也必然失败，直接剪枝。
        if(left == false) return {0, false};
        auto [rightDepth, right] = dfs(root->right);
        if(right == false) return {0, false};
        // 当前节点也必须满足左右高度差不超过 1。
        if(abs(leftDepth-rightDepth) > 1) return {0, false};
        return {max(leftDepth, rightDepth)+1, true};
    }

    bool isBalanced(TreeNode* root) {
        return dfs(root).second;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 返回值定义 | 同时返回高度和是否合法 | 正确覆盖“每个节点都平衡”的要求 | 继续先写清递归返回给父节点的信息 |
| 剪枝 | 子树不平衡时提前返回 | 避免无意义计算，逻辑稳定 | 可以用 `-1` 哨兵进一步简化状态 |
| 类型表达 | `pair<int, int>` 第二项实际是 bool | 可运行，但语义不够直观 | 可改为 `pair<int, bool>` 或哨兵写法 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 一次递归同时得到高度和平衡性，复杂度最优 | `pii` 命名不够表达状态含义 | 高度类性质判断题 |
| 推荐最优解 | 用 `-1` 表示失败，返回值更轻 | 需要记住哨兵含义 | 面试中常见、简洁的平衡树写法 |

## 最优解法

1. 递归函数返回当前子树高度。
2. 如果某棵子树不平衡，直接返回 `-1` 作为失败哨兵。
3. 当前节点拿到左右高度后，如果高度差大于 1，也返回 `-1`。
4. 最终根节点返回值不是 `-1`，整棵树就平衡。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
    int heightOrFail(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = heightOrFail(root->left);
        if (leftHeight == -1) return -1;
        int rightHeight = heightOrFail(root->right);
        if (rightHeight == -1) return -1;

        // -1 表示当前子树已经不平衡，向父节点继续传播失败。
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return max(leftHeight, rightHeight) + 1;
    }

public:
    bool isBalanced(TreeNode* root) {
        return heightOrFail(root) != -1;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `{高度, 是否平衡}` | 高度或 `-1` 失败哨兵 | 二者都对，哨兵更短 |
| 更新逻辑 | 先检查左右，再合并高度 | 同样后序合并 | 已命中核心模式 |
| 边界处理 | 空树返回平衡 | 空树高度 0 | 正确 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已是最优 |

## 下一步建议

进入下一题。你已经抓住了“子树返回高度，当前节点判断性质”的关键。

## 后续练习

1. `543. Diameter of Binary Tree` - 继续练高度返回值和全局答案分工。
2. `124. Binary Tree Maximum Path Sum` - 后续拔高时迁移同一类“贡献值 + 全局答案”模型。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/110.balanced-binary-tree.cpp`
- 新函数名：`isBalancedOpt`
- 保留用户原实现：是
