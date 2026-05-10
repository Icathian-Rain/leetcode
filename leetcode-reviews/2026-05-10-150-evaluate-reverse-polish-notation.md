# 题解点评 - 150. Evaluate Reverse Polish Notation

## 基本信息

- 日期：2026-05-10
- 主题：栈与队列 - 表达式、路径与嵌套结构
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/150.evaluate-reverse-polish-notation.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `stack<int>` 保存当前已经解析出来、但还没有被后续操作符消耗的数字。
2. 遇到普通数字时，用 `stoi` 转成整数并入栈。
3. 遇到操作符时，连续弹出两个数字，先弹出的是右操作数，后弹出的是左操作数。
4. 按操作符计算结果，再把结果压回栈中，作为后续表达式的一部分。
5. 所有 token 处理完后，栈顶就是整个逆波兰表达式的值。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个 token 只处理一次；最坏情况下大量数字会先入栈等待操作符处理。

## 用户代码注释版

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st; // 保存等待被操作符使用的数字或中间结果。
        for(auto tok: tokens) {
            if(tok == "+") {
                int num1 = st.top();st.pop(); // 右操作数
                int num2 = st.top();st.pop(); // 左操作数
                st.push(num2+num1);
            } else if(tok == "-") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2-num1); // 减法顺序不能写反。
            } else if(tok == "*") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2*num1);
            } else if(tok == "/") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2/num1); // 除法同样要保持左/右操作数顺序。
            } else {
                int num = stoi(tok.c_str());
                st.push(num);
            }
        }
        int ans=st.top();st.pop();
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 栈状态 | 栈中保存待参与运算的数字和中间结果。 | 建模准确，能自然处理任意表达式深度。 | 复盘时说清“操作符会消耗最近两个值并产生一个新值”。 |
| 操作数顺序 | 减法和除法使用 `num2 op num1`。 | 正确处理非交换运算。 | 把先弹出的变量命名为 `right`，后弹出的命名为 `left`，减少心智负担。 |
| 代码结构 | 四个操作符分支分别写计算过程。 | 正确但重复。 | 可抽出 `applyOperation`，让主循环更像表达式解释器。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 直接、正确，操作数顺序处理到位。 | 四个分支重复弹栈逻辑，变量名不够语义化。 | 适合本题提交和栈入门复盘。 |
| 推荐最优解 | 主循环统一处理操作符，变量名直接表达左右操作数。 | 本质复杂度不变。 | 更适合迁移到表达式求值类题。 |

## 最优解法

1. 用一个栈保存数字和已经计算出的中间结果。
2. 遇到数字就入栈。
3. 遇到操作符时，弹出右操作数和左操作数，计算后把结果压回栈。
4. 处理完所有 token 后，栈顶就是最终结果。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
    int applyOperation(int left, int right, const string& op) {
        if (op == "+") return left + right;
        if (op == "-") return left - right;
        if (op == "*") return left * right;
        return left / right;
    }

public:
    int evalRPN(vector<string>& tokens) {
        vector<int> values;

        for (const string& token : tokens) {
            if (token.size() == 1 && (token == "+" || token == "-" || token == "*" || token == "/")) {
                int right = values.back();
                values.pop_back();
                int left = values.back();
                values.pop_back();
                // 先弹出的是右操作数，减法和除法尤其不能写反。
                values.push_back(applyOperation(left, right, token));
            } else {
                values.push_back(stoi(token));
            }
        }

        return values.back();
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `stack<int>` 保存待运算值。 | `vector<int>` 当作栈保存待运算值。 | 状态本质相同，`vector` 便于统一写法。 |
| 更新逻辑 | 每个操作符分支都弹两次再计算。 | 统一弹出左右操作数，再调用计算函数。 | 抽出重复逻辑，突出表达式语义。 |
| 边界处理 | 依赖题目保证表达式合法。 | 同样依赖合法输入。 | 面试口述时说明 token 有效，因此无需额外防御。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优。 |

## 下一步建议

进入下一题即可。重点保留一个习惯：遇到栈里弹两个值的题，先给变量命名 `right` 和 `left`。

## 后续练习

1. `224. Basic Calculator` - 表达式求值的括号和符号进阶。
2. `227. Basic Calculator II` - 继续练操作符优先级和中间状态维护。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/150.evaluate-reverse-polish-notation.cpp`
- 新函数名：`evalRPNOpt`
- 保留用户原实现：是
