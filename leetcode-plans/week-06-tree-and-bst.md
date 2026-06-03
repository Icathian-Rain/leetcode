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

## 进度更新 - 2026-05-31

- 今日完成：`700. Search in a Binary Search Tree`、`98. Validate Binary Search Tree`、`230. Kth Smallest Element in a BST`、`235. Lowest Common Ancestor of a Binary Search Tree`
- 当前主题：第 4 天 - 二叉搜索树基础判断；并提前完成第 5 天第一题

### 通用解题模板

- 适用条件：题目明确给出二叉搜索树，要求查询节点、判断合法性、按有序顺序定位名次，或根据两个目标节点的位置关系找分叉点。
- 核心骨架：先判断当前节点是否为空或命中；利用左小右大的全局有序关系决定只走一侧，或用中序遍历把 BST 转成严格递增序列；涉及合法性判断时要携带祖先范围，而不是只比较父子节点。
- 关键边界：BST 合法性必须是严格不等；节点值可能到达 `-2^31`，哨兵值要用 `LLONG_MIN/LLONG_MAX` 或直接用上下界；成员变量计数或前驱值要注意多次调用时重置。
- 复杂度：搜索路径类通常时间 `O(h)`、空间递归 `O(h)` 或迭代 `O(1)`；中序遍历类通常时间 `O(n)` 或提前停止到 `O(h+k)`，空间 `O(h)`。

```cpp
class Solution {
public:
    TreeNode* bstSearchTemplate(TreeNode* root, int target) {
        while (root != nullptr) {
            if (root->val == target) {
                return root;
            }
            // BST 查询每次只保留可能含有目标的一侧。
            root = target < root->val ? root->left : root->right;
        }
        return nullptr;
    }

    bool bstRangeTemplate(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) {
            return true;
        }
        if (root->val <= lower || root->val >= upper) {
            return false;
        }
        return bstRangeTemplate(root->left, lower, root->val) &&
               bstRangeTemplate(root->right, root->val, upper);
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `700. Search in a Binary Search Tree` | 待提交验证，源码逻辑检查通过 | 正确根据大小关系只进入一侧子树，命中后返回整棵目标子树。 | 可补迭代写法，把空间降到 `O(1)`。 | [查看](../leetcode-reviews/2026-05-31-700-search-in-a-binary-search-tree.md) |
| `98. Validate Binary Search Tree` | 有边界风险，主体思路正确 | 抓住了中序遍历严格递增这个核心性质。 | `LONG_MIN` 在节点值取到 `-2^31` 时可能撞边界，建议改用上下界递归。 | [查看](../leetcode-reviews/2026-05-31-98-validate-binary-search-tree.md) |
| `230. Kth Smallest Element in a BST` | 待提交验证，源码逻辑检查通过 | 正确用中序遍历的升序访问定位第 k 小，并能找到后提前返回。 | 成员变量 `idx` 多次调用会残留；迭代中序或入口重置更稳。 | [查看](../leetcode-reviews/2026-05-31-230-kth-smallest-element-in-a-bst.md) |
| `235. Lowest Common Ancestor of a Binary Search Tree` | 待提交验证，源码逻辑检查通过 | 能把 LCA 转化为两条 BST 搜索路径的第一个分叉点。 | 当前递归正确；迭代版能把额外空间降为 `O(1)`。 | [查看](../leetcode-reviews/2026-05-31-235-lowest-common-ancestor-of-a-binary-search-tree.md) |

- 暴露问题：今天 BST 方向判断整体很稳，主要风险集中在“全局范围”和“成员状态”两类边界：98 不要用可能撞值域的哨兵，230 的计数状态要避免跨调用残留。
- 下一步安排：继续第 5 天二叉搜索树查询与修改。`701. Insert into a Binary Search Tree` 适合作为热身，`450. Delete Node in a BST` 是今天 BST 搜索路径训练后的主要挑战。

## 进度更新 - 2026-05-31（第 5 天补充）

- 今日完成：`701. Insert into a Binary Search Tree`、`450. Delete Node in a BST`
- 当前主题：第 5 天 - 二叉搜索树查询与修改

### 通用解题模板

- 适用条件：题目要求在 BST 中插入、删除或裁剪节点，并在修改后保持 BST 的有序结构。
- 核心骨架：搜索阶段根据 `key/val` 与当前节点值的大小关系只进入一侧；递归返回修改后的子树根；当前节点负责把左或右孩子重新接好；真正命中目标后再做局部结构重接。
- 关键边界：空子树往往就是插入位置或删除结束点；删除节点要区分无孩子、单孩子、双孩子；双孩子删除时可以用右子树最小节点或左子树最大节点承接另一侧子树；不要在未命中目标时同时递归左右两侧。
- 复杂度：时间 `O(h)`，空间递归 `O(h)`，其中 `h` 是树高；退化链表时最坏 `O(n)`。

```cpp
class Solution {
public:
    TreeNode* modifyBST(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->val) {
            root->left = modifyBST(root->left, key);
        } else if (key > root->val) {
            root->right = modifyBST(root->right, key);
        } else {
            // 命中目标后，在这里处理插入、删除或替换的局部结构。
            return rebuildLocalRoot(root);
        }
        return root;
    }

private:
    TreeNode* rebuildLocalRoot(TreeNode* root) {
        if (root->left == nullptr) return root->right;
        if (root->right == nullptr) return root->left;
        TreeNode* successor = root->right;
        while (successor->left != nullptr) successor = successor->left;
        successor->left = root->left;
        return root->right;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `701. Insert into a Binary Search Tree` | 待提交验证，源码逻辑检查通过 | 能在空位置创建新节点，并把修改后的子树根一路返回。 | 可补迭代写法，把额外空间从 `O(h)` 降到 `O(1)`。 | [查看](../leetcode-reviews/2026-05-31-701-insert-into-a-binary-search-tree.md) |
| `450. Delete Node in a BST` | 待提交验证，源码逻辑正确但复杂度可优化 | 删除目标后的三类结构处理完整，双孩子节点重接思路可行。 | 未命中时同时递归左右子树，没利用 BST 方向剪枝；应只递归一侧。 | [查看](../leetcode-reviews/2026-05-31-450-delete-node-in-a-bst.md) |

- 暴露问题：结构修改能力已经有了，尤其是能想到“双孩子删除后如何接回两边子树”。主要短板是搜索阶段要坚持 BST 的单侧路径，不要退回普通二叉树的全树 DFS。
- 下一步安排：进入第 6 天路径、贡献值与困难边界。建议先做 `112. Path Sum` 和 `113. Path Sum II`，把普通树路径状态重新练稳，再挑战 `124. Binary Tree Maximum Path Sum`。

## 进度更新 - 2026-06-01

- 今日完成：`112. Path Sum`、`113. Path Sum II`、`124. Binary Tree Maximum Path Sum`
- 当前主题：第 6 天 - 路径、贡献值与困难边界

### 通用解题模板

- 适用条件：题目围绕树上的路径展开，需要沿根到叶维护状态、收集路径，或在每个节点合并左右子树贡献更新全局答案。
- 核心骨架：根到叶路径题向下传递剩余目标值，并只在叶子结算；收集路径时使用 `push -> dfs -> pop` 回溯；最大路径类题让递归返回“能向父节点延伸的单边贡献”，全局答案在当前节点合并左右贡献。
- 关键边界：空节点不能构成根到叶路径；只有叶子节点代表完整路径；路径收集时必须撤销当前选择；最大路径和要允许全负树，负贡献不要向上延伸。
- 复杂度：通常时间 `O(n)`，空间 `O(h)`；如果需要复制所有路径，答案复制成本可能达到 `O(n*h)`。

```cpp
class Solution {
    int best = INT_MIN;

    int gainTemplate(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int left = max(0, gainTemplate(root->left));
        int right = max(0, gainTemplate(root->right));
        // 当前节点作为拐点时可以合并两侧；向父节点只能贡献一侧。
        best = max(best, root->val + left + right);
        return root->val + max(left, right);
    }

    void pathTemplate(TreeNode* root, int target, vector<int>& path) {
        if (root == nullptr) {
            return;
        }

        path.push_back(root->val);
        target -= root->val;
        if (root->left == nullptr && root->right == nullptr) {
            // 在叶子节点结算根到叶路径。
        } else {
            pathTemplate(root->left, target, path);
            pathTemplate(root->right, target, path);
        }
        path.pop_back();
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `112. Path Sum` | 待提交验证，源码逻辑检查通过 | 正确用剩余目标值向下传递，并且只在叶子节点判断完整路径。 | 叶子分支可以简化成直接比较当前节点值与剩余目标。 | [查看](../leetcode-reviews/2026-06-01-112-path-sum.md) |
| `113. Path Sum II` | 待提交验证，源码逻辑检查通过 | `path.push_back` 和 `path.pop_back` 的回溯位置正确，能隔离不同路径。 | 成员变量 `ans/path` 多次调用会残留；更稳的是入口局部变量传引用。 | [查看](../leetcode-reviews/2026-06-01-113-path-sum-ii.md) |
| `124. Binary Tree Maximum Path Sum` | 待提交验证，源码逻辑检查通过 | 已经区分“向父节点返回的单边贡献”和“当前节点合并两侧更新的全局答案”。 | 可以把负贡献显式截断为 0，让公式更稳定、更好迁移。 | [查看](../leetcode-reviews/2026-06-01-124-binary-tree-maximum-path-sum.md) |

- 暴露问题：今天整体质量很好，尤其是 124 已经抓住困难树题的核心分工。主要复盘点是减少成员变量残留风险，并把“负贡献不向上延伸”写成固定模板。
- 下一步安排：进入第 7 天综合复盘与结构迁移。建议按计划做 `572. Subtree of Another Tree`、`105. Construct Binary Tree from Preorder and Inorder Traversal`、`437. Path Sum III`，把双树比较、构造和路径统计收束到一轮复盘里。

## 进度更新 - 2026-06-03

- 今日完成：`572. Subtree of Another Tree`、`105. Construct Binary Tree from Preorder and Inorder Traversal`、`437. Path Sum III`
- 当前主题：第 7 天 - 综合复盘与结构迁移

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `572. Subtree of Another Tree` | 待提交验证，源码逻辑检查通过 | 能把 `Same Tree` 的双树比较嵌入整棵树搜索，结构判断完整。 | 朴素匹配最坏 `O(n*m)`；布尔递归建议用短路 `||`。 | [查看](../leetcode-reviews/2026-06-03-572-subtree-of-another-tree.md) |
| `105. Construct Binary Tree from Preorder and Inorder Traversal` | 待提交验证，源码逻辑检查通过 | 半开区间定义清楚，能正确由前序根和中序位置切分左右子树。 | 每次线性扫描中序位置，退化情况下会到 `O(n^2)`；可预处理下标。 | [查看](../leetcode-reviews/2026-06-03-105-construct-binary-tree-from-preorder-and-inorder-traversal.md) |
| `437. Path Sum III` | 有提交风险，核心算法正确 | 已命中前缀和计数 + 回溯模板，能一次 DFS 统计所有合法路径。 | 源码保留 `cout` 调试输出，且成员状态多次调用可能残留；提交前必须处理。 | [查看](../leetcode-reviews/2026-06-03-437-path-sum-iii.md) |

- 暴露问题：今天三题覆盖的是综合迁移，不共享单一通用模板，因此不强行沉淀一个大而泛的模板。主要问题集中在两类：一是最优复杂度意识，`572/105` 都可以通过预处理或序列化匹配减少重复工作；二是提交稳定性，`437` 的调试输出会直接污染结果。
- 下一步安排：第 6 周树专题可以进入总复盘。建议先把 `437` 的提交版本清理干净，再从 `572` 的双树比较、`105` 的构造区间、`437` 的路径前缀状态各挑一个小样例手推，确认自己能说清函数返回值和当前层维护的状态。
