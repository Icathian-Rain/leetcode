# 题解点评 - 83. Remove Duplicates from Sorted List

## 基本信息

- 日期：2026-05-15
- 主题：链表 - 基础连接改写
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/83.remove-duplicates-from-sorted-list.cpp`
- 资料来源：第 4 周计划（题号、英文题名和难度已于 2026-05-15 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 创建值为 `-101` 的哑节点，并让它指向原链表头。
2. 用 `pre` 表示当前保留下来的前一个节点，`cur` 表示正在检查的节点。
3. 如果 `cur->val == pre->val`，说明当前节点重复，把 `pre->next` 改到 `cur->next`。
4. 如果不重复，就同步推进 `pre` 和 `cur`。
5. 返回 `dummy->next`，并释放哑节点。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点被扫描一次，只额外维护常数个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dummy = new ListNode(-101, head); // 依赖题目值域，让哑节点值不等于合法节点值。
        ListNode *cur = head, *pre = dummy;
        while(cur != nullptr) {
            ListNode* nxt = cur->next; // 保存后继，方便删除当前节点后继续遍历。
            if(cur->val == pre->val) {
                pre->next = nxt; // 跳过当前重复节点。
                delete cur;      // LeetCode 通常不要求手动释放输入节点，真实工程中要看所有权。

                cur = nxt;
            } else {
                pre = cur;
                cur = nxt;
            }
        }
        ListNode *res = dummy->next;
        delete dummy;
        return res;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 有序相邻性 | 通过 `pre` 和 `cur` 比较相邻保留值。 | 正确利用了排序条件。 | 这题只需要看当前节点和下一个节点即可。 |
| 哑节点值 | 使用 `-101` 避免和合法值冲突。 | 依赖题目约束，能过但可迁移性弱。 | 如果不需要删除头结点，直接从 `head` 扫描更自然。 |
| 节点释放 | 对重复节点执行 `delete`。 | 本题通常可过，但 LeetCode 输入节点所有权不需要你管理。 | 训练题里推荐只改连接，不手动释放原链表节点。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确跳过重复节点，保存后继意识很好。 | 依赖哑节点特殊值，并手动释放输入节点。 | 能提交，但不是最简模板。 |
| 推荐最优解 | 直接比较 `current` 和 `current->next`，状态更少。 | 需要理解重复节点一定相邻。 | 最适合本题和有序链表去重模板。 |

## 最优解法

1. 用 `current` 从头扫描链表。
2. 只要 `current` 和 `current->next` 都存在，就比较两者的值。
3. 如果值相同，跳过 `current->next`。
4. 如果值不同，`current` 向后推进。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                // 有序链表中重复节点相邻，跳过后一个重复节点即可。
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }

        return head;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `dummy/pre/cur/nxt`。 | `current`。 | 本题不删除整段头部，状态可以更少。 |
| 更新逻辑 | 当前值和前一个保留值比较。 | 当前值和后一个值比较。 | 利用有序相邻性，写法更直接。 |
| 边界处理 | 空链表能返回空。 | 同样覆盖空链表和单节点。 | 当前边界没问题。 |
| 复杂度 | `O(n)` / `O(1)` | `O(n)` / `O(1)` | 已达到最优。 |

## 下一步建议

建议把这题和第 7 天的 `82. Remove Duplicates from Sorted List II` 放在一起复盘：83 是“重复值保留一个”，82 是“重复值整段删除”，两者对前驱节点的需求不同。

## 后续练习

1. `203. Remove Linked List Elements` - 练习真正需要处理头部连续删除的场景。
2. `82. Remove Duplicates from Sorted List II` - 练习删除整段重复值。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/83.remove-duplicates-from-sorted-list.cpp`
- 新函数名：`deleteDuplicatesOpt`
- 保留用户原实现：是
