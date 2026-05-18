# 题解点评 - 234. Palindrome Linked List

## 基本信息

- 日期：2026-05-17
- 主题：链表 - 关系识别与前后比较
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/234.palindrome-linked-list.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/palindrome-linked-list/) + [leetcode.ca 镜像页](https://leetcode.ca/all/234.html) + 本地源码
- 查询日期：2026-05-17

## 用户思路概述

1. 用成员指针 `pri` 指向链表头，作为从前往后移动的比较指针。
2. `check(cur)` 递归走到链表末尾，再在回溯阶段从尾到头访问节点。
3. 每次回溯时，先确认后续比较是否已经失败。
4. 如果当前回溯节点 `cur->val` 和前向指针 `pri->val` 不相等，就返回 `false`。
5. 比较成功后让 `pri = pri->next`，继续和更靠前的回溯节点配对。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个节点递归访问一次，递归调用栈深度为链表长度。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode *pri; // 从链表头向后走，用来和递归回溯的尾部节点配对。

    bool check(ListNode* cur) {
        if(cur == nullptr) return true;
        bool flag = check(cur->next); // 先递归到尾部，回溯时 cur 从后往前出现。
        if(flag == false) {
            return false; // 后面已经不匹配，直接向上传播失败。
        }

        if(cur->val != pri->val) return false; // 比较后向节点和前向节点的值。
        pri = pri->next;
        return true;
    }

    bool isPalindrome(ListNode* head) {
        pri = head;
        return check(head);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 前后比较 | 用递归回溯模拟从尾到头的访问。 | 思路正确，能覆盖奇偶长度。 | 这是很好的第一版，但要知道空间不是 follow-up 最优。 |
| 状态含义 | `pri` 作为成员变量承接前向位置。 | 能完成配对，但状态藏在类成员里。 | 面试中要主动说明 `pri` 每次比较后前进一步。 |
| 空间复杂度 | 使用递归栈。 | 正确但为 `O(n)`，没有达到 follow-up 的 `O(1)`。 | 推荐掌握反转后半段的常数空间写法。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 代码短，利用递归天然形成前后配对。 | 调用栈 `O(n)`，成员变量状态不如局部指针直观。 | 适合理解链表无法直接从尾部向前走的问题。 |
| 推荐最优解 | `O(1)` 额外空间，可恢复链表结构。 | 需要组合中点定位、反转和比较三步。 | 最适合本题 follow-up 和后续链表重排题。 |

## 最优解法

1. 先用快慢指针找到前半段尾部。
2. 反转后半段链表，使后半段可以从原尾部向前比较。
3. 用两个指针分别从头结点和反转后的后半段头部开始比较。
4. 比较结束后，把后半段再次反转接回，保持链表结构。
5. 返回比较结果。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
    ListNode* reverseListForPalindrome(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }

public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            // slow 停在前半段尾部，便于反转后半段并在结束后接回。
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* secondHalfHead = reverseListForPalindrome(slow->next);
        ListNode* first = head;
        ListNode* second = secondHalfHead;
        bool matched = true;

        while (matched && second != nullptr) {
            if (first->val != second->val) {
                matched = false;
            }
            first = first->next;
            second = second->next;
        }

        slow->next = reverseListForPalindrome(secondHalfHead);
        return matched;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pri` 前向走，递归 `cur` 后向回溯。 | `slow/fast` 定位，反转后用两个局部指针比较。 | 把隐式调用栈换成显式链表结构调整。 |
| 更新逻辑 | 递归返回时比较并推进 `pri`。 | 反转后半段后线性比较。 | 复盘三阶段边界：找中点、反转、恢复。 |
| 边界处理 | 空链表和单节点都能返回真。 | 同样覆盖，并处理奇偶长度。 | 当前正确性不错。 |
| 复杂度 | `O(n)` / `O(n)`。 | `O(n)` / `O(1)`。 | 去掉递归栈，达到 follow-up。 |

## 下一步建议

建议重写一次常数空间版本，重点手推 `[1,2,1]` 和 `[1,2,2,1]`。这题是后面 `143. Reorder List` 的前置训练：都需要先定位中点，再处理后半段。

## 后续练习

1. `143. Reorder List` - 继续练习中点定位、后半段处理和重新拼接。
2. `92. Reverse Linked List II` - 强化局部反转和接回边界。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/234.palindrome-linked-list.cpp`
- 新函数名：`isPalindromeOpt`
- 保留用户原实现：是

