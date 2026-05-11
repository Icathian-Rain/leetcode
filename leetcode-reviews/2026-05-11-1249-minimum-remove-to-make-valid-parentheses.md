# 题解点评 - 1249. Minimum Remove to Make Valid Parentheses

## 基本信息

- 日期：2026-05-11
- 主题：栈与队列 - 括号合法性进阶
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/1249.minimum-remove-to-make-valid-parentheses.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用栈 `st` 保存尚未匹配的左括号下标。
2. 用 `idx` 保存最终需要删除的字符下标。
3. 扫描字符串：遇到 `(` 时入栈；遇到 `)` 时，如果栈为空就把当前右括号标记为删除，否则弹出一个左括号完成匹配。
4. 扫描结束后，栈中剩余的左括号都没有被匹配，也加入删除集合。
5. 最后重新扫描字符串，只保留不在删除集合中的字符。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个字符最多入栈、出栈或被检查一次；删除下标集合和结果字符串都可能达到线性规模。

## 用户代码注释版

```cpp
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n=s.length();
        stack<int> st;          // 保存尚未匹配的左括号下标。
        unordered_set<int> idx; // 保存需要删除的下标。
        for(int i=0; i<n; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else if(s[i] == ')') {
                if(st.empty()) {
                    idx.insert(i); // 没有左括号可匹配，这个右括号必须删。
                } else {
                    st.pop(); // 匹配一个最近的左括号。
                }
            }
        }

        while(!st.empty()) {
            idx.insert(st.top()); // 剩下的左括号都无法匹配。
            st.pop();
        }

        string ans="";
        for(int i=0; i<n; i++) {
            if(idx.find(i) == idx.end()) {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 下标状态 | 用栈保存左括号下标，而不是只保存数量。 | 正确，因为题目需要删除具体字符。 | 遇到需要构造结果的题，优先判断是否必须保存位置。 |
| 删除集合 | 右括号当场标记，剩余左括号最后标记。 | 正确覆盖两类非法括号。 | 可以用 `vector<bool>` 替代哈希集合，减少常数开销。 |
| 字符保留 | 非括号字符自然保留。 | 符合题意，不会误删字母。 | 复盘时强调只处理括号，其他字符不改变合法性。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路清晰，删除下标显式，正确性容易证明。 | `unordered_set` 有哈希开销，输出阶段查找略重。 | 适合快速写出稳定解法。 |
| 推荐最优解 | 用布尔数组标记删除，语义一样但常数更低。 | 空间仍为 `O(n)`。 | 适合本题直接提交。 |

## 最优解法

1. 用数组或栈保存尚未匹配的左括号下标。
2. 遇到无法匹配的右括号，直接标记删除。
3. 扫描结束后，剩余左括号下标也标记删除。
4. 构造答案时跳过被标记位置，其余字符原样保留。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> openingIndexes;
        vector<bool> remove(s.size(), false);

        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '(') {
                openingIndexes.push_back(i);
            } else if (s[i] == ')') {
                if (openingIndexes.empty()) {
                    remove[i] = true;
                } else {
                    openingIndexes.pop_back();
                }
            }
        }

        // 剩余未匹配左括号都需要删除。
        for (int index : openingIndexes) {
            remove[index] = true;
        }

        string ans;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (!remove[i]) {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 栈保存未匹配左括号下标，哈希集合保存删除下标。 | 数组保存未匹配左括号下标，布尔数组标记删除。 | 状态语义相同，减少哈希常数。 |
| 更新逻辑 | 右括号非法立即加入集合，剩余左括号最后加入集合。 | 同样处理。 | 当前正确性已经稳定。 |
| 边界处理 | 全非法括号、混合字母和空匹配都覆盖。 | 同样覆盖。 | 已覆盖关键边界。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优量级。 |

## 下一步建议

进入下一题即可。复盘重点是：这题和 `921` 的差别不是括号规则，而是输出目标从“数量”变成了“具体字符串”，因此需要下标。

## 后续练习

1. `32. Longest Valid Parentheses` - 从删除位置迁移到最长合法区间边界。
2. `301. Remove Invalid Parentheses` - 更高阶的最少删除并输出所有结果，适合以后回溯专题。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/1249.minimum-remove-to-make-valid-parentheses.cpp`
- 新函数名：`minRemoveToMakeValidOpt`
- 保留用户原实现：是
