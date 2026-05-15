# 题解点评 - 206. Reverse Linked List

## 基本信息

- 日期：2026-05-15
- 主题：链表 - 基础连接改写
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/206.reverse-linked-list.cpp`
- 资料来源：第 4 周计划（题号、英文题名和难度已于 2026-05-15 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 写了迭代版本 `s1`：用 `cur` 扫描当前节点，`pre` 保存已经反转好的前一段。
2. 每轮先用 `tmp` 保存 `cur->next`，再把 `cur->next` 指回 `pre`。
3. 更新 `pre = cur`、`cur = tmp`，直到原链表遍历结束。
4. 写了递归版本 `s2`：递归反转 `head->next` 之后，把后继节点指回当前 `head`。
5. 最终公开函数 `reverseList` 调用递归版本。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：迭代版本 `O(1)`；递归版本 `O(n)`
- 复杂度来源：每个节点只处理一次；递归版本额外占用调用栈。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* s1(ListNode* head) {
        ListNode *cur = head, *pre = nullptr; // pre 是已经反转好的新链表头。
        while(cur != nullptr) {
            ListNode *tmp = cur->next; // 先保存后续入口，否则改 next 后会丢链。
            cur->next = pre;

            pre = cur;
            cur = tmp;
        }
        return pre;
    }

    ListNode* s2(ListNode* head) {
        if(head == nullptr) return nullptr;
        if(head->next == nullptr) return head;

        ListNode *nxt = s2(head->next); // nxt 是反转后整条链表的新头。
        head->next->next = head;        // 让原后继指回当前节点。
        head->next = nullptr;           // 当前节点变成局部尾部，必须断开旧指向。
        return nxt;
    }

    ListNode* reverseList(ListNode* head) {
        return s2(head);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 保存后继 | 迭代版先保存 `tmp` 再改 `next`。 | 正确避免断链。 | 这是链表改指针的第一习惯，继续保持。 |
| 返回新头 | 迭代返回 `pre`，递归返回最深处节点。 | 两种写法都正确。 | 复盘时分别说清新头来自哪里。 |
| 空间复杂度 | 当前公开提交使用递归。 | 正确但调用栈为 `O(n)`。 | 面试里优先掌握迭代版，空间更稳。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户递归解法 | 逻辑优雅，边界处理完整。 | 长链表下有调用栈开销。 | 适合理解反转的递归定义。 |
| 推荐最优解 | 原地迭代，空间 `O(1)`，最容易控风险。 | 需要手动维护三个指针。 | 适合提交和面试现场讲解。 |

## 最优解法

1. 用 `previous` 表示已经反转好的前一段链表。
2. 用 `current` 扫描原链表。
3. 每次先保存 `current->next`，再把 `current->next` 指向 `previous`。
4. 两个指针同步向前推进，最终 `previous` 就是新头。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            // 先保存后续入口，再改写 current->next，避免丢失剩余链表。
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 迭代版 `pre/cur/tmp`，递归版依赖调用栈。 | `previous/current/nextNode`。 | 变量名可以更贴近语义，方便复盘。 |
| 更新逻辑 | 两种反转都正确。 | 只保留迭代原地反转。 | 提交时优先选择空间 `O(1)` 的版本。 |
| 边界处理 | 空链表、单节点都覆盖。 | 同样覆盖。 | 当前边界意识不错。 |
| 复杂度 | 公开版本空间 `O(n)`。 | `O(1)` 额外空间。 | 掌握递归后，把迭代作为默认模板。 |

## 下一步建议

建议用迭代版再默写一遍，并口头说出每轮 `previous/current/nextNode` 分别指向哪里。第一天后续题都会用到这个“改指针前先保存后继”的动作。

## 后续练习

1. `21. Merge Two Sorted Lists` - 练习在构造结果链表时稳定维护尾指针。
2. `92. Reverse Linked List II` - 把整链反转迁移到局部区间反转。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/206.reverse-linked-list.cpp`
- 新函数名：`reverseListOpt`
- 保留用户原实现：是
