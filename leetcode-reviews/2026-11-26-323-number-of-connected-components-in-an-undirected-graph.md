# 题解点评 - 323. Number of Connected Components in an Undirected Graph（无向图中连通分量的数目）

## 基本信息

- 日期：2026-11-26
- 主题：第 12 周拓扑排序与并查集 - 并查集入门（第 3 天）
- 难度：中等（Plus 会员锁定页未直接显示，按通行信息标注）
- 本次结果：通过（用户确认已通过测试；本地测试套 10/10 ACCEPTED）
- 对应源码：[src/323.cpp](../src/323.cpp)（文件名无题名后缀，与 252/269/286 同类命名情况，留档待用户决定统一）
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/number-of-connected-components-in-an-undirected-graph/)，2026-11-26 查询——**页面被 Plus 会员墙锁定**，仅确认题名"无向图中连通分量的数目"与锁定状态；难度与约束按通行信息整理，标注"未联网校准细节"
- 通行约束要点：`1 <= n <= 2000`；`1 <= edges.length <= 5000`（通行信息）；题目问边表给出的图的连通分量个数

## 用户思路概述

1. 同一套 `UnionFind`（fa/sz/cnt 三件套）第二度出鞘。
2. 逐边 `unite`（不检查 connected——合并失败自动 no-op，不用先查再合）。
3. 返回 `uf.count()`——cnt 从 n 初始化，每次成功合并减一，终值即分量数。
4. 文件内置本地测试套（10 组样例，含全孤立、全连通、多分量、重边），全部通过。

## 用户解法复杂度

- 时间复杂度：`O((n + E) · α(n))`（初始化 n + 逐边合并）
- 空间复杂度：`O(n)`
- 复杂度来源：cnt 在合并动作中增量维护，免去了终态扫描（数 fa[i]==i 或 BFS 访问）那一次 O(n) 与一份数组遍历逻辑。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class UnionFind {
    vector<int> fa, sz;
    int cnt;                     // 从 n 起，unite 成功一次减一
    public:
    // ...（find/unite/connected/size/count 同 684 文件，略）
};
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for(auto e: edges) {
            int x=e[0], y=e[1];
            uf.unite(x, y);       // 直接合：失败即 no-op，免 connected 预查
        }
        return uf.count();        // 增量维护的分量计数，直接读
    }
};
```

（UnionFind 实现同 684 文件，`find` 路径压缩 + 小挂大 + cnt 增量维护，此处从略。）

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 增量维护 cnt | 构造从 n 起、unite 成功减一、count 直接读 | 免终态扫描的维护时机选择正确——这是 cnt 三件套的价值兑现 | 归纳一句：**"合并次数 = n - 分量数"**，cnt 是这条恒等式的运行时载体 |
| 免预查直接 unite | `unite` 内部先查同根自然 no-op | 省 323 场景下"先查后合"的重复计算；调用点最简 | 知道 684（冲突即答案）与 323（冲突即忽略）两种调用策略的差异——题目语义决定检查位置 |
| 与第 11 周 547 对照 | BFS 需外层枚举 + vis 数组；并查集版无外层循环 | 代码量差距一目了然：23 行 vs 3 行主体 | 本日核心复盘：同一道题两条脉络，写出取舍判断式 |
| 本地测试套 | 10 组样例含重边、空边、全孤立 | 覆盖面完整（含 {0,2}/{2,0} 类重复边不重复计数） | 该 main 含结构化绑定（C++17），保持原样即可；继续以本地套验证再提交 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（增量并查集） | 近线性免扫描；边动态加入也适用 | 无 | 边表输入的标准解 |
| BFS/DFS 分量计数（第 11 周 547 脉络） | 免写并查集类 | 需建邻接表 + 外层循环 + vis | 边静态、一次成图时也可 |
|DFS 多源汇点 | 无 | 不适用 | - |

## 最优解法

- 与用户解法同构：逐边 unite（失败自动忽略），读 cnt。
- 关键不变量：`cnt = n - 已成功合并次数`；终值即连通分量数。
- 最优时间复杂度：`O((n + E) · α(n))`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
    // 与用户类实现同构（fa/sz/cnt + 路径压缩 + 小挂大）；
    // 独立最简形态：数组 + 循环内联
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> fa(n), sz(n, 1);
        iota(fa.begin(), fa.end(), 0);
        int cnt = n;                     // 初始每人自成一类
        // 迭代隔代压缩查根
        auto findIt = [&](int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]];      // 隔代跳两层
                x = fa[x];
            }
            return x;
        };
        for (const auto& e : edges) {
            int rx = findIt(e[0]), ry = findIt(e[1]);
            if (rx == ry) continue;      // 同根：忽略（等价 unite 失败 no-op）
            if (sz[rx] < sz[ry]) swap(rx, ry);
            fa[ry] = rx;
            sz[rx] += sz[ry];
            cnt--;                       // 成功合并：分量数减一
        }
        return cnt;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 图结构 | 类封装（复用板子） | 行内数组最简形态 | 类版是正解——本套 UnionFind 三题复用中 |
| cnt 维护 | unite 内增量 | 循环内联递减 | 两种位置等价；类内维护让调用点最简 |
| 边界处理 | 空边表返回 n、重边 no-op、自环 no-op 全对 | 相同 | 已达标 |
| 复杂度 | `O((n+E)α)` / `O(n)` | 相同 | 已达最优 |

用户解法与推荐最优解同构（类封装 vs 行内两形态），本题完成质量高。

## 下一步建议

- 复盘任务（本日核心）：并排书写 547 的 BFS 版与本题的并查集版，从代码行数、额外结构、边动态加入的适配性三个方面写出取舍判断式。
- 验证一致性：本地测试套 10/10 已全过，题面确认 Plus 锁定页细节后（如有机会）可对照数值约束。

## 后续练习

1. `261. Graph Valid Tree` - 同日题单，cnt 语义加一条"恰为 1"的静态检查即成。
2. `305. Number of Islands II` - 第 5 天困难题，把 cnt 维护从"边流"搬到"点流"，动态版正在那里。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/323.cpp](../src/323.cpp)
- 新函数名：`countComponentsOpt`（行内最简形态），位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（含本地 main 测试套，保持不动）
- 备注：323 为 Plus 会员锁定题，题面细节按通行信息整理，点评中已标注"未联网校准细节"；文件名 `323.cpp` 无题名后缀，留档待统一。
