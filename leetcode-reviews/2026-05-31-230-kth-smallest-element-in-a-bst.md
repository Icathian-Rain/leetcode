# 题解点评 - 230. Kth Smallest Element in a BST

## 基本信息

- 日期：2026-05-31
- 主题：第 6 周 - 二叉搜索树基础判断
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/230.kth-smallest-element-in-a-bst.cpp`
- 资料来源：LeetCode 官方题目页、检索摘要
- 查询日期：2026-05-31

## 用户思路概述

1. BST 的中序遍历会按升序访问节点。
2. 使用成员变量 `idx` 表示当前访问到第几个节点。
3. 先递归左子树，如果左子树已经找到答案就提前返回。
4. 当前节点是第 `k` 个时返回当前值。
5. 否则计数加一，继续递归右子树。

## 用户解法复杂度

- 时间复杂度：平均可提前停止到 `O(h + k)`，最坏 `O(n)`。
- 空间复杂度：`O(h)`。
- 复杂度来源：中序遍历只访问到第 k 小附近；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
    int idx = 1;
    int dfs(TreeNode* root, int k) {
        if(root == nullptr) return -1;
        // 先访问更小的左子树。
        int ans = dfs(root->left, k);
        if(ans != -1) return ans;
        // 当前节点是第 k 个中序节点时，返回答案。
        if(idx == k) return root->val;
        idx++;
        return dfs(root->right, k);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        return dfs(root, k);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| BST 中序有序 | 正确利用升序访问 | 算法方向正确 | 继续把“第 k 小”绑定到中序遍历 |
| 提前停止 | 找到答案后向上传播 | 避免遍历整棵树 | 做得好 |
| 成员状态 | `idx` 不在入口重置 | 同一个 `Solution` 对象多次调用会残留 | 用局部 `k` 或迭代写法更稳 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 递归中序清晰，可提前停止 | `idx` 成员状态可复用风险，`-1` 哨兵依赖值域 | 单次提交可用 |
| 推荐最优解 | 迭代中序，用 `k` 自减，无成员残留 | 需要手写栈 | 更稳定的提交模板 |

## 最优解法

1. 用栈模拟中序遍历。
2. 不断向左走，把路径节点入栈。
3. 弹出一个节点就代表访问到下一个升序值，同时 `k--`。
4. 当 `k == 0` 时返回当前节点值。

- 最优时间复杂度：`O(h + k)`，最坏 `O(n)`。
- 最优空间复杂度：`O(h)`。

### 最优解代码

```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }

            cur = st.top();
            st.pop();
            // 中序第 k 次访问到的节点就是第 k 小。
            if (--k == 0) {
                return cur->val;
            }
            cur = cur->right;
        }
        return -1;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员计数 `idx` | 局部剩余名次 `k` | 减少跨调用状态 |
| 更新逻辑 | 左-根-右递归 | 显式栈中序 | 同一模式不同实现 |
| 边界处理 | 依赖题目保证 k 合法 | 同样依赖 k 合法 | 可接受 |
| 复杂度 | `O(h+k)` / `O(h)` | `O(h+k)` / `O(h)` | 同阶最优 |

## 下一步建议

做跟练题。你已经抓住中序有序性，建议再练相邻值差、众数这类同一模板题。

## 后续练习

1. `530. Minimum Absolute Difference in BST` - 继续维护中序前驱。
2. `501. Find Mode in Binary Search Tree` - 继续用中序聚合同值段。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/230.kth-smallest-element-in-a-bst.cpp`
- 新函数名：`kthSmallestOpt`
- 保留用户原实现：是
