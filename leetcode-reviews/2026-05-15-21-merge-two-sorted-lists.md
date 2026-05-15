# 题解点评 - 21. Merge Two Sorted Lists

## 基本信息

- 日期：2026-05-15
- 主题：链表 - 基础连接改写
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/21.merge-two-sorted-lists.cpp`
- 资料来源：第 4 周计划（题号、英文题名和难度已于 2026-05-15 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 创建 `dummy` 哑节点，用 `t` 作为结果链表尾指针。
2. 用 `p`、`q` 分别扫描 `list1` 和 `list2`。
3. 当某一条链表为空时，把另一条链表当前节点接到结果尾部，然后继续推进。
4. 两条链表都非空时，比较当前值，把较小节点接到结果尾部。
5. 返回 `dummy->next`，最后释放哑节点。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`
- 空间复杂度：`O(1)`
- 复杂度来源：每个节点最多被尾指针接入一次，只额外使用常数个指针。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(); // 用哑节点统一处理结果头部。
        ListNode *t = dummy;
        ListNode *p = list1, *q = list2;
        while(p != nullptr || q != nullptr) {
            if(p == nullptr) {
                t->next = q; // list1 用完后，继续接 list2 当前节点。
                q = q->next;
                t = t->next;
            } else if(q == nullptr) {
                t->next = p;
                p = p->next;
                t = t->next;
            } else {
                if(p->val < q->val) {
                    t->next = p;
                    p = p->next;
                    t = t->next;
                } else {
                    t->next = q;
                    q = q->next;
                    t = t->next;
                }
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
| 哑节点 | 使用 `dummy` 简化头部拼接。 | 正确，避免单独判断结果链表是否为空。 | 这会成为链表删除、合并、分区题的高频模板。 |
| 尾指针推进 | 每次接入节点后推进 `t`。 | 结果链表能保持连续。 | 可以把重复的 `t = t->next` 收束到分支外。 |
| 剩余链表处理 | 逐个接入剩余节点。 | 正确但代码稍重复。 | 一条链表为空后，剩余部分可以一次性接上。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确、直观，哑节点使用到位。 | `while (p || q)` 让空链表分支重复出现。 | 可以提交，适合初练。 |
| 推荐最优解 | 只在两条链表都非空时比较，最后一次性接剩余链表。 | 需要确认剩余部分已经有序。 | 更清爽，更容易迁移。 |

## 最优解法

1. 用栈上哑节点保存结果链表头之前的位置。
2. 当两条链表都非空时，选择较小节点接到尾部。
3. 每接一个节点，尾指针向后移动。
4. 循环结束后，一次性接上未遍历完的剩余链表。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // 剩余链表本身有序，直接接到结果尾部。
        tail->next = (list1 != nullptr) ? list1 : list2;
        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `dummy/t/p/q`。 | `dummy/tail/list1/list2`。 | 命名可以直接表达结果尾部和当前输入链表。 |
| 更新逻辑 | 空链表分支里也逐个推进。 | 两边都有节点时比较，最后接剩余。 | 减少重复分支，逻辑更紧。 |
| 边界处理 | 空链表、单边为空都覆盖。 | 同样覆盖。 | 当前边界正确。 |
| 复杂度 | `O(n+m)` / `O(1)` | `O(n+m)` / `O(1)` | 已达到最优。 |

## 下一步建议

建议记住“哑节点 + 尾指针 + 剩余部分一次性接上”这个模板。后面 `86. Partition List`、`148. Sort List` 都会反复用到这种构造结果链表的手感。

## 后续练习

1. `83. Remove Duplicates from Sorted List` - 继续练习有序链表的相邻关系处理。
2. `86. Partition List` - 把一个结果链表扩展成两个分区链表再拼接。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/21.merge-two-sorted-lists.cpp`
- 新函数名：`mergeTwoListsOpt`
- 保留用户原实现：是
