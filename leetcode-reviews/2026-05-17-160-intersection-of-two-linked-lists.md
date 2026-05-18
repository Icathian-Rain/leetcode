# 题解点评 - 160. Intersection of Two Linked Lists

## 基本信息

- 日期：2026-05-17
- 主题：链表 - 关系识别与前后比较
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/160.intersection-of-two-linked-lists.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/intersection-of-two-linked-lists/) + [leetcode.ca 镜像页](https://leetcode.ca/all/160.html) + 本地源码
- 查询日期：2026-05-17

## 用户思路概述

1. 先分别遍历 `headA` 和 `headB`，统计两条链表长度 `lenA` 和 `lenB`。
2. 重置两个指针 `p`、`q` 回到各自头结点。
3. 让较长链表的指针先走 `abs(lenA - lenB)` 步，使两个指针到尾部的剩余距离相同。
4. 两个指针同步向后走，每轮用 `p == q` 判断是否指向同一个节点。
5. 找到相同节点就返回，否则同时走到空后返回 `nullptr`。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`
- 空间复杂度：`O(1)`
- 复杂度来源：先遍历两条链表求长度，再同步扫描一次，只使用常数个指针和计数器。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB=0;
        ListNode *p = headA, *q = headB;
        while(p!=nullptr) {
            p = p->next;
            lenA++; // 统计 A 的长度。
        }
        while(q!=nullptr) {
            q = q->next;
            lenB++; // 统计 B 的长度。
        }

        p = headA;
        q = headB;
        if(lenA < lenB) {
            for(int i=0; i<(lenB - lenA); i++) {
                q=q->next; // B 更长，先消掉长度差。
            }
        } else {
            for(int i=0; i<(lenA - lenB); i++) {
                p=p->next; // A 更长，先消掉长度差。
            }
        }

        while(p!=nullptr && q!=nullptr) {
            if(p == q) return p; // 必须比较节点身份，不是比较节点值。
            p = p->next;
            q = q->next;
        }
        return nullptr;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 节点身份 | 使用 `p == q` 判断相交。 | 正确抓住题目要找的是同一个节点引用。 | 相交题不要比较 `val`，这一点非常关键。 |
| 长度差对齐 | 先让长链表多走差值。 | 两指针剩余距离一致，后续同步扫描正确。 | 这是稳定且容易讲清的做法。 |
| 结构保持 | 只移动指针，不改写 `next`。 | 满足题目要求的原结构不变。 | 继续保持，160 不需要任何连接修改。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路清晰，节点身份比较正确，复杂度最优。 | 需要两次计数加一次同步扫描，代码略长。 | 面试中完全可用，解释性强。 |
| 推荐最优解 | 不显式统计长度，两个指针换路后自然抵消长度差。 | 初次理解时需要手推 A+B 和 B+A 的路径。 | 更简洁，适合作为相交链表常用模板。 |

## 最优解法

1. 用 `pointerA` 从 `headA` 出发，`pointerB` 从 `headB` 出发。
2. 每轮两个指针都走一步。
3. 如果某个指针走到空，就切换到另一条链表的头结点。
4. 如果两条链表相交，两个指针会在相交节点相遇；如果不相交，最终会同时到达空。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* pointerA = headA;
        ListNode* pointerB = headB;

        while (pointerA != pointerB) {
            // 两个指针分别走完 A+B 和 B+A，长度差会被第二段路径抵消。
            pointerA = (pointerA == nullptr) ? headB : pointerA->next;
            pointerB = (pointerB == nullptr) ? headA : pointerB->next;
        }

        return pointerA;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `lenA/lenB` 加两个同步指针。 | 两个换路指针。 | 从显式长度差迁移到路径等长。 |
| 更新逻辑 | 长链表先走差值，再同步走。 | 走到空后切换到另一条链表。 | 两种都要能解释“剩余路径一样长”。 |
| 边界处理 | 无相交、某条链为空都能返回空。 | 同样覆盖。 | 当前边界正确。 |
| 复杂度 | `O(n+m)` / `O(1)`。 | `O(n+m)` / `O(1)`。 | 已达到最优，主要优化表达。 |

## 下一步建议

建议保留你的长度差写法作为“最容易解释”的版本，同时默写一遍换路版本。复盘重点是：相交链表比较的是节点身份，路径对齐只是为了让两个指针同时抵达同一个候选节点。

## 后续练习

1. `142. Linked List Cycle II` - 同样需要利用相遇关系定位特殊节点。
2. `138. Copy List with Random Pointer` - 继续强化“节点身份”和“节点值”不是一回事。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/160.intersection-of-two-linked-lists.cpp`
- 新函数名：`getIntersectionNodeOpt`
- 保留用户原实现：是

