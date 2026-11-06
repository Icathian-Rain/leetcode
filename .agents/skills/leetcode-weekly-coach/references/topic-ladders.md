# 主题梯度参考

在选择下一周主题、每日题单或点评后的跟练题时使用。这里保留本地训练路线；题号、难度、标签或约束需要精确时，按 `SKILL.md` 的联网查题规则校准。

## 默认主题顺序

除非用户指定主题，或已有自定义路线图，否则按下面顺序推进：

1. 数组与哈希
2. 双指针与滑动窗口
3. 栈与队列
4. 链表
5. 二分查找
6. 树与二叉搜索树
7. 回溯
8. 动态规划

完成核心 8 周后，可以继续扩展主题：

1. 堆与优先队列
2. 区间与贪心
3. 图论 BFS 与 DFS
4. 拓扑排序与并查集

## 每日梯度规则

1. 热身题：让基础模式清晰可见，优先简单题。
2. 核心题：逼用户真正使用本周主题技巧，优先中等题。
3. 拔高题：加入变体、额外数据结构或更恶劣的边界。

压缩成 2 题时：

- 轻量日用“热身 + 核心”。
- 回顾日或模拟面试日用“核心 + 拔高”。

## 数组与哈希

周目标：建立查找、计数、分组、前缀预处理这几类模式的快速识别能力。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 1 | Two Sum | 简单 | 哈希表查找补数 | `O(n)` / `O(n)` |
| 热身 | 217 | Contains Duplicate | 简单 | 哈希集合去重 | `O(n)` / `O(n)` |
| 热身 | 242 | Valid Anagram | 简单 | 频次统计 | `O(n)` / `O(1)` |
| 热身 | 169 | Majority Element | 简单 | Boyer-Moore 投票 | `O(n)` / `O(1)` |
| 核心 | 49 | Group Anagrams | 中等 | 规范化 key 分组 | `O(nk log k)` / `O(nk)` |
| 核心 | 347 | Top K Frequent Elements | 中等 | 频次表 + 桶/堆 | `O(n)` 或 `O(n log k)` |
| 核心 | 238 | Product of Array Except Self | 中等 | 前后缀乘积 | `O(n)` / `O(1)` 额外空间 |
| 核心 | 560 | Subarray Sum Equals K | 中等 | 前缀和 + 哈希计数 | `O(n)` / `O(n)` |
| 拔高 | 128 | Longest Consecutive Sequence | 中等 | 哈希集合找序列起点 | `O(n)` / `O(n)` |
| 拔高 | 41 | First Missing Positive | 困难 | 原地哈希/索引归位 | `O(n)` / `O(1)` |

## 双指针与滑动窗口

周目标：学会通过排序后的双指针或可移动窗口缩小搜索空间。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 125 | Valid Palindrome | 简单 | 相向双指针 | `O(n)` / `O(1)` |
| 热身 | 26 | Remove Duplicates from Sorted Array | 简单 | 快慢指针原地覆盖 | `O(n)` / `O(1)` |
| 热身 | 977 | Squares of a Sorted Array | 简单 | 相向双指针填充 | `O(n)` / `O(n)` |
| 核心 | 167 | Two Sum II - Input Array Is Sorted | 中等 | 有序数组双指针 | `O(n)` / `O(1)` |
| 核心 | 11 | Container With Most Water | 中等 | 贪心移动短板 | `O(n)` / `O(1)` |
| 核心 | 3 | Longest Substring Without Repeating Characters | 中等 | 滑动窗口去重 | `O(n)` / `O(k)` |
| 拔高 | 15 | 3Sum | 中等 | 排序 + 去重双指针 | `O(n^2)` / `O(1)` |
| 拔高 | 567 | Permutation in String | 中等 | 固定窗口频次 | `O(n)` / `O(1)` |
| 拔高 | 76 | Minimum Window Substring | 困难 | 可变窗口覆盖需求 | `O(n)` / `O(k)` |

## 栈与队列

周目标：识别 LIFO/FIFO 结构，以及单调栈、单调队列等模式。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 20 | Valid Parentheses | 简单 | 栈匹配 | `O(n)` / `O(n)` |
| 热身 | 232 | Implement Queue using Stacks | 简单 | 双栈摊还 | `O(1)` 摊还 |
| 热身 | 682 | Baseball Game | 简单 | 栈模拟 | `O(n)` / `O(n)` |
| 核心 | 155 | Min Stack | 中等 | 辅助栈维护最小值 | `O(1)` 操作 |
| 核心 | 150 | Evaluate Reverse Polish Notation | 中等 | 栈计算表达式 | `O(n)` / `O(n)` |
| 核心 | 739 | Daily Temperatures | 中等 | 单调栈找下一个更大 | `O(n)` / `O(n)` |
| 拔高 | 853 | Car Fleet | 中等 | 排序 + 单调栈思想 | `O(n log n)` / `O(n)` |
| 拔高 | 84 | Largest Rectangle in Histogram | 困难 | 单调栈边界 | `O(n)` / `O(n)` |
| 拔高 | 239 | Sliding Window Maximum | 困难 | 单调队列 | `O(n)` / `O(k)` |

## 链表

周目标：练熟指针移动、原地修改、环检测和链表重排。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 206 | Reverse Linked List | 简单 | 三指针反转 | `O(n)` / `O(1)` |
| 热身 | 21 | Merge Two Sorted Lists | 简单 | 哑节点合并 | `O(n+m)` / `O(1)` |
| 热身 | 141 | Linked List Cycle | 简单 | 快慢指针 | `O(n)` / `O(1)` |
| 核心 | 19 | Remove Nth Node From End of List | 中等 | 双指针间距 | `O(n)` / `O(1)` |
| 核心 | 143 | Reorder List | 中等 | 找中点 + 反转 + 合并 | `O(n)` / `O(1)` |
| 核心 | 2 | Add Two Numbers | 中等 | 进位模拟 | `O(n+m)` / `O(1)` |
| 拔高 | 138 | Copy List with Random Pointer | 中等 | 哈希映射或原地穿插 | `O(n)` / `O(n)` 或 `O(1)` |
| 拔高 | 25 | Reverse Nodes in k-Group | 困难 | 分组反转 | `O(n)` / `O(1)` |
| 拔高 | 146 | LRU Cache | 中等 | 哈希表 + 双向链表 | `O(1)` 操作 |

## 二分查找

周目标：基于单调性和边界模板做二分，而不是靠感觉试探。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 704 | Binary Search | 简单 | 闭区间/半开区间模板 | `O(log n)` / `O(1)` |
| 热身 | 35 | Search Insert Position | 简单 | lower_bound 思维 | `O(log n)` / `O(1)` |
| 热身 | 374 | Guess Number Higher or Lower | 简单 | 答案空间二分 | `O(log n)` / `O(1)` |
| 核心 | 74 | Search a 2D Matrix | 中等 | 矩阵映射二分 | `O(log mn)` / `O(1)` |
| 核心 | 875 | Koko Eating Bananas | 中等 | 二分答案 + 可行性 | `O(n log M)` / `O(1)` |
| 核心 | 153 | Find Minimum in Rotated Sorted Array | 中等 | 旋转数组二分 | `O(log n)` / `O(1)` |
| 拔高 | 33 | Search in Rotated Sorted Array | 中等 | 分段有序判断 | `O(log n)` / `O(1)` |
| 拔高 | 1011 | Capacity To Ship Packages Within D Days | 中等 | 二分容量 | `O(n log S)` / `O(1)` |
| 拔高 | 4 | Median of Two Sorted Arrays | 困难 | 分割二分 | `O(log(min(m,n)))` / `O(1)` |

## 树与二叉搜索树

周目标：在递归遍历、迭代遍历、BST 性质之间自由切换。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 226 | Invert Binary Tree | 简单 | 递归交换 | `O(n)` / `O(h)` |
| 热身 | 104 | Maximum Depth of Binary Tree | 简单 | DFS 深度 | `O(n)` / `O(h)` |
| 热身 | 100 | Same Tree | 简单 | 双树递归 | `O(n)` / `O(h)` |
| 核心 | 102 | Binary Tree Level Order Traversal | 中等 | BFS 分层 | `O(n)` / `O(w)` |
| 核心 | 98 | Validate Binary Search Tree | 中等 | 上下界递归/中序 | `O(n)` / `O(h)` |
| 核心 | 230 | Kth Smallest Element in a BST | 中等 | BST 中序 | `O(h+k)` / `O(h)` |
| 拔高 | 235 | Lowest Common Ancestor of a BST | 中等 | BST 分叉点 | `O(h)` / `O(1)` |
| 拔高 | 199 | Binary Tree Right Side View | 中等 | BFS/DFS 视图 | `O(n)` / `O(h)` |
| 拔高 | 124 | Binary Tree Maximum Path Sum | 困难 | 后序贡献值 | `O(n)` / `O(h)` |

## 回溯

周目标：建立状态空间搜索意识，学会维护路径、选择列表和剪枝条件。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 78 | Subsets | 中等 | 选/不选或 start 索引 | `O(n * 2^n)` |
| 热身 | 17 | Letter Combinations of a Phone Number | 中等 | 多叉选择树 | `O(4^n)` |
| 核心 | 39 | Combination Sum | 中等 | 可重复选择 + 剪枝 | 指数级 |
| 核心 | 46 | Permutations | 中等 | used 数组排列 | `O(n!)` |
| 核心 | 79 | Word Search | 中等 | 网格 DFS + 回溯标记 | `O(mn4^L)` |
| 拔高 | 131 | Palindrome Partitioning | 中等 | 分割枚举 + 回文判断 | 指数级 |
| 拔高 | 40 | Combination Sum II | 中等 | 排序去重剪枝 | 指数级 |
| 拔高 | 51 | N-Queens | 困难 | 约束集合剪枝 | 指数级 |

## 动态规划

周目标：先想清楚状态、转移和初始条件，再动手写代码。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 70 | Climbing Stairs | 简单 | 一维递推 | `O(n)` / `O(1)` |
| 热身 | 746 | Min Cost Climbing Stairs | 简单 | 一维最小代价 | `O(n)` / `O(1)` |
| 热身 | 198 | House Robber | 中等 | 选/不选状态 | `O(n)` / `O(1)` |
| 核心 | 322 | Coin Change | 中等 | 完全背包最小值 | `O(amount*n)` |
| 核心 | 416 | Partition Equal Subset Sum | 中等 | 0/1 背包可达性 | `O(n*sum)` |
| 核心 | 300 | Longest Increasing Subsequence | 中等 | DP 或 贪心二分 | `O(n^2)` 或 `O(n log n)` |
| 拔高 | 1143 | Longest Common Subsequence | 中等 | 二维序列 DP | `O(mn)` |
| 拔高 | 91 | Decode Ways | 中等 | 字符串一维 DP | `O(n)` / `O(1)` |
| 拔高 | 139 | Word Break | 中等 | 前缀可达 DP | `O(n^2)` |

## 堆与优先队列

周目标：维护动态极值，以及滚动变化下的 top-k 结构。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 703 | Kth Largest Element in a Stream | 简单 | 大小为 k 的小根堆 | `O(log k)` 操作 |
| 热身 | 1046 | Last Stone Weight | 简单 | 大根堆模拟 | `O(n log n)` |
| 核心 | 973 | K Closest Points to Origin | 中等 | 堆/快速选择 | `O(n log k)` 或 `O(n)` |
| 核心 | 621 | Task Scheduler | 中等 | 频次贪心/堆模拟 | `O(n)` 或 `O(n log k)` |
| 核心 | 658 | Find K Closest Elements | 中等 | 二分窗口/堆 | `O(log(n-k)+k)` |
| 拔高 | 295 | Find Median from Data Stream | 困难 | 双堆平衡 | `O(log n)` 操作 |
| 拔高 | 23 | Merge k Sorted Lists | 困难 | 小根堆合并 | `O(N log k)` |

## 区间与贪心

周目标：学会排序事件、合并区间，并为局部最优决策给出理由。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 56 | Merge Intervals | 中等 | 排序后合并 | `O(n log n)` |
| 热身 | 57 | Insert Interval | 中等 | 分段处理区间 | `O(n)` |
| 热身 | 605 | Can Place Flowers | 简单 | 局部合法贪心 | `O(n)` / `O(1)` |
| 核心 | 435 | Non-overlapping Intervals | 中等 | 按右端点贪心 | `O(n log n)` |
| 核心 | 55 | Jump Game | 中等 | 最远可达 | `O(n)` / `O(1)` |
| 核心 | 763 | Partition Labels | 中等 | 最远结束位置 | `O(n)` / `O(1)` |
| 拔高 | 134 | Gas Station | 中等 | 总量 + 当前亏空 | `O(n)` / `O(1)` |
| 拔高 | 846 | Hand of Straights | 中等 | 计数 + 顺子构造 | `O(n log n)` |
| 拔高 | 452 | Minimum Number of Arrows to Burst Balloons | 中等 | 按右端点贪心 | `O(n log n)` |

## 图论 BFS 与 DFS

周目标：区分图遍历、连通块统计、按层求最短路径这几类思维。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 1971 | Find if Path Exists in Graph | 简单 | 建图 + DFS/BFS | `O(n+e)` |
| 热身 | 733 | Flood Fill | 简单 | 网格 DFS/BFS | `O(mn)` |
| 热身 | 200 | Number of Islands | 中等 | 连通块染色 | `O(mn)` |
| 核心 | 133 | Clone Graph | 中等 | 图遍历 + 映射 | `O(V+E)` |
| 核心 | 994 | Rotting Oranges | 中等 | 多源 BFS | `O(mn)` |
| 核心 | 417 | Pacific Atlantic Water Flow | 中等 | 反向 DFS/BFS | `O(mn)` |
| 拔高 | 207 | Course Schedule | 中等 | 拓扑/环检测 | `O(V+E)` |
| 拔高 | 127 | Word Ladder | 困难 | BFS 最短转换 | `O(nL^2)` |
| 拔高 | 130 | Surrounded Regions | 中等 | 边界连通块 | `O(mn)` |

## 拓扑排序与并查集

周目标：识别依赖关系图和连通性合并问题。

| 阶段 | 题号 | 题目 | 难度 | 核心模式 | 典型复杂度 |
| --- | --- | --- | --- | --- | --- |
| 热身 | 997 | Find the Town Judge | 简单 | 入度/出度 | `O(n+e)` |
| 热身 | 684 | Redundant Connection | 中等 | 并查集判环 | `O(n alpha(n))` |
| 核心 | 210 | Course Schedule II | 中等 | 拓扑排序输出序列 | `O(V+E)` |
| 核心 | 323 | Number of Connected Components in an Undirected Graph | 中等 | 并查集/DFS | `O(n+e)` |
| 核心 | 721 | Accounts Merge | 中等 | 并查集合并账号 | `O(nk alpha(nk))` |
| 拔高 | 1584 | Min Cost to Connect All Points | 中等 | 最小生成树 | `O(n^2 log n)` |
| 拔高 | 269 | Alien Dictionary | 困难 | 建图 + 拓扑序 | `O(V+E)` |

## 复盘后的跟练建议

- 如果用户还没有掌握当前模式，优先留在同一主题内补弱。
- 如果当前主题已经稳定，安排一个相邻主题的迁移题。
- 当用户明显卡住时，给 1 道补弱题和 1 道迁移题。
- 点评后跟练题优先选择本文件中同主题且未出现在近期计划/点评里的题。
