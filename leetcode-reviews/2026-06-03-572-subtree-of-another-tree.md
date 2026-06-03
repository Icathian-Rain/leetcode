# 题解点评 - 572. Subtree of Another Tree

## 基本信息

- 日期：2026-06-03
- 主题：树与二叉搜索树，第 7 天综合复盘与结构迁移
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/572.subtree-of-another-tree.cpp`
- 资料来源：本地周计划与源码，未联网校准
- 查询日期：未联网

## 用户思路概述

1. 先写 `isSame`，同步比较两棵树是否结构和值完全一致。
2. 在 `isSubtree` 中，对 `root` 的每个节点尝试与 `subRoot` 做一次完整双树比较。
3. 如果当前节点不匹配，就递归去左右子树继续寻找可能的起点。

## 用户解法复杂度

- 时间复杂度：最坏 `O(n * m)`
- 空间复杂度：`O(h1 + h2)`
- 复杂度来源：`root` 的多个节点都可能触发一次对子树规模为 `m` 的完整比较；递归栈来自主树搜索和双树比较。

## 用户代码注释版

```cpp
class Solution {
public:
    bool isSame(TreeNode* root, TreeNode* subRoot) {
        // 两边都空，说明当前结构完全匹配。
        if(root == nullptr && subRoot == nullptr) return true;
        // 只有一边为空，结构不同。
        if(root == nullptr || subRoot == nullptr) return false;
        // 值不同，当前起点不可能匹配。
        if(root->val != subRoot->val) return false;
        return isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // 先尝试把当前 root 当作子树起点。
        if(isSame(root, subRoot) == true) return true;
        if(root == nullptr && subRoot != nullptr) return false;
        // 继续在左右子树中寻找起点；这里用 || 更符合短路语义。
        return isSubtree(root->left, subRoot) | isSubtree(root->right, subRoot);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 双树比较 | `isSame` 覆盖双空、单空和值不同 | 正确性稳定 | 保持这个基础模板 |
| 搜索起点 | 对主树每个节点尝试匹配 | 思路直观，容易写对 | 面对大数据时要意识到重复比较成本 |
| 短路逻辑 | 使用 `|` 而不是 `||` | 正确性通常不受影响，但会多做递归 | 布尔递归优先使用 `||` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 结构清晰，和第 1 天 `Same Tree` 能直接迁移 | 最坏会重复比较大量节点 | 普通输入和面试手写都可接受 |
| 推荐最优解 | 序列化后用 KMP 匹配，整体线性 | 代码更长，需要记录空节点避免结构歧义 | 需要强调最坏复杂度时更合适 |

## 最优解法

1. 用先序遍历序列化两棵树，并显式记录空节点。
2. 把 `subRoot` 的序列当作模式串，主树序列当作文本串。
3. 用 KMP 判断模式串是否出现在文本串中。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(n + m)`

### 最优解代码

```cpp
class Solution {
    void serialize(TreeNode* root, vector<int>& values) {
        if (root == nullptr) {
            values.push_back(INT_MIN);
            return;
        }
        values.push_back(root->val);
        serialize(root->left, values);
        serialize(root->right, values);
    }

    bool contains(const vector<int>& source, const vector<int>& pattern) {
        vector<int> lps(pattern.size());
        for (int i = 1, len = 0; i < pattern.size();) {
            if (pattern[i] == pattern[len]) lps[i++] = ++len;
            else if (len > 0) len = lps[len - 1];
            else ++i;
        }
        for (int i = 0, j = 0; i < source.size(); ++i) {
            while (j > 0 && source[i] != pattern[j]) j = lps[j - 1];
            if (source[i] == pattern[j]) ++j;
            if (j == pattern.size()) return true;
        }
        return false;
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        vector<int> source, pattern;
        serialize(root, source);
        serialize(subRoot, pattern);
        return contains(source, pattern);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 当前起点与两棵树同步比较 | 两棵树的结构序列 | 看到“整棵结构匹配”时可以想到序列化 |
| 更新逻辑 | 每个节点重新比较 | 预处理模式串后线性扫描 | 减少重复比较 |
| 边界处理 | 空节点在比较中处理 | 空节点写入序列 | 保证结构不同不会误判 |
| 复杂度 | `O(n*m)` | `O(n+m)` | 大规模输入时优先线性匹配 |

## 下一步建议

当前朴素解法已经能作为稳定提交版本。建议补一个结构相似但空孩子不同的反例，再复盘为什么序列化必须记录空节点。

## 后续练习

1. `100. Same Tree` - 巩固双树同步比较。
2. `297. Serialize and Deserialize Binary Tree` - 强化树结构序列化意识。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/572.subtree-of-another-tree.cpp`
- 新函数名：`isSubtreeOpt`
- 保留用户原实现：是
