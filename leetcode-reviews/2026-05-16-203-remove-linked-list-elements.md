# 题解点评 - 203. Remove Linked List Elements

## 基本信息

- 日期：2026-05-16
- 主题：链表 - 删除、定位与头结点边界
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/203.remove-linked-list-elements.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/remove-linked-list-elements/) + [leetcode.ca 镜像页](https://leetcode.ca/all/203.html) + 本地源码
- 查询日期：2026-05-16

## 用户思路概述

1. 创建栈上哑节点 `dummy`，让它指向原始 `head`，用于统一处理删除头结点的情况。
2. 用 `pre` 表示当前保留下来的前驱节点，用 `cur` 表示正在检查的节点。
3. 当 `cur->val == val` 时，把 `pre->next` 改到 `cur->next`，再让 `cur` 回到新的 `pre->next`。
4. 当当前节点不需要删除时，同时推进 `pre` 和 `cur`。
5. 最后返回 `dummy.next`，作为可能变化后的新头结点。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点最多被访问一次，只额外维护哑节点和两个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(-1, head); // 哑节点承接“头结点也可能被删”的边界。
        ListNode* pre = &dummy, *cur = head;
        while(cur != nullptr) {
            if(cur->val == val) {
                pre->next = cur->next; // 跳过当前命中的节点。
                delete cur;            // LeetCode 题解通常不需要手动释放输入节点。
                cur = pre->next;       // pre 不动，继续检查接上来的新节点。
            } else {
                pre = pre->next;       // 当前节点保留，前驱向后推进。
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 头结点变化 | 使用 `dummy` 统一处理。 | 能覆盖 `[7,7,7,7]` 这类开头连续命中的情况。 | 链表删除题只要头可能变化，优先想到哑节点。 |
| 前驱维护 | 删除时 `pre` 不动，保留时才推进。 | 逻辑正确，不会漏删连续目标值。 | 这点很关键，建议作为固定口令记住。 |
| 节点释放 | 对被删节点执行 `delete`。 | 本地思维完整，但在线提交通常不要求管理输入节点所有权。 | 训练题里建议只改连接，不手动释放原链表节点。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 哑节点和前驱推进都正确，能覆盖头部连续删除。 | 手动 `delete` 输入节点，且分支里更新方式略紧。 | 可以提交，适合作为删除类题的起点。 |
| 推荐最优解 | 同样 `O(n)` / `O(1)`，只做连接改写，所有权更清晰。 | 仍要小心删除时前驱不能推进。 | 最适合作为 LeetCode 链表删除模板。 |

## 最优解法

1. 创建哑节点并指向 `head`，确保删除头结点时也有稳定前驱。
2. 用 `previous` 指向当前保留链表的尾部，用 `current` 扫描原链表。
3. 每轮先保存 `current->next`，如果当前值命中目标，就让 `previous->next` 跳过当前节点。
4. 如果当前值不命中，才把 `previous` 推进到当前节点。
5. 遍历结束后返回 `dummy.next`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            if (current->val == val) {
                // 删除当前节点时 previous 不动，继续承接后续可能被删除的节点。
                previous->next = nextNode;
            } else {
                previous = current;
            }
            current = nextNode;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pre/cur` 语义正确。 | `previous/current/nextNode` 更明确。 | 变量名稍微展开，复盘时更轻松。 |
| 更新逻辑 | 删除和保留分支都能正确推进。 | 每轮统一保存 `nextNode`。 | 先保存后继，再决定是否跳过当前节点。 |
| 边界处理 | 空链表、删除头、连续删除都覆盖。 | 同样覆盖。 | 当前边界意识很好。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议补测 `[]`、`[7]` 删除 `7`、`[7,7,1]` 删除 `7`、`[1,2,3]` 删除 `4`。这题的重点不是复杂度，而是确认“删除时前驱不动”已经形成肌肉记忆。

## 后续练习

1. `19. Remove Nth Node From End of List` - 继续练习删除头结点和稳定前驱。
2. `82. Remove Duplicates from Sorted List II` - 练习删除整段节点后如何接回后续链表。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/203.remove-linked-list-elements.cpp`
- 新函数名：`removeElementsOpt`
- 保留用户原实现：是

