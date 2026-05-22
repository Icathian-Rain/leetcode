# 算法模板 - 链表哑节点删除与过滤

## 基本信息

- 日期：2026-05-22
- 主题：第 4 周链表
- 目标：用哑节点统一处理头结点可能变化的删除、过滤和去重问题
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-linked-list-dummy-delete.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-linked-list-dummy-delete.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目可能删除头结点，或开头连续多个节点都要删除
- 扫描时需要保留前驱节点来跳过当前节点
- 有序链表去重、按值删除、按条件过滤都可以归到这个骨架

## 核心思路

1. 创建 `dummy` 指向原头结点，让返回头稳定为 `dummy.next`。
2. `previous` 指向已确认保留部分的尾部，`current` 指向正在检查的节点。
3. 删除当前节点时，只改 `previous->next`，`previous` 不推进。
4. 保留当前节点时，`previous` 才推进到 `current`。

## 关键边界

- 空链表和单节点都应自然通过循环
- 删除头结点时不能直接返回旧 `head`
- 删除一段节点时，要先保存跳过后的入口
- LeetCode 题解通常只改连接，不主动 `delete` 输入节点

## 复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`

## 模板代码

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeValue(ListNode* head, int value) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            if (current->val == value) {
                previous->next = current->next; // 删除时 previous 不动，继续检查新后继。
            } else {
                previous = current;
            }
            current = previous->next;
        }

        return dummy.next;
    }

    ListNode* deleteDuplicatesKeepOne(ListNode* head) {
        ListNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }
        return head;
    }
};
```

## 运行样例

### 样例 1

- 输入：`head = [6, 6, 1, 2, 6], value = 6`
- 输出：`[1, 2]`
- 说明：头部连续命中时，`dummy` 保证返回头能稳定更新。

### 样例 2

- 输入：`head = [1, 1, 2, 3, 3]`
- 输出：`[1, 2, 3]`
- 说明：有序链表只需要比较相邻节点，重复时跳过后继。

## 套用提醒

- 一旦头结点可能被删，就优先上哑节点。
- 删除当前节点时前驱不动，保留当前节点时前驱才推进。
- 如果题目要求删除整段重复值，需要在这个模板上增加“先扫描重复段，再决定是否接入”的逻辑。
