# 题解点评 - 124. Binary Tree Maximum Path Sum

## 基本信息

- 日期：2026-06-01
- 主题：第 6 周 - 路径、贡献值与困难边界
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/124.binary-tree-maximum-path-sum.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki / leetcode.ca 检索摘要
- 查询日期：2026-06-01

## 用户思路概述

1. 用成员变量 `ans` 保存全局最大路径和，并初始化为 `INT_MIN` 以覆盖全负树。
2. DFS 返回当前节点能向父节点贡献的最大单边路径和。
3. 空节点返回 0。
4. 当前节点先递归得到左右子树贡献。
5. 用 `leftMax + rightMax + root->val` 更新经过当前节点并连接左右两侧的路径。
6. 再计算当前节点向父节点返回的单边贡献，并用它更新全局答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(h)`
- 复杂度来源：每个节点访问一次；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
    int ans=INT_MIN;

    int dfs(TreeNode* root) {
        if(root == nullptr) return 0;

        int leftMax = dfs(root->left);
        int rightMax = dfs(root->right);
        // 当前节点作为拐点时，可以把左右两侧都纳入全局答案。
        ans = max(ans, leftMax+rightMax+root->val);
        // 返回给父节点时，只能选择一侧继续向上延伸，或只选当前节点。
        int ret = max({leftMax+root->val, rightMax+root->val, root->val});
        ans = max(ans, ret);
        return ret;
    }
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 贡献值和全局答案 | 返回单边贡献，全局答案可合并两边 | 抓住本题核心 | 这是很重要的树 DP 分工 |
| 全负树 | `ans = INT_MIN` | 能覆盖全负节点 | 正确 |
| 负贡献处理 | 通过 `ret` 选择当前节点或单边 | 正确但表达略绕 | 可用 `max(0, childGain)` 简化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确区分全局路径和向上贡献，能处理负数 | 负贡献没有显式截断，推理成本稍高；成员 `ans` 有复用风险 | 单次提交可用 |
| 推荐最优解 | 子树负贡献直接截断为 0，公式更统一 | 需要理解“空贡献”不是空路径答案 | 最大路径和标准模板 |

## 最优解法

1. DFS 返回当前节点向父节点贡献的最大单边路径和。
2. 对左右子树返回值取 `max(0, gain)`，负贡献不向当前节点延伸。
3. 当前节点作为路径拐点时，用 `root->val + leftGain + rightGain` 更新全局答案。
4. 返回父节点时只能选择 `root->val + max(leftGain, rightGain)`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(h)`

### 最优解代码

```cpp
class Solution {
    int maxGain(TreeNode* root, int& best) {
        if (root == nullptr) {
            return 0;
        }

        int leftGain = max(0, maxGain(root->left, best));
        int rightGain = max(0, maxGain(root->right, best));
        // 当前节点是路径最高拐点时，左右贡献都可以计入全局答案。
        best = max(best, root->val + leftGain + rightGain);
        return root->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        int best = INT_MIN;
        maxGain(root, best);
        return best;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `ans` 成员 + `dfs` 返回单边贡献 | 局部 `best` + `maxGain` 返回单边贡献 | 减少状态残留 |
| 更新逻辑 | 同时比较双边路径和单边返回 | 负贡献先截断，再统一更新 | 公式更容易复用 |
| 边界处理 | 空节点返回 0，全负树覆盖 | 相同 | 正确 |
| 复杂度 | `O(n)` / `O(h)` | `O(n)` / `O(h)` | 已是最优 |

## 下一步建议

做跟练题。当前题已经把第 6 周最关键的“贡献值 vs 全局答案”吃下来了，建议用相邻题巩固。

## 后续练习

1. `543. Diameter of Binary Tree` - 回看同一个贡献值模型的边数版本。
2. `687. Longest Univalue Path` - 继续练单边贡献和经过当前节点的全局答案。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/124.binary-tree-maximum-path-sum.cpp`
- 新函数名：`maxPathSumOpt`
- 保留用户原实现：是
