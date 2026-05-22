# 算法模板 - 链表分组局部改写

## 基本信息

- 日期：2026-05-22
- 主题：第 4 周链表
- 目标：处理固定小组、指定区间或多阶段链表重排时，稳定保存组前、组头、组尾和组后
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-linked-list-segment-rewrite.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-linked-list-segment-rewrite.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目要求每 `k` 个节点反转、两两交换或只反转局部区间
- 修改连接前必须确认当前组是否完整
- 处理完局部后，要把新头和新尾接回链表整体

## 核心思路

1. 用 `beforeGroup` 锁定当前组的前驱。
2. 先向后走 `k` 步找到 `groupTail`，不足一组直接结束。
3. 保存 `afterGroup = groupTail->next`，避免反转时丢失后续入口。
4. 在 `[groupHead, groupTail]` 内部改写连接，再把局部新头尾接回。

## 关键边界

- `k <= 1` 时不需要改写
- 不足一组的尾部必须保持原样
- 反转过程中所有指针都不能越过 `afterGroup`
- 接回后，下一轮的 `beforeGroup` 应该移动到局部处理后的尾部

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
private:
    pair<ListNode*, ListNode*> reverseClosed(ListNode* head, ListNode* afterTail) {
        ListNode* previous = afterTail;
        ListNode* current = head;
        while (current != afterTail) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        return {previous, head}; // previous 是新头，head 变成新尾。
    }

public:
    ListNode* reverseKGroupLike(ListNode* head, int k) {
        if (k <= 1) {
            return head;
        }

        ListNode dummy(0, head);
        ListNode* beforeGroup = &dummy;

        while (true) {
            ListNode* groupTail = beforeGroup;
            for (int i = 0; i < k && groupTail != nullptr; ++i) {
                groupTail = groupTail->next;
            }
            if (groupTail == nullptr) {
                break;
            }

            ListNode* groupHead = beforeGroup->next;
            ListNode* afterGroup = groupTail->next;
            auto [newHead, newTail] = reverseClosed(groupHead, afterGroup);

            beforeGroup->next = newHead;
            beforeGroup = newTail;
        }

        return dummy.next;
    }
};
```

## 运行样例

### 样例 1

- 输入：`head = [1,2,3,4,5], k = 2`
- 输出：`[2,1,4,3,5]`
- 说明：每组 2 个节点反转，不足一组的 `5` 保持原样。

### 样例 2

- 输入：`head = [1,2,3,4,5], k = 3`
- 输出：`[3,2,1,4,5]`
- 说明：第一组三个节点改写后，尾部两个节点不足一组不动。

## 套用提醒

- 链表分组题先命名四个锚点：组前、组头、组尾、组后。
- 改连接前先保存 `afterGroup`，这是避免丢链的保险绳。
- 如果题目是局部区间反转，可以把 `beforeGroup` 定位到 `left` 前一个节点，再复用局部反转。
