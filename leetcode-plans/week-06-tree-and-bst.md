# 第 06 周 - 树与二叉搜索树

## 本周目标

把注意力从线性区间切到树形结构：每次面对一棵树，都先说清楚当前函数要处理“当前节点本身”“左右子树结果”还是“从父节点传下来的限制”。到本周结束时，你应该能稳定写出基础递归、分层遍历、二叉搜索树判断与查询，以及路径类题目中的返回值和全局答案分工。

当前进度：已完成第 1 天基础递归与双树比较。第 5 周二分仍有第 4 天总结待补；如果当天时间紧，可以先补第 5 周闭环，再继续第 2 天分层观察题。

资料校准：题号、英文题名和难度参考 LeetCode 官方题目页、LeetCode 中文题目页、LeetCode Wiki 与 leetcode.ca 资料；生成日期为 2026-05-27。

## 与第 5 周衔接

第 5 周二分训练的是“区间里答案是否还存在”。第 6 周树题要把这个意识迁移成“子树返回什么信息”。二分里端点含义不清会漏答案；树题里递归返回值含义不清，会把局部答案、父节点需要的信息和全局答案混在一起。

## 前置知识

- 能读懂 LeetCode 的 `TreeNode` 结构
- 能区分空节点、叶子节点、单边子树和完整左右子树
- 能手推一棵 3-5 个节点的小树
- 能解释递归函数的输入、返回值和终止条件
- 能使用队列按层处理节点
- 能说清二叉搜索树中节点值与左右子树值的关系

## 每日计划

### 第 1 天 - 基础递归与双树比较

1. `226. Invert Binary Tree` (`简单`) - 练习对每个节点做相同的局部操作，并确认空节点如何返回。
2. `104. Maximum Depth of Binary Tree` (`简单`) - 练习把左右子树结果合并成当前节点答案。
3. `100. Same Tree` (`简单`) - 练习同步观察两棵树，并处理结构不同和值不同的情况。

### 第 2 天 - 分层观察与视角结果

1. `102. Binary Tree Level Order Traversal` (`中等`) - 练习按层收集节点，并保持每层结果边界清楚。
2. `103. Binary Tree Zigzag Level Order Traversal` (`中等`) - 练习在分层结果上加入方向变化。
3. `199. Binary Tree Right Side View` (`中等`) - 练习从每一层提取一个代表性结果。

### 第 3 天 - 高度、平衡与公共祖先

1. `110. Balanced Binary Tree` (`简单`) - 练习在判断性质时同时关心子树规模差异。
2. `543. Diameter of Binary Tree` (`简单`) - 练习区分当前节点能贡献的信息和全局最优答案。
3. `236. Lowest Common Ancestor of a Binary Tree` (`中等`) - 练习在普通二叉树中根据左右子树结果定位交汇节点。

### 第 4 天 - 二叉搜索树基础判断

1. `700. Search in a Binary Search Tree` (`简单`) - 练习根据节点值关系选择下一步方向。
2. `98. Validate Binary Search Tree` (`中等`) - 练习判断整棵树是否满足全局有序限制。
3. `230. Kth Smallest Element in a BST` (`中等`) - 练习按二叉搜索树的有序结构定位第 k 个结果。

### 第 5 天 - 二叉搜索树查询与修改

1. `235. Lowest Common Ancestor of a Binary Search Tree` (`简单`) - 练习利用二叉搜索树性质定位分叉位置。
2. `701. Insert into a Binary Search Tree` (`中等`) - 练习在保持结构性质的前提下接入新节点。
3. `450. Delete Node in a BST` (`中等`) - 练习在删除节点后恢复树的合法结构。

### 第 6 天 - 路径、贡献值与困难边界

1. `112. Path Sum` (`简单`) - 练习沿路径累积状态，并判断根到叶子的条件。
2. `113. Path Sum II` (`中等`) - 练习收集多条合法路径，并在返回上一层前恢复当前选择。
3. `124. Binary Tree Maximum Path Sum` (`困难`) - 练习把“向父节点贡献的值”和“整棵树中的最优值”分开。

### 第 7 天 - 综合复盘与结构迁移

1. `572. Subtree of Another Tree` (`简单`) - 练习把双树比较嵌入到整棵树搜索中。
2. `105. Construct Binary Tree from Preorder and Inorder Traversal` (`中等`) - 练习根据两种观察顺序还原树结构。
3. `437. Path Sum III` (`中等`) - 练习把路径统计和从祖先到当前节点的状态结合起来。

## 本周关注清单

- 每题动手前先写一句：当前函数返回给父节点的是什么。
- 遇到路径题，先区分“当前路径状态”和“全局答案”。
- 遇到 BST 题，先确认限制是只作用于父子节点，还是作用于整棵左右子树。
- 空节点不是例外情况，而是递归的基本输入；先写空节点返回值。
- 对每道题至少手推一棵只有左子树或只有右子树的小树。
- 能递归写出的题，至少选 2-3 题再口头说明迭代或分层版本的状态组织。

## 本周节奏建议

- 第 1 天：先把递归函数的返回值说清楚，暂时不要追求花哨写法。
- 第 2 天：切换到按层处理，重点观察一层的开始和结束在哪里。
- 第 3 天：进入“局部信息”和“全局答案”的分离，这是树题最常见的卡点。
- 第 4-5 天：集中训练 BST，重点是全局约束、查询方向和修改后的结构恢复。
- 第 6 天：处理路径题和困难题，不求快，先画出一条经过当前节点的路径能怎么延伸。
- 第 7 天：做综合迁移，把比较、构造和路径统计三类能力串起来复盘。

## 进度更新 - 2026-05-28

- 今日完成：`226. Invert Binary Tree`、`104. Maximum Depth of Binary Tree`、`100. Same Tree`
- 当前主题：第 1 天 - 基础递归与双树比较

### 通用解题模板

- 适用条件：题目要求处理整棵树，并且当前节点的答案可以由空节点情况、当前节点值以及左右子树结果共同决定。
- 核心骨架：先定义递归函数返回给父节点的信息；处理空节点；递归处理左右子树；把左右结果和当前节点合并后返回。
- 关键边界：空节点返回值必须和题意匹配；如果是双树题，要先处理两个节点是否同时为空或只有一个为空；不要在递归前覆盖还需要继续访问的子树指针。
- 复杂度：时间通常为 `O(n)`，空间为 `O(h)`，其中 `h` 是树高。

```cpp
class Solution {
public:
    int treeRecursionTemplate(TreeNode* root) {
        if (root == nullptr) {
            return 0; // 按题意定义空节点返回值。
        }

        int left = treeRecursionTemplate(root->left);
        int right = treeRecursionTemplate(root->right);
        return combine(root, left, right); // 合并当前节点与左右子树结果。
    }

private:
    int combine(TreeNode* root, int left, int right) {
        return max(left, right) + 1;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `226. Invert Binary Tree` | 待提交验证，源码逻辑检查通过 | 正确先递归得到左右子树结果，再交换当前节点指针，避免覆盖原子树。 | 复盘时说清函数返回的是“翻转后的当前子树根”。 | [查看](../leetcode-reviews/2026-05-28-226-invert-binary-tree.md) |
| `104. Maximum Depth of Binary Tree` | 待提交验证，源码逻辑检查通过 | 空节点返回 `0`、左右深度取最大再加一，返回值定义非常清楚。 | 后续高度类题要继续区分“返回给父节点的信息”和“全局答案”。 | [查看](../leetcode-reviews/2026-05-28-104-maximum-depth-of-binary-tree.md) |
| `100. Same Tree` | 待提交验证，源码逻辑检查通过 | 能完整处理双空、单空、值不同和左右子树同步比较。 | 空节点分支可以简化，但当前正确性没有问题。 | [查看](../leetcode-reviews/2026-05-28-100-same-tree.md) |

- 暴露问题：今天整体很稳，三题都已经抓住“先定义递归返回值，再处理空节点，再合并左右结果”的主线。主要需要继续强化口述能力：每道题都要能一句话说出递归函数返回给父节点的是什么。
- 下一步安排：进入第 2 天分层观察与视角结果。下一组题会从递归调用栈切换到按层维护节点，重点观察每一层的边界和结果收集时机。

## 进度更新 - 2026-05-29

- 今日完成：`102. Binary Tree Level Order Traversal`、`103. Binary Tree Zigzag Level Order Traversal`、`199. Binary Tree Right Side View`
- 当前主题：第 2 天 - 分层观察与视角结果

### 通用解题模板

- 适用条件：题目要求按树的每一层收集、变形或提取结果，例如每层数组、交替方向、每层代表节点。
- 核心骨架：队列从根节点开始；每轮先记录当前队列大小作为本层边界；只处理固定数量节点；处理过程中把非空孩子加入队列，留到下一层。
- 关键边界：空树直接返回空结果；必须在进入本层循环前保存 `levelSize`；不要用循环中的动态 `q.size()` 判断本层结束；输出方向可以改变，但队列推进顺序通常保持左、右孩子自然入队。
- 复杂度：时间 `O(n)`，空间 `O(w)`，其中 `w` 是树的最大宽度。

```cpp
class Solution {
public:
    vector<vector<int>> levelTemplate(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            vector<int> level;

            // 当前循环只消费本层节点，孩子节点留给下一轮。
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);

                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            ans.push_back(level);
        }
        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `102. Binary Tree Level Order Traversal` | 待提交验证，源码逻辑检查通过 | 能稳定用 `q.size()` 冻结当前层边界，每层结果不会混入下一层。 | 变量名可以更语义化；复盘时说清 `levelSize` 的作用。 | [查看](../leetcode-reviews/2026-05-29-102-binary-tree-level-order-traversal.md) |
| `103. Binary Tree Zigzag Level Order Traversal` | 待提交验证，源码逻辑检查通过 | 复用层序骨架，只改变当前层输出方向，没有破坏队列推进顺序。 | 可以进一步练习“按下标写入”来省掉反转步骤。 | [查看](../leetcode-reviews/2026-05-29-103-binary-tree-zigzag-level-order-traversal.md) |
| `199. Binary Tree Right Side View` | 待提交验证，源码逻辑检查通过 | 正确把右视图转化为每层最后一个节点，思路直接且稳。 | 建议补充右优先 DFS 视角，训练“第一次到达某深度”的建模。 | [查看](../leetcode-reviews/2026-05-29-199-binary-tree-right-side-view.md) |

- 暴露问题：第 2 天整体完成质量很好，层边界已经稳定；主要提升点不是正确性，而是把“遍历顺序”和“输出顺序”分开讲清楚。
- 下一步安排：进入第 3 天高度、平衡与公共祖先。`110. Balanced Binary Tree` 已创建但尚未实现，可以先用它承接“子树返回高度，当前节点判断性质”的训练。

## 进度更新 - 2026-05-29（第 3 天）

- 今日完成：`110. Balanced Binary Tree`、`543. Diameter of Binary Tree`、`236. Lowest Common Ancestor of a Binary Tree`
- 当前主题：第 3 天 - 高度、平衡与公共祖先

### 通用解题模板

- 适用条件：题目要求根据左右子树结果判断当前节点性质、更新全局答案，或把命中状态向父节点传播。
- 核心骨架：先定义递归返回给父节点的信息；空节点返回题意下的中性值；递归处理左右子树；当前节点根据左右结果更新局部判断或全局答案；最后返回父节点需要的单一信息。
- 关键边界：返回给父节点的信息不能混入只能在当前节点结算的全局答案；路径类题通常只能向上贡献单边结果；公共祖先类题要允许目标节点本身作为祖先。
- 复杂度：时间 `O(n)`，空间 `O(h)`，其中 `h` 是树高。

```cpp
class Solution {
    int answer = 0;

    int treePostorderTemplate(TreeNode* root) {
        if (root == nullptr) {
            return 0; // 空节点返回当前题的中性值。
        }

        int left = treePostorderTemplate(root->left);
        int right = treePostorderTemplate(root->right);

        // 在当前节点合并左右结果，必要时更新全局答案。
        answer = max(answer, combineForGlobal(left, right));
        return contributionToParent(left, right); // 返回父节点真正需要的信息。
    }

    int combineForGlobal(int left, int right) {
        return left + right;
    }

    int contributionToParent(int left, int right) {
        return max(left, right) + 1;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `110. Balanced Binary Tree` | 待提交验证，源码逻辑检查通过 | 能一次递归同时返回高度和平衡性，并在子树失败时提前剪枝。 | `pair<int, int>` 的第二项语义实际是 bool，可改成哨兵或更明确类型。 | [查看](../leetcode-reviews/2026-05-29-110-balanced-binary-tree.md) |
| `543. Diameter of Binary Tree` | 待提交验证，源码逻辑检查通过 | 正确区分“返回给父节点的高度”和“当前节点更新的全局直径”。 | 成员变量 `ans` 在复用对象多次调用时要重置；可改局部变量引用。 | [查看](../leetcode-reviews/2026-05-29-543-diameter-of-binary-tree.md) |
| `236. Lowest Common Ancestor of a Binary Tree` | 待提交验证，源码逻辑检查通过 | 覆盖目标节点本身作为祖先的情况，并能把已找到的 LCA 向上传播。 | 当前分支略复杂，建议熟悉更标准的左右结果合并模板。 | [查看](../leetcode-reviews/2026-05-29-236-lowest-common-ancestor-of-a-binary-tree.md) |

- 暴露问题：今天整体已经进入树题核心区，最大进步是开始稳定区分“子树返回给父节点的信息”和“当前节点自己结算的答案”。主要复盘点是减少分支复杂度，让返回值语义更统一。
- 下一步安排：进入第 4 天二叉搜索树基础判断。接下来从普通二叉树的后序合并切到 BST 的全局有序限制，重点观察限制是只看父子节点，还是要覆盖整棵左右子树。
