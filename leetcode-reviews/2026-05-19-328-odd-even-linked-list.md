# 题解点评 - 328. Odd Even Linked List

## 基本信息

- 日期：2026-05-19
- 主题：链表 - 模拟、分区与位置重组
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/328.odd-even-linked-list.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/odd-even-linked-list/) + [leetcode.ca 镜像页](https://leetcode.ca/all/328.html) + 本地源码
- 查询日期：2026-05-19

## 用户思路概述

1. 建立 `odd` 和 `even` 两条哑节点链表。
2. 用 `idx` 记录当前节点是第几个位置，注意这里的奇偶指的是位置，不是节点值。
3. 顺序扫描原链表，奇数位置接到 `odd` 尾部，偶数位置接到 `even` 尾部。
4. 扫描结束后，把奇数位置链表尾部接到偶数位置链表头部。
5. 最后执行 `q->next = nullptr`，切断偶数链表尾部可能保留的旧连接。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点只访问和重接一次；额外只使用哑节点、尾指针和计数器。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd, even;          // 两条子链：奇数位置、偶数位置。
        ListNode*p = &odd, *q=&even; // p/q 分别维护两条子链尾部。
        ListNode*cur = head;
        int idx = 1;                 // 题目按 1-based 位置判断奇偶。

        while(cur != nullptr) {
            if(idx %2 == 1) {
                p->next = cur;
                p=p->next;
            } else {
                q->next = cur;
                q=q->next;
            }
            cur = cur->next; // 依赖原链表旧 next 继续前进。
            idx++;
        }

        p->next = even.next;
        q->next = nullptr; // 关键收尾：避免偶数尾部继续指向旧节点。

        return odd.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 题意区分 | 用 `idx` 判断位置奇偶。 | 正确避开了“节点值奇偶”的常见误解。 | 继续先确认题目说的是值、位置还是节点身份。 |
| 稳定重组 | 顺序追加到奇偶两条子链。 | 能保持两组内部相对顺序。 | 这是本题正确性的核心。 |
| 原地常数空间 | 只用了常数个指针和哑节点。 | 满足题目复杂度要求。 | 进一步可用原链表的奇偶尾指针直接改写，省掉计数器。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路直观，分组稳定，尾部置空正确。 | 需要额外计数器，且每轮依赖旧连接继续前进。 | 可以提交，适合先理解“按位置分两段”。 |
| 推荐最优解 | 用奇尾和偶尾交替推进，不需要显式计数。 | 指针改写顺序要更小心。 | 适合作为本题和类似位置重排题的标准模板。 |

## 最优解法

1. 若链表为空或只有一个节点，直接返回。
2. 令 `oddTail` 指向第一个节点，`evenHead` 和 `evenTail` 指向第二个节点。
3. 每轮把下一个奇数位置节点接到 `oddTail` 后面，再把下一个偶数位置节点接到 `evenTail` 后面。
4. 循环结束后，将奇数链表尾部接到偶数链表头部。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* oddTail = head;
        ListNode* evenHead = head->next;
        ListNode* evenTail = evenHead;

        while (evenTail != nullptr && evenTail->next != nullptr) {
            // oddTail 维护奇数位置尾部，evenTail 维护偶数位置尾部。
            oddTail->next = evenTail->next;
            oddTail = oddTail->next;
            evenTail->next = oddTail->next;
            evenTail = evenTail->next;
        }

        oddTail->next = evenHead;
        return head;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 两条哑节点链表 + `idx`。 | 原链表上的奇尾、偶头、偶尾。 | 用指针位置本身表达分组状态。 |
| 更新逻辑 | 顺序扫描并按计数器追加。 | 一次循环同时推进奇链和偶链。 | 练习按连接关系推进，而不是只靠计数。 |
| 边界处理 | 空链表也能自然返回，尾部置空正确。 | 显式处理空链表和单节点。 | 显式边界更利于复盘。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优，主要改进模板迁移性。 |

## 下一步建议

建议把这题和 `86. Partition List` 放在一起复盘：两题都可以写成“两条子链收集后拼接”，但本题还有一种更紧凑的原地奇偶尾指针写法。先保证尾部收口，再追求更短模板。

## 后续练习

1. `86. Partition List` - 对比按条件分组和按位置分组的共同结构。
2. `143. Reorder List` - 继续练习多阶段拆分和重新拼接。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/328.odd-even-linked-list.cpp`
- 新函数名：`oddEvenListOpt`
- 保留用户原实现：是
