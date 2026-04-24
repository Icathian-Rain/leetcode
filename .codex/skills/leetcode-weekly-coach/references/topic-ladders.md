# 主题梯度参考

在选择下一周主题，或在单个主题内挑选每日题目梯度时，使用这份参考。

## 默认主题顺序

除非用户自己指定主题，或已经有一套自定义路线图，否则按下面顺序推进：

1. 数组与哈希
2. 双指针与滑动窗口
3. 栈与队列
4. 链表
5. 二分查找
6. 树与二叉搜索树
7. 回溯
8. 动态规划

完成核心 8 周后，可以继续这些扩展主题：

1. 堆与优先队列
2. 区间与贪心
3. 图论 BFS 与 DFS
4. 拓扑排序与并查集

## 主题模式

### 数组与哈希

- 周目标：建立查找、计数、分组、前缀预处理这几类模式的快速识别能力。
- 热身题池：`Two Sum`、`Contains Duplicate`、`Valid Anagram`、`Majority Element`。
- 核心题池：`Group Anagrams`、`Top K Frequent Elements`、`Product of Array Except Self`。
- 拔高题池：`Longest Consecutive Sequence`、`First Missing Positive`。

### 双指针与滑动窗口

- 周目标：学会通过排序后的双指针或可移动窗口缩小搜索空间。
- 热身题池：`Valid Palindrome`、`Remove Duplicates from Sorted Array`、`Squares of a Sorted Array`。
- 核心题池：`Two Sum II`、`Container With Most Water`、`Longest Substring Without Repeating Characters`。
- 拔高题池：`3Sum`、`Permutation in String`、`Minimum Window Substring`。

### 栈与队列

- 周目标：识别 LIFO/FIFO 结构，以及单调栈、单调队列等模式。
- 热身题池：`Valid Parentheses`、`Implement Queue using Stacks`、`Baseball Game`。
- 核心题池：`Min Stack`、`Evaluate Reverse Polish Notation`、`Daily Temperatures`。
- 拔高题池：`Car Fleet`、`Largest Rectangle in Histogram`、`Sliding Window Maximum`。

### 链表

- 周目标：练熟指针移动、原地修改、环检测和链表重排。
- 热身题池：`Reverse Linked List`、`Merge Two Sorted Lists`、`Linked List Cycle`。
- 核心题池：`Remove Nth Node From End of List`、`Reorder List`、`Add Two Numbers`。
- 拔高题池：`Copy List with Random Pointer`、`Reverse Nodes in k-Group`、`LRU Cache`。

### 二分查找

- 周目标：基于单调性和边界模板做二分，而不是靠感觉试探。
- 热身题池：`Binary Search`、`Search Insert Position`、`Guess Number Higher or Lower`。
- 核心题池：`Search a 2D Matrix`、`Koko Eating Bananas`、`Find Minimum in Rotated Sorted Array`。
- 拔高题池：`Search in Rotated Sorted Array`、`Capacity To Ship Packages Within D Days`、`Median of Two Sorted Arrays`。

### 树与二叉搜索树

- 周目标：在递归遍历、迭代遍历、BST 性质之间自由切换。
- 热身题池：`Invert Binary Tree`、`Maximum Depth of Binary Tree`、`Same Tree`。
- 核心题池：`Binary Tree Level Order Traversal`、`Validate Binary Search Tree`、`Kth Smallest Element in a BST`。
- 拔高题池：`Lowest Common Ancestor of a Binary Search Tree`、`Binary Tree Right Side View`、`Binary Tree Maximum Path Sum`。

### 回溯

- 周目标：建立状态空间搜索意识，学会尽早剪枝。
- 热身题池：`Subsets`、`Letter Combinations of a Phone Number`。
- 核心题池：`Combination Sum`、`Permutations`、`Word Search`。
- 拔高题池：`Palindrome Partitioning`、`Combination Sum II`、`N-Queens`。

### 动态规划

- 周目标：先想清楚状态、转移和初始条件，再动手写代码。
- 热身题池：`Climbing Stairs`、`Min Cost Climbing Stairs`、`House Robber`。
- 核心题池：`Coin Change`、`Partition Equal Subset Sum`、`Longest Increasing Subsequence`。
- 拔高题池：`Longest Common Subsequence`、`Decode Ways`、`Word Break`。

### 堆与优先队列

- 周目标：维护动态极值，以及滚动变化下的 top-k 结构。
- 热身题池：`Kth Largest Element in a Stream`、`Last Stone Weight`。
- 核心题池：`K Closest Points to Origin`、`Task Scheduler`、`Find K Closest Elements`。
- 拔高题池：`Find Median from Data Stream`、`Merge k Sorted Lists`。

### 区间与贪心

- 周目标：学会排序事件、合并区间，并为局部最优决策给出理由。
- 热身题池：`Merge Intervals`、`Insert Interval`、`Can Place Flowers`。
- 核心题池：`Non-overlapping Intervals`、`Jump Game`、`Partition Labels`。
- 拔高题池：`Gas Station`、`Hand of Straights`、`Minimum Number of Arrows to Burst Balloons`。

### 图论 BFS 与 DFS

- 周目标：区分图遍历、连通块统计、按层求最短路径这几类思维。
- 热身题池：`Find if Path Exists in Graph`、`Flood Fill`、`Number of Islands`。
- 核心题池：`Clone Graph`、`Rotting Oranges`、`Pacific Atlantic Water Flow`。
- 拔高题池：`Course Schedule`、`Word Ladder`、`Surrounded Regions`。

### 拓扑排序与并查集

- 周目标：识别依赖关系图和连通性合并问题。
- 热身题池：`Find the Town Judge`、`Redundant Connection`。
- 核心题池：`Course Schedule II`、`Number of Connected Components in an Undirected Graph`、`Accounts Merge`。
- 拔高题池：`Min Cost to Connect All Points`、`Alien Dictionary`。

## 每日梯度规则

在安排一天的题单时，遵循下面规则：

1. 先放 1 道热身题，让基础模式清晰可见。
2. 再放 1 道核心题，逼用户真正用上本周主题技巧。
3. 最后放 1 道拔高题，加入变体、额外数据结构或更恶劣的边界情况。

需要压缩成 2 题时：

- 轻量日用“热身 + 核心”。
- 回顾日或模拟面试日用“核心 + 拔高”。

## 复盘后的跟练建议

在题解点评后安排后续练习时：

- 如果用户还没有真正掌握当前模式，优先留在同一主题内。
- 只有当前主题已经稳定，才推进到下一主题。
- 当用户明显卡住时，给 1 道补弱题和 1 道迁移题。
