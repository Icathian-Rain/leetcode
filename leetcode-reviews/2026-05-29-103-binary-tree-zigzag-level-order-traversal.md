# 题解点评 - 103. Binary Tree Zigzag Level Order Traversal

## 基本信息

- 日期：2026-05-29
- 主题：第 6 周第 2 天 - 分层观察与视角结果
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/103.binary-tree-zigzag-level-order-traversal.cpp`
- 资料来源：LeetCode 官方题目页、leetcode.ca 检索摘要
- 查询日期：2026-05-29

## 用户思路概述

1. 空树返回空数组。
2. 使用队列按层遍历，每轮用当前队列大小锁定本层节点范围。
3. 仍然按从左到右的自然顺序收集当前层节点值。
4. 根据当前答案已有层数判断这一层是否需要反转。
5. 将处理后的当前层结果加入答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(w)`，返回结果本身为 `O(n)`。
- 复杂度来源：每个节点只入队出队一次；每层反转的总元素数加起来仍是 `n`。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 空树没有层序结果。
        if(root == nullptr) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            vector<int> arr;
            // 固定当前层大小，避免孩子节点提前进入本层。
            int n=q.size();
            for(int i=0; i<n; i++) {
                auto p=q.front(); q.pop();
                arr.push_back(p->val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            // 第 0 层从左到右，第 1 层从右到左，依次交替。
            if(ans.size()%2==1)reverse(arr.begin(), arr.end());
            ans.push_back(arr);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 遍历顺序和输出顺序 | 保持左右入队，只反转输出 | 避免破坏下一层的天然结构 | 这是很稳的写法，优先保留 |
| 奇偶层判断 | 用 `ans.size() % 2` 判断方向 | 正确但语义略隐含 | 可以用 `bool leftToRight` 表达方向 |
| 复杂度意识 | 反转不会改变总 `O(n)` | 不会超时 | 若想减少一次反转，可按目标下标写入 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 简洁，复用 102 的层序骨架，正确性好解释 | 每个反向层需要一次 `reverse`，方向状态不够显性 | 适合快速提交和复盘 |
| 推荐最优解 | 直接按方向写入目标下标，省去反转步骤 | 下标计算要小心 | 适合训练“遍历顺序不等于输出顺序”的题 |

## 最优解法

1. 仍然按层使用队列遍历。
2. 用 `leftToRight` 标记当前层输出方向。
3. 当前层创建固定大小数组，弹出第 `i` 个节点时，根据方向决定写入 `i` 或 `levelSize - 1 - i`。
4. 孩子始终按左、右顺序入队，避免影响下一层的节点顺序。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(w)`，不含返回结果。

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            vector<int> level(levelSize);

            // 队列仍按自然层序推进，只把当前层写到不同下标。
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                int index = leftToRight ? i : levelSize - 1 - i;
                level[index] = node->val;

                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            ans.push_back(std::move(level));
            leftToRight = !leftToRight;
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 用 `ans.size()` 推导方向 | 用 `leftToRight` 显式表示方向 | 让控制逻辑更可读 |
| 更新逻辑 | 先顺序收集，再反转 | 直接写入目标下标 | 省掉后处理，训练下标控制 |
| 边界处理 | 覆盖空树、单节点 | 覆盖空树、单节点 | 当前已稳定 |
| 复杂度 | `O(n)` / `O(w)` | `O(n)` / `O(w)` | 两者同阶，推荐写法更精炼 |

## 下一步建议

做跟练题。当前写法已经能通过，建议复盘时重点说清：队列的推进顺序不用变，变的是每层结果的写入顺序。

## 后续练习

1. `199. Binary Tree Right Side View` - 继续练从每层中抽取特定位置。
2. `515. Find Largest Value in Each Tree Row` - 练习每层聚合一个统计值。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/103.binary-tree-zigzag-level-order-traversal.cpp`
- 新函数名：`zigzagLevelOrderOpt`
- 保留用户原实现：是
