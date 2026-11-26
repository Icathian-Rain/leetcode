# 题解点评 - 684. Redundant Connection（冗余连接）

## 基本信息

- 日期：2026-11-26
- 主题：第 12 周拓扑排序与并查集 - 并查集入门（第 3 天）
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/684.redundant-connection.cpp](../src/684.redundant-connection.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/redundant-connection/)，2026-11-26 查询
- 约束要点：`3 <= n <= 1000`；边数恰为 n（树 + 1 条多余边）；`ai < bi` 且无重复边；多解时返回**输入顺序最后出现**的那条

## 用户思路概述

1. 手写 `UnionFind` 类：`fa` 父指针数组 + `sz` 大小数组 + `cnt` 分量计数三件套；`find` 带路径压缩（`fa[x] = find(fa[x])`），`unite` 小挂大（按秩合并）。
2. 逐边尝试加入：若两端 `connected` 已成立，则此边是环上的多余边，立即返回——第一个造成冲突的边在输入顺序上即最后可行的多余边。
3. 1 基输入转 0 基（`x-1, y-1`）。

## 用户解法复杂度

- 时间复杂度：`O(n · α(n))`（α 为反阿克曼函数，近常数）
- 空间复杂度：`O(n)`
- 复杂度来源：每条边一次 find×2 + 至多一次 unite；路径压缩 + 按大小合并后单次操作摊还近 O(1)。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class UnionFind {
    private:
        vector<int> fa, sz;   // fa: 父指针（根的 fa 是自身）；sz: 每棵树大小
        int cnt;              // 当前连通分量数
    public:
        UnionFind(int n): fa(n), sz(n, 1), cnt(n) {
            iota(fa.begin(), fa.end(), 0);   // 初始每人自成一类
        }
        int find(int x) {
            return fa[x] == x ? x : fa[x] = find(fa[x]);   // 查根 + 路径压缩一步到位
        }
        bool unite(int x, int y) {
            x = find(x);
            y = find(y);
            if(x == y) return false;
            if(sz[x] < sz[y]) swap(x, y);   // 小树挂到大树下
            fa[y] = x;
            sz[x] += sz[y];
            cnt --;                        // 合并成功：分量数减一
            return true;
        }
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
        int size(int x) {
            return sz[find(x)];
        }
        int count() {
            return cnt;
        }
};
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        UnionFind uf(n);
        for(auto edge: edges) {
            int x=edge[0], y=edge[1];
            if(uf.connected(x-1, y-1)) {   // 加入前两端已同根：此边成环
                return {x, y};              // 首个冲突边 = 输入顺序最后的多余边
            }
            uf.unite(x-1, y-1);
        }
        return {};
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| UnionFind 完整封装 | fa/sz/cnt 三件套 + 五个方法 | 一次性写出数据结构全量 API，且**三个文件用同一套实现**——这是本日做重要的产出，一条可长期复用的板子已经成型 | 把这个类抄进个人模板库；后续 323/261/721 直接调用 |
| 路径压缩写法 | `fa[x] = find(fa[x])` 递归三元 | 紧凑且正确——赋值发生在递归返回之后，挂到根上 | n=1000 递归深度安全；知道超大并查集要迭代化 |
| 小挂大 | `sz` 按大小合并（非按秩 `rank`） | 与按秩等价的优化形态 | 知道两者等价即可；按大小的好处是 `size()` 直接可查 |
| "冲突即答案"论证 | 首个 `connected` 成立的边立即返回 | 正确性关键：题目保证 n 条边恰含一个环；沿输入序逐边加入时，**环闭合的那条边**（即无法 unite 的第一条）删去后剩余恰为生成树——它同时是"最后出现的可行答案" | 复述这层双重身份的论证——为什么"第一条冲突边"恰好就是题目要的"最后一条可行边" |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（增量并查集） | `O(n·α)` 近线性；一次扫描；结构可复用 | 无 | 边动态加入判环的标准解 |
| DFS 找环（出度=2 的点集） | 能找具体环路径 | 要找"删最后边"需在环上定位最大下标，实现更绕 | 只要环不需要定位时可用 |
| 拓扑排序删边 | 换一个视角 | 本题所有点度数对称，无层可剥 | 不适用于本题 |

## 最优解法

- 与用户解法同构。逐边加入：两端已连通即为多余边，立即返回；否则合并。
- 关键不变量：处理到位置 i 时，前 i 条已加入的边构成森林（无环）；第一条无法加入的边恰是环上输入位置最靠后的边。
- 最优时间复杂度：`O(n · α(n))`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
    // 684 数据规模小，用数组即够；结构化封装同用户版
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = static_cast<int>(edges.size());
        vector<int> fa(n + 1, 0);          // 题目为 1 基，直接开 n+1 免去偏移换算
        vector<int> sz(n + 1, 1);
        for (int i = 0; i <= n; i++) fa[i] = i;

        // 路径压缩查根（迭代版，两行循环，免递归）
        auto findIt = [&](int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]];        // 隔代压缩：祖父一步跳两层
                x = fa[x];
            }
            return x;
        };

        for (const auto& e : edges) {
            int rx = findIt(e[0]), ry = findIt(e[1]);
            if (rx == ry) return e;        // 两端已同根：此边成环，即答案
            if (sz[rx] < sz[ry]) swap(rx, ry); // 小挂大
            fa[ry] = rx;
            sz[rx] += sz[ry];
        }
        return {};
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 结构 | 完整 UnionFind 类（可复用） | 行内 lambda 版（免类开销） | 类版是正解——数据结构该沉淀；lambda 版仅作"五分钟速写版"参考 |
| find 写法 | 递归全压缩 | 迭代隔代压缩 | 两种都取最优阶；隔代版免递归，超大并查集更稳 |
| 编号处理 | 1 基转 0 基 | 开 n+1 数组免转换 | 两种习惯都行；直接开 n+1 少一处 -1 心智负担 |
| 复杂度 | `O(n·α)` / `O(n)` | 相同 | 已达最优 |

用户解法即推荐最优解的类封装形态，本题完成质量高。本日三题共用这一套 UnionFind，标志着第 12 周的第二块基础设施落成。

## 下一步建议

- 复盘任务：说清"第一条冲突边 = 最后可行边"的论证（环闭合处删边 ⟺ 环上其余边按输入序均在其前）。
- 结构沉淀：把 UnionFind 类复制到个人模板库；对照第 11 周 547 的 BFS 分量计数，回答"同一道连通问题，两条脉络的代码量与思维负担差多少"。

## 后续练习

1. `685. Redundant Connection II` - 有向版冗余连接，冲突类型从"环"扩展到"环+双父"，是本题的进阶裁决版。
2. `721. Accounts Merge` - 第 4 天题单，并查集合并"邮箱"对象，检验类封装的复用性。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/684.redundant-connection.cpp](../src/684.redundant-connection.cpp)
- 新函数名：`findRedundantConnectionOpt`（lambda 简版），位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（含 UnionFind 类，德不改动）
- 备注：用户文件中 `class UnionFind` 定义于 `class Solution` 之前、`@lc code=start` 之后，提交时随 code 段一起提交，结构无碍。
