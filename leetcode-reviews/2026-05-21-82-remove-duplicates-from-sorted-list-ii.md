# 题解点评 - 82. Remove Duplicates from Sorted List II

## 基本信息

- 日期：2026-05-21
- 主题：链表 - 综合复盘与设计迁移
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/82.remove-duplicates-from-sorted-list-ii.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/) + [leetcode.ca 镜像页](https://leetcode.ca/all/82.html) + 本地源码
- 查询日期：2026-05-21

## 用户思路概述

1. 用 `dummy` 作为头结点前驱，统一处理开头就是重复段的情况。
2. 用 `pre` 指向当前结果链表尾部，用 `cur` 扫描待处理节点。
3. 当 `cur` 和 `cur->next` 值相等时，记录重复值 `val`。
4. 删除当前重复段中的节点，并让 `pre->next` 跳过整段重复值。
5. 如果当前节点不重复，就同步推进 `pre` 和 `cur`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点最多被扫描一次；额外只使用常数个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-1, head);       // 头结点也可能被删除，用 dummy 稳定返回头。
        ListNode*pre = &dummy, *cur=head;
        while(cur != nullptr && cur->next != nullptr) {
            if(cur->val == cur->next->val) {
                int val = cur->val;
                ListNode* p=cur->next->next;
                delete cur->next;
                delete cur;             // LeetCode 中通常只改连接，不必手动释放输入节点。
                while(p != nullptr && p->val == val) {
                    ListNode* tmp=p->next;
                    delete p;
                    p = tmp;
                }
                pre->next = p;           // pre 不动，直接跳过整段重复值。
                cur = p;
            } else {
                pre = pre->next;         // 当前节点保留，pre 才推进。
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
| 删除整段重复值 | 能识别重复段并把整段跳过。 | 正确区别于第 83 题只保留一个重复值。 | 继续先确认题目要求“保留一个”还是“全部删除”。 |
| 头结点边界 | 使用 `dummy` 处理开头重复段。 | 能覆盖 `[1,1,1,2]` 这类样例。 | 这是删除类链表题的稳定模板。 |
| 手动释放节点 | 代码中对输入节点执行 `delete`。 | 本地可行，但在线题解通常不需要，且容易增加悬空指针风险。 | 推荐只改连接，交给评测环境管理内存。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 逻辑正确，头部重复段和连续重复段都能覆盖。 | 手动 `delete` 输入节点让实现更紧，也不利于复盘指针状态。 | 可以提交，但建议改成只跳过节点的写法。 |
| 推荐最优解 | 不释放输入节点，只通过 `previous` 跳过重复段，结构更稳。 | 需要准确判断当前是否处在重复段。 | 适合作为删除整段重复值的固定模板。 |

## 最优解法

1. 建立 `dummy`，让 `previous` 指向当前结果链表尾部。
2. 用 `current` 扫描链表，遇到相同值时持续推进到重复段末尾。
3. 如果当前值出现过重复，令 `previous->next = current->next` 跳过整段。
4. 如果没有重复，说明当前节点保留，`previous` 向前推进。
5. 最后返回 `dummy.next`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            bool duplicated = false;
            while (current->next != nullptr && current->val == current->next->val) {
                duplicated = true;
                current = current->next;
            }

            if (duplicated) {
                // current 已停在重复段最后一个节点，previous 直接接到重复段之后。
                previous->next = current->next;
            } else {
                previous = previous->next;
            }

            current = current->next;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pre/cur/p/val`。 | `previous/current/duplicated`。 | 用布尔状态表达“是否处在重复段”。 |
| 更新逻辑 | 删除重复节点并跳过整段。 | 只改连接跳过整段。 | LeetCode 链表题优先只改连接。 |
| 边界处理 | 头部重复、尾部重复都能覆盖。 | 同样覆盖，并减少释放内存带来的风险。 | 保留 dummy 模板。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议重写一遍不 `delete` 的版本，把重点放在 `previous` 什么时候推进：当前值保留才推进，当前值重复时不推进，只改 `previous->next`。

## 后续练习

1. `203. Remove Linked List Elements` - 回看删除目标值时前驱是否推进。
2. `83. Remove Duplicates from Sorted List` - 对比“保留一个重复值”和“删除整段重复值”的分支差异。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/82.remove-duplicates-from-sorted-list-ii.cpp`
- 新函数名：`deleteDuplicatesOpt`
- 保留用户原实现：是
