# 题解点评 - 92. Reverse Linked List II

## 基本信息

- 日期：2026-05-18
- 主题：链表 - 局部重排
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/92.reverse-linked-list-ii.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/reverse-linked-list-ii/) + [leetcode.ca 镜像页](https://leetcode.ca/all/92.html) + 本地源码
- 查询日期：2026-05-18

## 用户思路概述

1. 创建哑节点 `dummy`，用于处理 `left == 1` 时头结点变化的情况。
2. 用 `pre` 和 `cur` 一起向前移动，直到进入需要反转的区间。
3. 用 `leftTail` 保存反转区间前一个节点，后续要靠它把反转后的区间接回前半段。
4. 从 `left` 到 `right` 逐个把当前节点指向 `pre`，完成区间内部反转。
5. 循环结束后，让原区间头结点接到 `cur`，再让 `leftTail->next` 指向反转后的新头。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：只扫描到 `right` 位置并原地改写连接，额外维护常数个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(-1, head);

        ListNode*pre = &dummy, *cur = head;
        ListNode*leftTail = pre; // 反转区间前驱，最后负责接回新区间头。
        for(int i=1; i<=right; i++) {
            if(i < left) {
                pre = pre->next;
                cur = cur->next;
                leftTail = leftTail->next;
            } else {
                ListNode* nxt = cur->next; // 保存后继入口。
                cur->next = pre;           // 当前节点反指向前一个节点，形成局部反转。
                pre = cur;
                cur = nxt;
            }
        }
        leftTail->next->next=cur; // 原区间头变尾，接回右侧剩余链表。
        leftTail->next = pre;     // 区间前驱接到反转后的新区间头。
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 区间前驱 | 用 `leftTail` 保存 `left` 前一个节点。 | 能处理反转后接回前半段。 | 这个位置是局部反转题的锚点。 |
| 后继保存 | 每次反转前保存 `nxt`。 | 不会丢掉右侧未处理链表。 | 继续保持。 |
| 局部不变量 | 反转时会临时让区间头指回区间外节点。 | 最终能修正，但中间状态不够干净，解释成本高。 | 推荐头插法，让区间尾始终接住剩余部分。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 最终连接正确，时间和空间都达标。 | 反转过程临时跨出区间，`left == 1` 时还会短暂指向哑节点。 | 可提交，但复盘时不如头插法清晰。 |
| 推荐最优解 | 区间前驱和区间尾保持稳定，每轮把尾部后一个节点搬到区间头。 | 初次写时要小心四次赋值顺序。 | 最适合本题和局部重排迁移。 |

## 最优解法

1. 用哑节点承接可能变化的头结点。
2. 先走到 `left` 前一个节点 `beforeLeft`。
3. 令 `sublistTail = beforeLeft->next`，它会成为反转后区间尾部。
4. 重复 `right - left` 次：把 `sublistTail->next` 这个节点摘出来，插到 `beforeLeft->next` 前面。
5. 返回 `dummy.next`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        ListNode* beforeLeft = &dummy;

        for (int i = 1; i < left; ++i) {
            beforeLeft = beforeLeft->next;
        }

        ListNode* sublistTail = beforeLeft->next;
        for (int i = 0; i < right - left; ++i) {
            // 每轮把 sublistTail 后面的节点搬到区间头部，区间尾部始终由 sublistTail 承接。
            ListNode* moving = sublistTail->next;
            sublistTail->next = moving->next;
            moving->next = beforeLeft->next;
            beforeLeft->next = moving;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pre/cur/leftTail`。 | `beforeLeft/sublistTail/moving`。 | 明确区间前驱和区间尾的职责。 |
| 更新逻辑 | 类似整段反转，最后接回。 | 头插法逐个搬节点。 | 减少临时跨区间反指。 |
| 边界处理 | `left == right`、`left == 1` 能被最终修正。 | 同样覆盖，过程更稳定。 | 建议重点手推 `left == 1`。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议用头插法重写一次，并手推 `[1,2,3,4,5], left=2, right=4`。这题的复盘价值在于：局部反转不是只把区间内部翻过来，还要保证前后两侧都接回。

## 后续练习

1. `206. Reverse Linked List` - 回到整链反转，巩固最小反转单元。
2. `25. Reverse Nodes in k-Group` - 把指定区间反转推广到多段分组反转。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/92.reverse-linked-list-ii.cpp`
- 新函数名：`reverseBetweenOpt`
- 保留用户原实现：是

