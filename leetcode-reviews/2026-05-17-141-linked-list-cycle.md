# 题解点评 - 141. Linked List Cycle

## 基本信息

- 日期：2026-05-17
- 主题：链表 - 关系识别与前后比较
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/141.linked-list-cycle.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/linked-list-cycle/) + [leetcode.ca 镜像页](https://leetcode.ca/all/141.html) + 本地源码
- 查询日期：2026-05-17

## 用户思路概述

1. 先处理 `head == nullptr`，空链表一定没有环。
2. 用 `slow` 从头结点出发，用 `fast` 从 `head->next` 出发，让两者形成一格距离。
3. 只要 `slow != fast`，就继续推进：`slow` 每次走一步，`fast` 每次走两步。
4. 推进前检查 `fast == nullptr || fast->next == nullptr`，一旦快指针到达链表尾部，说明没有环。
5. 如果循环因为 `slow == fast` 结束，说明两个指针在环内相遇，返回 `true`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：慢指针最多进入环并被快指针追上；额外只维护两个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr) return false;
        ListNode* fast = head->next, *slow = head; // fast 先走一格，避免初始时直接相等。
        while(slow != fast) {
            if(fast == nullptr || fast->next == nullptr) {
                return false; // fast 能走到空，说明链表有尾部，不存在环。
            }
            fast = fast->next->next; // 快指针每轮走两步。
            slow = slow->next;       // 慢指针每轮走一步。
        }
        return true; // 两个指针相遇，说明存在重复访问关系。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 相遇判断 | 能用一快一慢两个指针判断环。 | 核心模式正确，时间和空间都达标。 | 复盘时说清“为什么有环一定会相遇”。 |
| 空指针边界 | 在访问 `fast->next->next` 前检查 `fast` 和 `fast->next`。 | 避免无环链表上的空指针访问。 | 这个检查顺序很稳，继续保持。 |
| 初始化方式 | `fast = head->next`，`slow = head`。 | 正确，但比同起点写法稍绕一点。 | 推荐也掌握同起点版本，更容易迁移到 876 和 234。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确命中快慢指针，边界检查完整。 | 快指针先走一格需要额外解释。 | 可以直接提交，适合本题。 |
| 推荐最优解 | 两指针同起点，循环内推进后判断相遇。 | 需要避免在推进前误判初始相等。 | 更适合作为统一模板迁移到中点、找环入口等题。 |

## 最优解法

1. 令 `slow` 和 `fast` 都从 `head` 出发。
2. 当 `fast` 和 `fast->next` 都存在时，`slow` 走一步，`fast` 走两步。
3. 如果某一轮推进后两者相等，说明存在环。
4. 如果快指针走到空，说明链表有终点，不存在环。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            // fast 每次走两步，slow 每次走一步；有环时二者一定会在环内相遇。
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `fast` 领先 `slow` 一格。 | 两者都从 `head` 出发。 | 统一模板后更容易迁移。 |
| 更新逻辑 | 先判断不相等，再检查空指针并推进。 | 循环条件检查空指针，推进后判断相遇。 | 把“能不能走”放在循环条件里。 |
| 边界处理 | 空链表、单节点无环都覆盖。 | 同样覆盖。 | 当前边界没问题。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议用同起点版本再默写一遍，并手推“单节点自环”和“两节点成环”。这题已经说明你能把链表题从值比较转到节点关系判断。

## 后续练习

1. `142. Linked List Cycle II` - 在判断有环之后继续定位环入口。
2. `876. Middle of the Linked List` - 复用同一套快慢推进节奏。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/141.linked-list-cycle.cpp`
- 新函数名：`hasCycleOpt`
- 保留用户原实现：是

