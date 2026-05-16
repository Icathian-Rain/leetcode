# 题解点评 - 19. Remove Nth Node From End of List

## 基本信息

- 日期：2026-05-16
- 主题：链表 - 删除、定位与头结点边界
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/19.remove-nth-node-from-end-of-list.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/) + [leetcode.ca 镜像页](https://leetcode.ca/2015-12-19-19-Remove-Nth-Node-From-End-of-List/) + 本地源码
- 查询日期：2026-05-16

## 用户思路概述

1. 创建哑节点 `dummy` 指向 `head`，用于处理删除头结点的情况。
2. 用递归走到链表末尾，回溯时统计当前节点距离尾部的序号。
3. `dfs` 参数里传入 `cur` 和它的前驱 `pre`，这样找到目标节点时可以直接改 `pre->next`。
4. 当回溯得到的 `nxtCnt == n` 时，说明当前 `cur` 是倒数第 `n` 个节点。
5. 删除目标节点后返回 `dummy.next`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个节点递归访问一次，递归调用栈深度为链表长度。

## 用户代码注释版

```cpp
class Solution {
public:
    int dfs(ListNode* cur, ListNode* pre, int n) {
        if(cur == nullptr) return 1; // 回溯时从尾部之后的位置开始计数。
        int nxtCnt = dfs(cur->next, cur, n);
        if(nxtCnt == n) {
            pre->next = cur->next; // pre 是目标节点前驱，可直接跳过 cur。
            delete cur;            // LeetCode 题解通常不需要手动释放输入节点。
        }
        return nxtCnt+1;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(-1, head); // 删除头结点时，dummy 是稳定前驱。
        dfs(head, &dummy, n);
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 删除头结点 | 用 `dummy` 作为头结点前驱。 | 可以覆盖 `[1], n = 1` 和删除原头的情况。 | 这点非常稳，链表删除题继续保持。 |
| 倒数定位 | 用递归回溯计数找到目标。 | 正确，但不是题目 follow-up 中的一趟常数空间写法。 | 用固定间隔的两个指针替代递归栈。 |
| 节点释放 | 找到目标后 `delete cur`。 | 本地所有权意识完整，但在线题解通常只改连接。 | 推荐不释放输入节点，避免和平台内存管理预期混在一起。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 递归回溯定位倒数节点，删除头边界处理正确。 | 空间 `O(n)`，且 `pre` 随递归传递可读性一般。 | 能过当前约束，但迁移到长链表不够稳。 |
| 推荐最优解 | 一趟遍历、常数空间，直接定位待删节点前驱。 | 需要把 `fast` 先走 `n` 步的间隔维持清楚。 | 最适合本题和面试现场讲解。 |

## 最优解法

1. 创建哑节点 `dummy`，让 `fast` 和 `slow` 都从 `dummy` 出发。
2. 先让 `fast` 向前走 `n` 步。
3. 然后让 `fast` 和 `slow` 同步向前走，直到 `fast->next` 到达空。
4. 此时 `slow` 正好停在待删除节点的前驱位置。
5. 改写 `slow->next` 跳过目标节点，返回 `dummy.next`。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }

        while (fast->next != nullptr) {
            // fast 与 slow 保持 n 个节点的间隔，slow 最终停在待删节点前驱。
            fast = fast->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;
        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cur/pre/nxtCnt` 通过递归回溯表达倒数位置。 | `fast/slow` 通过固定间隔表达倒数位置。 | 把“尾部回数”转成“前面先走 n 步”。 |
| 更新逻辑 | 递归到底后回溯删除。 | 一趟同步推进后删除。 | 面试中优先写常数空间版本。 |
| 边界处理 | `dummy` 覆盖删除头结点。 | `dummy` 同样覆盖删除头结点。 | 当前最重要边界已经抓住。 |
| 复杂度 | `O(n)` / `O(n)`。 | `O(n)` / `O(1)`。 | 去掉递归栈。 |

## 下一步建议

建议重写一遍双指针版本，并重点手推 `n == 链表长度` 和 `n == 1` 两种边界。这个题的核心迁移点是：需要删除倒数位置时，先定位“待删节点的前驱”，而不是只定位目标节点本身。

## 后续练习

1. `141. Linked List Cycle` - 继续练习两个指针之间的相对运动。
2. `24. Swap Nodes in Pairs` - 继续练习用稳定前驱改写局部连接。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/19.remove-nth-node-from-end-of-list.cpp`
- 新函数名：`removeNthFromEndOpt`
- 保留用户原实现：是

