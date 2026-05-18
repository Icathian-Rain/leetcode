# 题解点评 - 24. Swap Nodes in Pairs

## 基本信息

- 日期：2026-05-18
- 主题：链表 - 局部重排
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/24.swap-nodes-in-pairs.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/swap-nodes-in-pairs/) + [leetcode.ca 镜像页](https://leetcode.ca/all/24.html) + 本地源码
- 查询日期：2026-05-18

## 用户思路概述

1. 创建哑节点 `dummy` 指向原链表头，用来统一处理头两个节点被交换后的新头。
2. 用 `pre` 表示当前二元组的前驱节点，用 `cur` 表示二元组的第一个节点。
3. 当 `cur` 和 `cur->next` 都存在时，先保存下一组入口 `nxt = cur->next->next`。
4. 依次把 `pre->next` 指向第二个节点、第二个节点指向第一个节点、第一个节点接回下一组入口。
5. 交换完成后，让 `pre` 移到当前二元组尾部，`cur` 移到下一组入口。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点最多被访问和重接一次，只额外维护常数个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(-1, head); // 哑节点承接交换后可能变化的新头。
        ListNode*pre = &dummy, *cur = head;
        while(cur != nullptr && cur->next != nullptr) {
            ListNode* nxt = cur->next->next; // 保存下一组入口，避免重接后丢链。
            pre->next = cur->next;           // 前驱接到二元组第二个节点。
            pre->next->next = cur;           // 第二个节点反接第一个节点。
            cur->next = nxt;                 // 第一个节点成为当前二元组尾部并接回下一组。
            pre = cur;
            cur = pre->next;
        }
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 前驱节点 | 使用 `pre` 稳定承接每个二元组。 | 能正确处理头结点交换。 | 局部重排题优先找“当前组前驱”。 |
| 后续入口 | 先保存 `nxt` 再重接三个连接。 | 避免丢失下一组链表。 | 继续保持“改连接前保存入口”的习惯。 |
| 尾部收口 | 交换后 `cur->next = nxt`。 | 奇数长度尾节点可以自然保留。 | 手推 `[1,2,3]` 检查最后一个节点不被误改。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 连接顺序正确，哑节点使用到位，复杂度最优。 | `pre->next->next` 这类链式写法读起来稍紧。 | 可以直接提交，适合作为两两交换模板。 |
| 推荐最优解 | 用 `first/second/nextPair` 命名当前组节点，语义更清楚。 | 本质复杂度不变。 | 更适合复盘和迁移到 k 组重排。 |

## 最优解法

1. 用哑节点统一处理头结点变化。
2. 每轮确认当前前驱后至少还有两个节点。
3. 分别保存当前组第一个节点、第二个节点和下一组入口。
4. 按“前驱接第二个、第二个接第一个、第一个接下一组”的顺序重接。
5. 把前驱推进到当前组尾部，进入下一组。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;

        while (previous->next != nullptr && previous->next->next != nullptr) {
            ListNode* first = previous->next;
            ListNode* second = first->next;
            ListNode* nextPair = second->next;

            // previous 始终指向当前二元组前驱，重接后 first 成为下一组前驱。
            previous->next = second;
            second->next = first;
            first->next = nextPair;
            previous = first;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pre/cur/nxt`。 | `previous/first/second/nextPair`。 | 用变量名表达二元组结构。 |
| 更新逻辑 | 三次重接顺序正确。 | 同样三次重接，但节点身份更明确。 | 复盘时画出前驱、两个待换节点和下一组入口。 |
| 边界处理 | 空链表、单节点、奇数长度都覆盖。 | 同样覆盖。 | 当前边界稳定。 |
| 复杂度 | `O(n)` / `O(1)`。 | `O(n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议把这题的四个指针位置画一遍：`previous -> first -> second -> nextPair`。第 6 天的 k 组反转会把这个二元组扩展成更长的小组。

## 后续练习

1. `92. Reverse Linked List II` - 继续练习在指定区间内重接节点。
2. `25. Reverse Nodes in k-Group` - 把两两交换推广到固定长度分组。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/24.swap-nodes-in-pairs.cpp`
- 新函数名：`swapPairsOpt`
- 保留用户原实现：是

