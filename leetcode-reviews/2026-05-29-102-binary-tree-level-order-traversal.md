# 题解点评 - 102. Binary Tree Level Order Traversal

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 2 天 - 分层观察与视角结果
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/102.binary-tree-level-order-traversal.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki / Fandom 检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 空树直接返回空数组，避免后续队列中出现空指针。
2. 用队列保存下一批待处理节点，从根节点开始。
3. 每轮先记录 `q.size()` 作为当前层节点数，只弹出这一层的节点。
4. 把当前层节点值放入 `arr`，再把非空左右孩子加入队列，供下一层处理。
5. 当前层处理完成后，把 `arr` 放入答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(w)`，返回结果本身为 `O(n)`；其中 `w` 是树的最大宽度。
- 复杂度来源：每个节点入队、出队各一次；队列最多保存一层附近的节点。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // 空树没有任何层，直接返回空结果。
        if(root == nullptr) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            vector<int> arr;
            // 先冻结当前层大小，后面入队的孩子不会混入本层。
            int n=q.size();
            for(int i=0; i<n; i++) {
                auto p=q.front(); q.pop();
                arr.push_back(p->val);
                // 左右孩子只负责进入下一层。
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            ans.push_back(arr);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 层边界 | 先保存 `q.size()`，做得正确 | 保证每个 `arr` 只包含同一层节点 | 继续把“冻结当前层大小”当作层序遍历默认动作 |
| 空树处理 | 开头直接返回 `{}` | 覆盖 LeetCode 的空输入 | 保持这个习惯 |
| 代码清晰度 | 变量短但结构清楚 | 可读性足够，略缺语义 | 复盘时可把 `n` 口述为 `levelSize` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 标准层序遍历，正确、稳定、容易迁移 | `arr` 可提前 `reserve`，变量名还能更语义化 | 几乎所有按层收集结果的树题 |
| 推荐最优解 | 同样是 `O(n)`，用 `levelSize` 和 `reserve` 明确层边界 | 本质复杂度没有进一步下降 | 面试和提交都适合 |

## 最优解法

1. 如果根节点为空，直接返回空答案。
2. 队列从根节点开始，每轮取出当前队列大小作为本层节点数。
3. 本层只弹出固定数量节点，收集值，并把非空孩子加入队列。
4. 本层收集完后追加到答案。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(w)`，不含返回结果；`w` 为最大层宽。

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            vector<int> level;
            level.reserve(levelSize);

            // 固定处理当前层节点，孩子节点只进入下一轮。
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            ans.push_back(std::move(level));
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `q`、`arr`、`n` | `q`、`level`、`levelSize` | 变量名更贴近层序语义 |
| 更新逻辑 | 每层弹出 `n` 个节点 | 相同 | 已掌握核心模式 |
| 边界处理 | 覆盖空树 | 覆盖空树 | 无需重写 |
| 复杂度 | `O(n)` / `O(w)` | `O(n)` / `O(w)` | 已是最优复杂度 |

## 下一步建议

进入下一题。你已经把层序遍历骨架写稳了，后面重点练“同样的层边界下，结果收集规则如何变化”。

## 后续练习

1. `103. Binary Tree Zigzag Level Order Traversal` - 在同一层序骨架上改变每层输出方向。
2. `199. Binary Tree Right Side View` - 在同一层序骨架上只提取每层代表节点。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/102.binary-tree-level-order-traversal.cpp`
- 新函数名：`levelOrderOpt`
- 保留用户原实现：是
