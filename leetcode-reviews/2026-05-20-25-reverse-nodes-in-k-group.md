# 题解点评 - 25. Reverse Nodes in k-Group

## 基本信息

- 日期：2026-05-20
- 主题：链表 - 复杂引用与分组改写
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/25.reverse-nodes-in-k-group.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/reverse-nodes-in-k-group/) + [leetcode.ca 镜像页](https://leetcode.ca/all/25.html) + 本地源码
- 查询日期：2026-05-20

## 用户思路概述

1. 用 `dummy` 作为稳定头前节点，`pre` 指向当前待处理分组的前一个节点。
2. 每轮从 `pre` 出发向后数 `k` 个节点，若不足 `k` 个，直接返回结果。
3. 保存当前组后面的入口 `nxt = tail->next`。
4. 把当前组临时切成独立链表，再调用 `reverseList(cur, tail)` 反转整组。
5. 将反转后的组接回 `pre` 和 `nxt` 之间，然后推进到下一组。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点只被定位和反转常数次；只额外使用若干指针。

## 用户代码注释版

```cpp
using pll=pair<ListNode*, ListNode*>;
class Solution {
public:
    pll reverseList(ListNode* head, ListNode* tail) {
        ListNode*pre = nullptr;
        ListNode*cur = head;
        while(cur != nullptr) {          // 当前组已被切断，所以反转到 nullptr 停止。
            ListNode* nxt=cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return {tail, head};             // 原尾变新头，原头变新尾。
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(-1, head);
        ListNode*pre = &dummy, *cur=head;
        while(cur != nullptr) {
            ListNode*tail = pre;
            for(int i=0; i<k; i++) {
                tail = tail->next;
                if(tail == nullptr) {
                    return dummy.next;   // 不足一组的尾部保持原样。
                }
            }
            ListNode*nxt = tail->next;   // 保存下一组入口。

            pre->next = nullptr;
            tail->next = nullptr;        // 临时切断当前组，方便复用普通反转。

            tie(cur, tail) = reverseList(cur, tail);

            pre->next = cur;             // 当前组接回前侧。
            tail->next = nxt;            // 当前组接回后侧。

            pre = tail;
            cur = nxt;
        }
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 分组边界 | 每轮先数够 `k` 个节点，不够就返回。 | 正确保留不足一组的尾部。 | 这是本题最重要的正确性条件。 |
| 接回前后 | 保存 `nxt`，反转后接回 `pre` 和 `nxt`。 | 能避免丢失后续节点。 | 继续保持“改连接前保存入口”。 |
| 反转方式 | 先切断当前组，再按普通链表反转。 | 思路清楚，容易验证。 | 进阶可不显式切断，用 `afterGroup` 作为反转终点。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 分组检查、临时切断、反转接回都很清楚。 | `pre->next = nullptr` 不是必须；辅助函数在 `public` 下，边界含义略松。 | 可以提交，属于扎实的困难题解法。 |
| 推荐最优解 | 反转函数直接以组尾和组后入口为边界，不需要先切断前侧。 | 对 `previous = afterGroup` 的含义要理解清楚。 | 更适合作为固定分组反转模板。 |

## 最优解法

1. 用哑节点记录整体结果头，并让 `beforeGroup` 指向当前组前驱。
2. 每轮从 `beforeGroup` 出发尝试找到第 `k` 个节点；找不到就返回。
3. 保存 `afterGroup = tail->next`，作为当前组反转后的尾部出口。
4. 在 `[head, tail]` 范围内反转，反转时让原组头最终指向 `afterGroup`。
5. 把组前驱接到新组头，再把指针推进到下一组。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
    pair<ListNode*, ListNode*> reverseSegment(ListNode* head, ListNode* tail) {
        ListNode* afterTail = tail->next;
        ListNode* previous = afterTail;
        ListNode* current = head;

        while (previous != tail) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return {tail, head};
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* beforeGroup = &dummy;

        while (head != nullptr) {
            ListNode* tail = beforeGroup;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr) {
                    return dummy.next;
                }
            }

            ListNode* afterGroup = tail->next;
            // 只反转 [head, tail]，afterGroup 始终作为下一段入口保留。
            tie(head, tail) = reverseSegment(head, tail);
            beforeGroup->next = head;
            tail->next = afterGroup;

            beforeGroup = tail;
            head = afterGroup;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pre/cur/tail/nxt`。 | `beforeGroup/head/tail/afterGroup`。 | 用名字标出组前、组头、组尾、组后。 |
| 更新逻辑 | 先切断当前组，再普通反转。 | 以 `afterGroup` 为边界直接反转。 | 省掉不必要的前侧断开。 |
| 边界处理 | 不足 `k` 个直接返回，正确。 | 同样保留不足一组尾部。 | 当前已经抓住核心边界。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

这题完成质量不错。建议复盘时只盯四个位置：组前驱、组头、组尾、组后入口。只要这四个点不丢，困难题就会变成若干次稳定的局部反转。

## 后续练习

1. `92. Reverse Linked List II` - 对比固定区间反转和固定分组反转。
2. `24. Swap Nodes in Pairs` - 把 `k = 2` 的局部重排作为简化版复盘。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/25.reverse-nodes-in-k-group.cpp`
- 新函数名：`reverseKGroupOpt`
- 保留用户原实现：是
