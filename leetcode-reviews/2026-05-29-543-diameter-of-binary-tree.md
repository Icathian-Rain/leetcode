# 题解点评 - 543. Diameter of Binary Tree

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 3 天 - 高度、平衡与公共祖先
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/543.diameter-of-binary-tree.cpp`
- 资料来源：LeetCode 官方题目页、检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 用成员变量 `ans` 记录全局最大直径。
2. 递归函数 `dfs` 返回当前节点向父节点能贡献的最大深度。
3. 空节点深度为 0。
4. 对每个节点，先得到左右子树深度。
5. 经过当前节点的候选直径为 `left + right`，用它更新全局答案。
6. 返回 `max(left, right) + 1` 给父节点。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`
- 复杂度来源：每个节点只计算一次深度；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
    int ans=0;
    int dfs(TreeNode* root) {
        // 空节点不能向父节点贡献高度。
        if(root == nullptr) return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        // 经过当前节点的路径边数，是左深度加右深度。
        ans = max(ans, left+right);
        // 返回给父节点的只能是一边的最大深度，不能把两边都带上去。
        return max(left, right)+1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 返回值和答案分离 | `dfs` 返回高度，`ans` 记录直径 | 抓住了本题最核心分工 | 后续路径题继续沿用这个思路 |
| 边数定义 | 用 `left + right` 更新答案 | 正确，避免节点数/边数混淆 | 复盘时说明深度以节点数表示，直径以边数表示 |
| 成员变量 | `ans` 作为成员状态 | LeetCode 单次调用没问题 | 可用局部变量引用，降低多次调用残留风险 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 简洁准确，复杂度最优 | 成员变量在复用对象多次调用时需重置 | 树上最长路径类问题 |
| 推荐最优解 | 用局部 `diameter` 引用传递，函数更纯 | 多一个参数 | 更适合长期复用和模板化 |

## 最优解法

1. 后序遍历整棵树。
2. 递归返回当前节点向父节点贡献的最大深度。
3. 当前节点用左右深度之和更新全局直径。
4. 返回时只能选择左右一边继续向上延伸。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
    int depth(TreeNode* root, int& diameter) {
        if (root == nullptr) {
            return 0;
        }

        int leftDepth = depth(root->left, diameter);
        int rightDepth = depth(root->right, diameter);
        // 当前节点作为拐点时，左右深度之和就是候选直径。
        diameter = max(diameter, leftDepth + rightDepth);
        return max(leftDepth, rightDepth) + 1;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        depth(root, diameter);
        return diameter;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员变量 `ans` | 局部变量 `diameter` | 减少对象状态残留 |
| 更新逻辑 | 左右深度更新全局答案 | 相同 | 已掌握 |
| 边界处理 | 空节点返回 0 | 空节点返回 0 | 正确 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已是最优 |

## 下一步建议

做跟练题。重点保留这句口头模板：返回给父节点的是单边贡献，全局答案可以在当前节点合并两边。

## 后续练习

1. `124. Binary Tree Maximum Path Sum` - 同样区分单边贡献和全局最优。
2. `687. Longest Univalue Path` - 继续练经过当前节点的路径合并。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/543.diameter-of-binary-tree.cpp`
- 新函数名：`diameterOfBinaryTreeOpt`
- 保留用户原实现：是
