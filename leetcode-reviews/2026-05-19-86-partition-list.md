# 题解点评 - 86. Partition List

## 基本信息

- 日期：2026-05-19
- 主题：链表 - 模拟、分区与位置重组
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/86.partition-list.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/partition-list/) + [leetcode.ca 镜像页](https://leetcode.ca/all/86.html) + 本地源码
- 查询日期：2026-05-19

## 用户思路概述

1. 建立 `low` 和 `high` 两个哑节点，分别承接小于 `x` 和大于等于 `x` 的节点。
2. 用 `cur` 顺序扫描原链表，保持原始遍历顺序。
3. 遇到 `cur->val < x` 时接到 `low` 链表尾部，否则接到 `high` 链表尾部。
4. 扫描结束后，把小值链表尾部接到大值链表头部。
5. 最后执行 `q->next = nullptr`，切断旧尾部连接。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点只扫描和重接一次；除哑节点和尾指针外没有额外线性存储。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode low, high;          // 两条结果链表的哑节点。
        ListNode*p = &low, *q=&high; // p/q 分别维护两条链表尾部。
        ListNode*cur = head;

        while(cur != nullptr) {
            if(cur->val < x) {
                p->next = cur; // 保持遍历顺序接入小值链表。
                p=p->next;
            } else {
                q->next = cur; // 保持遍历顺序接入大值链表。
                q=q->next;
            }
            cur = cur->next; // 这里依赖原链表的旧 next 继续前进。
        }

        p->next = high.next;
        q->next = nullptr; // 关键收尾：避免高值链表尾部残留旧连接。

        return low.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 稳定分区 | 按原链表顺序追加到两条子链。 | 能满足题目要求的相对顺序不变。 | 这个方向完全正确。 |
| 尾部收口 | 写了 `q->next = nullptr`。 | 避免旧连接残留导致结果错误或成环。 | 链表分段拼接题都要保留这个检查。 |
| 改连接前保存入口 | 当前直接用 `cur = cur->next` 依赖旧连接。 | 本题因为尾部最终切断仍能正确，但结构推演略脆。 | 推荐先保存 `nextNode`，再把当前节点断开并接入目标链表。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路标准，稳定性要求和尾部收口都处理到位。 | 接入节点时没有立即断开旧连接，可读性和局部安全性稍弱。 | 可以提交，适合作为双链分区的基础写法。 |
| 推荐最优解 | 每轮先保存后继并断开当前节点，链表归属更清楚。 | 比用户代码多一行断链动作。 | 适合迁移到更复杂的多段分组和拼接题。 |

## 最优解法

1. 用两条哑节点链表分别保存 `< x` 和 `>= x` 的节点。
2. 遍历原链表时，先保存 `nextNode`。
3. 将当前节点的 `next` 置空，再按条件接到对应链表尾部。
4. 遍历完成后，把小值链表尾部接到大值链表头部。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode beforeDummy(0);
        ListNode afterDummy(0);
        ListNode* beforeTail = &beforeDummy;
        ListNode* afterTail = &afterDummy;

        while (head != nullptr) {
            ListNode* nextNode = head->next;
            head->next = nullptr; // 先断开旧连接，避免分区后尾部残留。

            if (head->val < x) {
                beforeTail->next = head;
                beforeTail = head;
            } else {
                afterTail->next = head;
                afterTail = head;
            }

            head = nextNode;
        }

        beforeTail->next = afterDummy.next;
        return beforeDummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `low/high` 两条子链，`p/q` 维护尾部。 | `before/after` 两条子链，尾指针语义更明确。 | 用名字表达分区含义。 |
| 更新逻辑 | 接入后依赖旧 `next` 前进。 | 先保存后继，再断开当前节点。 | 养成“保存入口，再改连接”的链表习惯。 |
| 边界处理 | 空链表、全小于、全大于都可覆盖，尾部置空正确。 | 每轮断开节点，最终拼接自然收口。 | 当前正确，推荐让局部结构更稳。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议保留当前双链分区框架，再专门练一遍“先存 `nextNode`，当前节点断开，再接入目标链表”。这个动作会直接迁移到后面的分组重排和复杂链表复制。

## 后续练习

1. `328. Odd Even Linked List` - 同样是拆成两段后拼接，但分组条件换成位置。
2. `82. Remove Duplicates from Sorted List II` - 继续练习按条件跳过整段节点并稳定接回。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/86.partition-list.cpp`
- 新函数名：`partitionOpt`
- 保留用户原实现：是
