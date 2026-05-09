# 题解点评 - 232. Implement Queue using Stacks

## 基本信息

- 日期：2026-05-09
- 主题：栈与队列
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/232.implement-queue-using-stacks.cpp`
- 资料来源：本地周计划已基于 LeetCode GraphQL 元数据校准
- 查询日期：2026-05-08

## 用户思路概述

1. 用输入栈 `a` 接收新元素，用输出栈 `b` 负责按队列顺序弹出旧元素。
2. 当 `b` 为空时，把 `a` 中元素整体倒入 `b`，从而让最早进入队列的元素来到 `b.top()`。
3. `peek()` 通过调用 `pop()` 取出队首，再把该值压回输出栈顶；这个写法不会破坏队列顺序，但查询接口会临时修改再恢复状态，表达上略绕。

## 用户解法复杂度

- 时间复杂度：`push` 为 `O(1)`；`pop` 和 `peek` 摊还 `O(1)`，单次最坏 `O(n)`。
- 空间复杂度：`O(n)`。
- 复杂度来源：每个元素最多从输入栈搬到输出栈一次，两个栈合计保存全部队列元素。

## 用户代码注释版

```cpp
class MyQueue {
    stack<int> a, b; // a 接收新元素，b 保存已翻转后的队首方向
public:
    void push(int x) {
        a.push(x);
    }

    int pop() {
        if (b.empty()) {
            while (!a.empty()) {
                b.push(a.top()); // 只在 b 空时集中翻转，保证摊还复杂度
                a.pop();
            }
        }
        int res = b.top();
        b.pop();
        return res;
    }

    int peek() {
        int res = this->pop(); // 先复用 pop 取出当前队首
        b.push(res);           // 再压回输出栈顶，恢复可观察到的队首
        return res;
    }

    bool empty() {
        return a.empty() && b.empty();
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态不变量 | `pop` 中已经建立 `b.top()` 是队首 | 主体方向正确 | 继续用具体序列验证接口是否保持队列语义。 |
| 查询接口表达 | `peek()` 调用 `pop()` 后再压回 | 结果正确，但读代码时需要额外证明状态被恢复 | 更直接的写法是只搬运、不弹出，直接返回 `b.top()`。 |
| 摊还复杂度 | 只在 `b` 为空时搬运 | 能避免重复倒栈 | 继续坚持该策略，不要每次操作都来回搬。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户原解法 | 两栈分工正确，`peek` 删除再恢复后仍保持队列语义 | 查询接口表达不够直接，容易被误读为破坏状态 | 可以提交；若追求清晰度，可改成直接读取 `b.top()`。 |
| 推荐写法 | 两栈分工清晰，`peek` 不需要临时弹出 | 需要理解单次最坏和摊还的区别 | 适合所有本题合法调用序列，也更便于面试讲解。 |

## 推荐写法

1. 新元素始终压入输入栈。
2. 只有输出栈为空且需要访问队首时，才把输入栈全部倒入输出栈。
3. `pop()` 弹出输出栈栈顶；`peek()` 可以像用户写法一样删除再恢复，也可以只读取输出栈栈顶。推荐后者，因为接口语义更直观。

- 推荐时间复杂度：`push` 为 `O(1)`；`pop`、`peek` 摊还 `O(1)`
- 推荐空间复杂度：`O(n)`

### 推荐代码

```cpp
class MyQueue {
    stack<int> inStack;
    stack<int> outStack;

    void moveIfNeeded() {
        if (!outStack.empty()) {
            return;
        }
        // 只在输出栈为空时翻转一次，保证每个元素最多搬运一次。
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    MyQueue() = default;

    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        moveIfNeeded();
        int value = outStack.top();
        outStack.pop();
        return value;
    }

    int peek() {
        moveIfNeeded();
        return outStack.top();
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `a` 输入，`b` 输出 | `inStack` 输入，`outStack` 输出 | 命名可更直观，便于说明方向。 |
| 更新逻辑 | `pop` 搬运正确，`peek` 复用 `pop` 后恢复 | 抽出“必要时搬运”，查看不删除 | 用户写法正确；推荐写法主要提升可读性。 |
| 边界处理 | 依赖题目保证非空 `pop/peek` | 相同 | 题目允许这样处理。 |
| 复杂度 | 摊还 `O(1)` | 摊还 `O(1)` | 复盘每个元素最多搬运一次。 |

## 下一步建议

当前题可以进入下一题。复盘时建议保留一个交替调用测试，例如 `push(1), push(2), peek(), peek(), pop(), pop()`，用来证明“删除再恢复”的 `peek()` 没有破坏队列语义。

## 后续练习

1. `155. Min Stack` - 练习在每次更新主状态时同步维护辅助状态。
2. `933. Number of Recent Calls` - 继续训练队首过期和先进先出语义。

## 代码同步

- 未改写用户源码；已恢复用户原 `peek()` 写法。
- 原实现正确：是。
- 备注：文档中保留更直观的推荐写法，作为可读性优化参考，不作为正确性修正。
