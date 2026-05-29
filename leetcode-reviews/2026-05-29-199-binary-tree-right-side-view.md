# 题解点评 - 199. Binary Tree Right Side View

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 2 天 - 分层观察与视角结果
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/199.binary-tree-right-side-view.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki 检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 空树直接返回空数组。
2. 使用队列做层序遍历，每轮记录当前层节点数量。
3. 遍历当前层时，如果当前下标是 `n - 1`，说明这是这一层最后被弹出的节点。
4. 因为孩子按左、右顺序入队，每层最后一个节点就是从右侧能看到的节点。
5. 把每层最后一个节点值加入答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(w)`，其中 `w` 是树的最大宽度。
- 复杂度来源：每个节点入队、出队一次；队列最多保存相邻层节点。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        // 空树右视图为空。
        if(root == nullptr) return {};
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            // 固定当前层节点数，i == n - 1 表示当前层最后一个节点。
            int n=q.size();
            for(int i=0; i<n; i++) {
                auto p=q.front(); q.pop();
                if(i == n-1) ans.push_back(p->val);
                // 左右孩子自然入队，因此下一层仍保持从左到右的顺序。
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 右视图含义 | 正确转化为“每层最右节点” | 题意建模准确 | 后续左视图、每层最大值都可迁移 |
| 层边界 | 用 `q.size()` 固定当前层 | 正确性稳定 | 继续保持 |
| 可替代写法 | 当前只用了 BFS | 已足够最优 | 可补一个右优先 DFS，训练树深度视角 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 标准、直观，和 102/103 共享骨架 | 队列空间取决于最大宽度 | 分层观察、每层取代表值 |
| 推荐最优解 | 右优先 DFS，第一次到达某深度就是答案 | 需要清楚递归深度和答案长度的关系 | 适合迁移到视图类、深度优先类树题 |

## 最优解法

1. 用右优先 DFS 遍历树，并携带当前深度。
2. 如果 `depth == ans.size()`，说明这是第一次到达该深度。
3. 因为递归先访问右子树，第一次到达某层的节点就是该层右视图节点。
4. 然后继续访问左子树，只补充右侧不存在时才能看到的更深节点。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`，其中 `h` 是树高；不含返回结果。

### 最优解代码

```cpp
class Solution {
private:
    void dfs(TreeNode* node, int depth, vector<int>& ans) {
        if (node == nullptr) {
            return;
        }

        // 右优先遍历下，第一次到达某一层的节点就是右视图节点。
        if (depth == static_cast<int>(ans.size())) {
            ans.push_back(node->val);
        }
        dfs(node->right, depth + 1, ans);
        dfs(node->left, depth + 1, ans);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        dfs(root, 0, ans);
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 队列表示当前层和下一层 | 深度表示当前节点所在层 | 两种视角都要能口述 |
| 更新逻辑 | 每层最后一个节点入答案 | 每层第一次访问的节点入答案 | 把“视角”转成访问顺序 |
| 边界处理 | 空树返回 `{}` | 空节点递归返回 | 都正确 |
| 复杂度 | `O(n)` / `O(w)` | `O(n)` / `O(h)` | BFS 更直观，DFS 更适合视图类迁移 |

## 下一步建议

进入下一题。当前第 2 天的层序骨架已经很稳，下一步可以切到第 3 天的高度和平衡判断，重点从“按层观察”转成“子树向父节点返回什么信息”。

## 后续练习

1. `110. Balanced Binary Tree` - 练习用子树高度支撑整棵树性质判断。
2. `543. Diameter of Binary Tree` - 练习区分返回给父节点的信息和全局答案。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/199.binary-tree-right-side-view.cpp`
- 新函数名：`rightSideViewOpt`
- 保留用户原实现：是
