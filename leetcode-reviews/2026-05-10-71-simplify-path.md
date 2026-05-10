# 题解点评 - 71. Simplify Path

## 基本信息

- 日期：2026-05-10
- 主题：栈与队列 - 表达式、路径与嵌套结构
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/71.simplify-path.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 先扫描原始路径，把 `/` 分隔出的非空片段放入 `fullPath`。
2. 再遍历 `fullPath`：遇到 `..` 时回退一层，遇到 `.` 时跳过，其他片段加入最终路径栈 `ansPath`。
3. 最后把 `ansPath` 中保留的目录片段按 `/` 拼回规范路径。
4. 如果最终没有任何目录片段，返回根路径 `/`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：路径字符串扫描一次，目录片段最多保存到 `fullPath` 和 `ansPath` 中。

## 用户代码注释版

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> ansPath;  // 最终仍然有效的目录层级。
        vector<string> fullPath; // 先收集所有非空路径片段。
        string tmp="";

        for(auto ch: path) {
            if(ch == '/') {
                if(tmp != "") {
                    fullPath.push_back(tmp);
                    tmp = "";
                }
            } else {
                tmp.push_back(ch);
            }
        }

        if(tmp != "") fullPath.push_back(tmp);

        for(auto p: fullPath) {
            if(p == "..") {
                if(!ansPath.empty()) {
                    ansPath.pop_back(); // 回到上一级目录。
                }
            } else if(p == ".") {
                continue; // 当前目录，不改变路径。
            } else {
                ansPath.push_back(p); // 普通目录名，包含 "..." 这类合法名称。
            }
        }

        string ans = "";
        for(auto p: ansPath) {
            ans.push_back('/');
            ans+=p;
        }

        return ans == "" ? "/": ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 路径片段状态 | 能把有效目录层级维护在 `ansPath` 中。 | 核心逻辑正确。 | 复盘时说清 `ansPath` 就是当前规范路径的目录栈。 |
| 特殊片段处理 | 正确区分 `..`、`.` 和普通目录名。 | 能处理根目录回退和多余斜杠。 | 特别记住 `"..."` 不是特殊片段，而是普通目录名。 |
| 空间表达 | 先保存 `fullPath`，再二次处理。 | 正确但多了一份中间数组。 | 可在扫描片段结束时直接处理，减少中间状态。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 两阶段结构清楚，容易调试。 | 需要额外保存所有路径片段。 | 适合初次实现，便于验证每段解析结果。 |
| 推荐最优解 | 边扫描边处理片段，只保留最终目录栈。 | 循环边界稍微更细。 | 适合作为更紧凑的提交写法。 |

## 最优解法

1. 用 `parts` 保存当前规范路径中仍然有效的目录片段。
2. 扫描路径，遇到 `/` 或字符串末尾时得到一个完整片段。
3. 片段为 `..` 时尝试弹出上一层；片段为空或 `.` 时忽略；其他片段入栈。
4. 最后把 `parts` 用 `/` 拼接；如果没有片段，返回 `/`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> parts;
        string segment;

        for (int i = 0; i <= (int)path.size(); ++i) {
            if (i == (int)path.size() || path[i] == '/') {
                if (segment == "..") {
                    if (!parts.empty()) {
                        parts.pop_back();
                    }
                } else if (!segment.empty() && segment != ".") {
                    // 普通目录名保留，"..." 也是合法目录名。
                    parts.push_back(segment);
                }
                segment.clear();
            } else {
                segment.push_back(path[i]);
            }
        }

        if (parts.empty()) {
            return "/";
        }

        string ans;
        for (const string& part : parts) {
            ans += "/" + part;
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `fullPath` 保存所有片段，`ansPath` 保存有效路径。 | 只用 `parts` 保存有效路径。 | 减少中间状态，让“路径栈”更突出。 |
| 更新逻辑 | 先切分，再处理特殊片段。 | 每切出一个片段立刻处理。 | 两种都正确，推荐版本更紧。 |
| 边界处理 | 多斜杠、根目录回退、空结果都覆盖。 | 同样覆盖，并统一处理末尾片段。 | 当前边界覆盖很好。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优量级。 |

## 下一步建议

进入下一题即可。复盘时重点把 `.`、`..`、`...` 三者区别讲清楚，这题的坑主要在语义边界。

## 后续练习

1. `388. Longest Absolute File Path` - 继续练路径层级状态。
2. `1249. Minimum Remove to Make Valid Parentheses` - 换成记录待删除位置的栈状态。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/71.simplify-path.cpp`
- 新函数名：`simplifyPathOpt`
- 保留用户原实现：是
