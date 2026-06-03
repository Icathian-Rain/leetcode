# 题解点评 - 105. Construct Binary Tree from Preorder and Inorder Traversal

## 基本信息

- 日期：2026-06-03
- 主题：树与二叉搜索树，第 7 天综合复盘与结构迁移
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/105.construct-binary-tree-from-preorder-and-inorder-traversal.cpp`
- 资料来源：本地周计划与源码，未联网校准
- 查询日期：未联网

## 用户思路概述

1. 用半开区间 `[preL, preR)` 和 `[inL, inR)` 表示当前子树范围。
2. 前序区间的第一个值作为当前根节点。
3. 在线性扫描中序区间找到根节点位置，得到左子树大小，再切分左右子树递归构造。

## 用户解法复杂度

- 时间复杂度：最坏 `O(n^2)`
- 空间复杂度：`O(h)`
- 复杂度来源：每层递归都会在中序数组中线性查找根的位置；递归栈深度为树高。

## 用户代码注释版

```cpp
class Solution {
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int preL, int preR, int inL, int inR) {
        // 中序区间为空，当前子树为空。
        if(inL == inR) return nullptr;
        int rootVal = preorder[preL];
        TreeNode* root = new TreeNode(rootVal);
        int lpreL = preL+1;
        int lpreR;
        int linL  = inL;
        int linR = inL;
        // 找到根在中序里的位置，从而确定左子树长度。
        while(inorder[linR] != rootVal) {
            linR++;
        }
        int lSize = linR - linL;
        lpreR = lpreL+lSize;

        root->left = build(preorder, inorder, lpreL,lpreR, linL, linR);
        root->right = build(preorder, inorder, lpreR, preR, linR+1, inR);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 区间定义 | 使用半开区间 | 边界清楚，不容易漏节点 | 继续保持半开区间习惯 |
| 左子树长度 | 能由中序根位置推出 | 核心拆分正确 | 变量名可直接写成 `leftSize` |
| 根位置查找 | 每次递归线性扫描 | 退化树会变慢 | 预处理值到下标的映射 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 区间切分正确，容易手推 | 最坏 `O(n^2)` | 小输入或先练区间时可以接受 |
| 推荐最优解 | 每个节点只处理一次 | 需要额外哈希表 | 本题标准提交写法 |

## 最优解法

1. 预处理中序数组，把节点值映射到下标。
2. 每次用前序首元素确定根节点，再 `O(1)` 找到中序根位置。
3. 根据左子树长度切分前序和中序半开区间，递归构造左右子树。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
    unordered_map<int, int> inorderIndex;

    TreeNode* build(vector<int>& preorder, int preL, int preR, int inL, int inR) {
        if (preL == preR) return nullptr;
        int rootVal = preorder[preL];
        TreeNode* root = new TreeNode(rootVal);
        int rootIndex = inorderIndex[rootVal];
        int leftSize = rootIndex - inL;
        root->left = build(preorder, preL + 1, preL + 1 + leftSize, inL, rootIndex);
        root->right = build(preorder, preL + 1 + leftSize, preR, rootIndex + 1, inR);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        inorderIndex.clear();
        for (int i = 0; i < inorder.size(); ++i) {
            inorderIndex[inorder[i]] = i;
        }
        return build(preorder, 0, preorder.size(), 0, inorder.size());
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 两个遍历数组的半开区间 | 同样使用半开区间 | 状态已经很好 |
| 更新逻辑 | 扫描中序找根 | 哈希表直接定位根 | 消除重复查找 |
| 边界处理 | 用 `inL == inR` 判断空树 | 用 `preL == preR` 判断空树 | 两者都可以，保持一致即可 |
| 复杂度 | 最坏 `O(n^2)` | `O(n)` | 预处理索引 |

## 下一步建议

建议重写一遍最优版本，重点不是背代码，而是口头说清：前序负责给根，中序负责给左右子树边界。

## 后续练习

1. `106. Construct Binary Tree from Inorder and Postorder Traversal` - 迁移同一套区间切分。
2. `889. Construct Binary Tree from Preorder and Postorder Traversal` - 练习构造信息不足时的边界判断。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/105.construct-binary-tree-from-preorder-and-inorder-traversal.cpp`
- 新函数名：`buildTreeOpt`
- 保留用户原实现：是
