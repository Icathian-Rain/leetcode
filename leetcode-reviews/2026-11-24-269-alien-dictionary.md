# 题解点评 - 269. Alien Dictionary（火星词典）

## 基本信息

- 日期：2026-11-24
- 主题：第 12 周拓扑排序与并查集 - 拓扑顺序变体（第 2 天）
- 难度：困难（国际版通行难度；中国版页面为 Plus 会员锁定，页面未直接显示难度，按通行信息标注）
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/269.cpp](../src/269.cpp)（文件名为 `269.cpp`，无题名后缀，与 286/252 同类命名情况，留档待用户决定是否统一）
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/alien-dictionary/)，2026-11-24 查询——**页面被 Plus 会员墙锁定**，题意与约束按通行信息整理，标注"未联网校准细节"；解题模板与判定逻辑与本周主题一致可复核
- 通行约束要点：`1 <= words.length <= 100`；`1 <= words[i].length <= 100`；小写字母；单词可能相同；非法两种情形返回空串（字母序矛盾 / 前缀违反 `"ab" < "abc"` 方向）

## 用户思路概述

1. 全对对比建图：`(i, j)` 对 `i<j` 逐字符找首个不同位，得"字符先序边" `a → b`；用 26×26 的 `cmp` 矩阵存字符间已判定的大小关系，冲突立即返回空串。
2. 差一位短的（`k == min`）即前缀关系：前长后短（`a.size() > b.size()`）非法返回空串；`a` 是 `b` 前缀则合法。
3. `vis` 记录出现过的字母（来自任一单词的任何位），保证答案包含全部出现字母。
4. Kahn 排序：`vis && inDeg==0` 的字母入队，出队追加，出边清零入队。
5. 输出长度 ≠ 出现字母数（有环）返回空串。

## 用户解法复杂度

- 时间复杂度：总对比字符量 `O(n²·L)` = 100²×100 = 10⁶ 量级最坏（L = 词长）；**矩阵防重后建图与排序部分 `O(26·26)` 微不足道**
- 空间复杂度：`O(26² + Σ|word|)`（cmp 矩阵 + 邻接 26 桶）
- 复杂度来源：全对比对是这个规模（100 词）的通行做法；真正的优化（相邻对即可）见最优解，但这个体量全对也毫秒级。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        int n=words.size();
        vector<bool> vis(26, false);      // 出现过的字母（最终答案全集）
        vector<int> inDeg(26, 0);
        vector<vector<int>> next(26);    // 字符级邻接：next[a] = 排在 a 后面的字母
        vector<vector<int>> cmp(26, vector<int>(26, 0));  // cmp[a][b]: -1 a<b, 1 a>b, 0 未判定
        for(int i=0; i<n; i++) {
            string a=words[i];
            for(int k=0; k<a.size(); k++) {
                vis[a[k]-'a'] = true;       // 记录字母出现
            }
            for(int j=i+1; j<n; j++) {       // 全对比对（i<j 保证 a 排在 b 前）
                string b=words[j];
                int k=0;
                for(k=0; k<min(a.size(), b.size()); k++) {
                    if(a[k] == b[k]) continue;   // 跳过相同前缀
                    // 首个不同位：a[k] < b[k]
                    if(cmp[a[k]-'a'][b[k]-'a'] == 1) {
                        return "";               // 与已判定关系冲突：非法
                    }
                    else if(cmp[a[k]-'a'][b[k]-'a'] == 0) {
                        cmp[a[k]-'a'][b[k]-'a'] = -1;   // 判定 a<b
                        cmp[b[k]-'a'][a[k]-'a'] = 1;    // 对称记录 b>a
                        inDeg[b[k]-'a']++;
                        next[a[k]-'a'].push_back(b[k]-'a');  // 建字符先序边
                    }
                    break;                        // 首个不同位后：本对无更多信息
                }
                if(k == min(a.size(), b.size())) {
                    if(a.size() > b.size()) {   // 前长后短：违反字典序
                        return "";
                    }
                }
            }
        }
        string ans="";
        queue<int> q;
        for(int i=0; i<26; i++) {
            if(vis[i] == true && inDeg[i] == 0) {   // 只排出出现过的字母
                ans.push_back(i+'a');
                q.push(i);
            }
        }

        while(!q.empty()) {
            auto p=q.front(); q.pop();
            for(auto nxt: next[p]) {
                inDeg[nxt]--;
                if(inDeg[nxt] == 0) {
                    ans.push_back(nxt+'a');    // 清零入队按拓扑序追加
                    q.push(nxt);
                }
            }
        }
        return ans.size() == count(vis.begin(), vis.end(), true) ? ans : "";  // 长度不足=有环
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 字符建模 | 26 字母为节点、首异位为边 | 建模方向完全正确："排序结果 → 字符先序边"是本题唯一的建模允许 | 复盘时用 `["wrt","wrf","er",...]` 官方示例手动推一遍建图（t→f, w→e, r→t, e→r），确认边来源可追溯 |
| 冲突检测 | `cmp` 矩阵预检已判定关系 | 防止重复建边（同字母对多词重复给入度+1 是本题最常见 bug）；冲突立即判非法 | 意识到 cmp 矩阵实际上兼任了"防重边登记表"角色——用 `containsEdge` 检查或 `next[u]` 里查重都可达同效果 |
| 多解处理 | 输出一个合法字典序，同级字母按编号序 | 本题允许多解——同级字母任意顺序都是合法，按编号序自然可行 | 想清"多解时 `queue` 初始顺序决定分支"，不必追求某种"唯一正确"答案 |
| 前缀检查 | `a.size() > b.size()` 在逐字符循环后 | 正确实现"前长后短非法"；K 停在 `min(len)` 后再比较长度 | 该检查**必须在跑完公共前缀后**才有效——提前比较会误判，本写法正确 |
| 建全图 vs 相邻对 | 逐对全对比对 | 相邻对 `(i, i+1)` 已含全部约束信息（全序对由相邻对传递），全对比对冗余但本题规模无害 | 见最优解对照——相邻对版本在建图部分降为 `O(n·L)` |
| 出现字母全集 | `vis` 独立收集自每个单词全部字符 | 保证孤立字母（无任何先序边）也被输出 | 已达标 |

### 相邻对充分性论证（本日核心复盘点）

- 对任意 `i<j`，字典序约束 `words[i] < words[j]` 可由相邻约束链传递：`words[i] < words[i+1] < ... < words[j]`，其中首个不同字符位提供字符级先序边——传递的是"字符大小"，不依赖词间直接比较。
- 例外是非法检测本身：前缀违反必须逐对检查（相邻对只能查出相邻位置的前缀违反；全序中若 `words[i]` 是 `words[j]` 的真前缀但 `i<j`，则必有某相邻对已先违反——鸽笼+传递可证相邻版同样覆盖，见官方题解）。用户的全对版本在检测非法这件事上更直白。

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（cmp 矩阵防重 + 全对建图 + Kahn） | 冲突检查完备；防重严谨；100 词规模最快通过 | 建图 `O(n²L)` 冗余（同信息相邻对就有） | 规模小、要求稳的写法 |
| 相邻对建图 | `O(n·L)` 建图最简；信息无损 | 冲突检测依赖拓扑环判定（本版无单独 cmp 矩阵，冲突以环的形式暴露） | 词数大时的标准解 |
| DFS 后序反转 | 代码更紧凑 | 递归 26 节点无风险但无收益 | 与 Kahn 等价 |

两个版本对"非法"的暴露方式不同值得注意：cmp 矩阵版在**建图时**即可直接判冲突（a<b 与 a>b 同时出现）；相邻对版只能等**环判定**（长度不足）兜底。两者覆盖的非法集相同，但检测时机不同。

## 最优解法

1. 相邻对建图：`words[i]` 与 `words[i+1]` 首异位建边（查重防重复入度）；前缀违反立即返回空串。
2. 全字母 vis 收集；Kahn 排序输出。
3. 长度不足（有环）返回空串。
- 关键不变量：相邻对的字符先序边集合与全对先序边集合**在去重后相同**；Kahn 出序自然给出一个合法多解之一。
- 最优时间复杂度：`O(n·L + C)`，C = 26² 常量级排序
- 最优空间复杂度：`O(C²)`（字符级结构只有常数）

### 最优解代码

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<vector<int>> next(26);    // 字符级邻接
        vector<int> indeg(26, 0);
        vector<bool> seen(26, false);    // 出现过的字母
        for (const string& w : words) {
            for (char c : w) seen[c - 'a'] = true; // 全集收集
        }
        for (size_t i = 0; i + 1 < words.size(); i++) { // 相邻对足矣
            const string& a = words[i];
            const string& b = words[i + 1];
            size_t k = 0;
            while (k < a.size() && k < b.size() && a[k] == b[k]) k++;
            if (k == a.size() && k == b.size()) continue;      // 完全相等：无信息
            if (k == b.size()) return "";                    // b 是 a 真前缀而排在后：非法
            // 首异位建边（查重防多次入度）
            int x = a[k] - 'a', y = b[k] - 'a';
            if (x != y && find(next[x].begin(), next[x].end(), y) == next[x].end()) {
                next[x].push_back(y);
                indeg[y]++;
            }
        }
        queue<int> q;
        string ans;
        for (int i = 0; i < 26; i++) {
            if (seen[i] && indeg[i] == 0) { // 只排出现过的字母
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ans.push_back(static_cast<char>('a' + u));
            for (int v : next[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        // 长度不足 = 字符级环：非法
        return static_cast<int>(ans.size()) == static_cast<int>(count(seen.begin(), seen.end(), true))
                   ? ans : string("");
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 建图范围 | 全对比对 `O(n²L)` | 相邻对 `O(nL)` | 信息无损的降阶——词数大时是真正的分水岭，值得写一次对照版 |
| 冲突检测 | cmp 矩阵建图时直判 | 环判定兜底 | 两种时机都正确；cmp 版报错更早，环版代码更短 |
| 防重 | cmp 矩阵 0/±1 三态 | `find` 查重 | 都正确；三态矩阵多一双倍空间但换来即时冲突检测 |
| 排序主体 | Kahn，`vis && inDeg==0` 入队 | 相同 | 已达标 |
| 环判定 | 长度 vs 全集 | 相同 | 已达标 |

## 本地验证记录

- 源码内置 `main`（本地调试入口，含 5 组样例含前缀非法与环非法）——按仓库约定不删除用户本地验证代码，仅点评文档留档。注意该 `main` 使文件**不能直接提交 LeetCode**（提交时需以插件模板重构文件头），与其它 src 文件的结构不同，留档提示。

## 下一步建议

- 复盘任务（困难题核心）：论证"相邻对建图信息无损"——用 `words[i] < words[i+1] < ... < words[j]` 的传递链说一遍，再看官方示例手推一遍建图。
- 文件结构：若今后把 269 纳入插件模板提交，需移除 `using namespace std;` 与 `main`；当前保持原样，仅留档。

## 后续练习

1. `1462. Course Schedule IV` - 同日题单，闭包查询与字符级建图相互呼应（对象级 vs 字符级拓扑）。
2. `1203. Sort Items by Groups Performed Dependencies` - 双层节点（组间+组内）拓扑的进阶题，作为困难题的延伸方向。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/269.cpp](../src/269.cpp)
- 新函数名：`alienOrderOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域（原 `main` 与用户实现保持不动）
- 保留用户原实现：是（含本地 `main` 调试入口）
- 备注：269 为 Plus 会员锁定题，题面细节按通行信息整理，点评中已标注"未联网校准细节"。
