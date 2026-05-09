# 题解点评 - 682. Baseball Game

## 基本信息

- 日期：2026-05-08
- 主题：栈与队列 - 基础栈语义与状态回退
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/682.baseball-game.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `stack<int>` 保存当前仍然有效的每轮得分。
2. 普通数字直接转成整数并入栈。
3. 遇到 `C` 时删除上一轮有效得分；遇到 `D` 时把上一轮得分翻倍作为新得分。
4. 遇到 `+` 时取最近两轮有效得分相加，作为新得分入栈。
5. 最后把栈里所有有效得分求和。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个操作最多处理一次；栈中最多保存所有有效得分。

## 用户代码注释版

```cpp
class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st; // 保存所有当前有效的历史得分。
        for(auto op: operations) {
            if(op == "C") {
                if(!st.empty())
                    st.pop(); // 删除最近一轮有效得分。
            } else if(op == "D") {
                if(!st.empty()) {
                    int num=st.top();
                    st.push(num*2); // 新得分为上一轮有效得分的两倍。
                }
            } else if(op == "+") {
                if(st.empty()) {
                    continue;
                }
                int num1 = st.top();
                st.pop(); // 临时弹出最近一轮，用来拿到倒数第二轮。

                if(st.empty()) {
                    st.push(num1);
                    continue;
                }

                int num2 = st.top();
                st.push(num1); // 恢复最近一轮。
                st.push(num1 + num2); // 新得分为最近两轮有效得分之和。
            } else {
                int num=atoi(op.c_str());
                st.push(num);
            }
        }
        int ans=0;
        while(!st.empty()) {
            ans+=st.top();
            st.pop();
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 历史状态 | 用栈保存有效得分，`C` 能撤销最近状态。 | 建模正确，符合题意。 | 复盘时说清“栈中只保留有效记录”。 |
| `+` 操作 | 通过临时弹出拿到最近两项，再恢复。 | 正确但步骤稍绕。 | 用 `vector` 保存历史得分时可直接访问倒数两项。 |
| 求和方式 | 最后统一弹栈求和。 | 正确，时间仍为线性。 | 可边处理边维护 `total`，让答案状态同步更新。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 直接表达撤销最近记录，容易理解。 | `+` 要弹出再恢复；最后还要再遍历求和。 | 适合练基础栈模拟。 |
| 推荐最优解 | 用 `vector` 作为栈，倒数访问更简单，并同步维护总分。 | 仍需要保证题目操作有效，否则要额外防御。 | 适合作为本题直接提交写法。 |

## 最优解法

1. 用 `vector<int>` 保存所有有效得分，把它当作可随机访问的栈。
2. 普通数字入栈并加入总分。
3. `C` 删除最后一项，并从总分中扣除。
4. `D` 和 `+` 根据最后一项或最后两项计算新分数，入栈并加入总分。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> scores;
        int total = 0;

        for (const string& op : operations) {
            if (op == "C") {
                total -= scores.back();
                scores.pop_back();
            } else if (op == "D") {
                scores.push_back(scores.back() * 2);
                total += scores.back();
            } else if (op == "+") {
                // 新分数只依赖最近两轮有效得分。
                int current = scores[(int)scores.size() - 1] + scores[(int)scores.size() - 2];
                scores.push_back(current);
                total += current;
            } else {
                int current = stoi(op);
                scores.push_back(current);
                total += current;
            }
        }

        return total;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `stack<int>` 保存有效得分。 | `vector<int>` 保存有效得分并支持倒数访问。 | 本质一致，`vector` 更适合本题的最近两项读取。 |
| 更新逻辑 | `+` 临时弹出再恢复。 | 直接读取倒数两项。 | 减少状态扰动，降低写错概率。 |
| 边界处理 | 对空栈做了防御。 | 依赖题目保证操作有效。 | LeetCode 提交可简化，通用代码可保留防御。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优。 |

## 下一步建议

进入下一题即可。这里最值得复盘的是：有时 `vector` 可以作为“增强版栈”，在需要看倒数第二项时更自然。

## 后续练习

1. `150. Evaluate Reverse Polish Notation` - 继续练最近状态合并成新状态。
2. `394. Decode String` - 在简单历史记录之上加入嵌套上下文。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/682.baseball-game.cpp`
- 新函数名：`calPointsOpt`
- 保留用户原实现：是
