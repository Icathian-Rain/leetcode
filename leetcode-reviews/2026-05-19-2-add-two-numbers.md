# 题解点评 - 2. Add Two Numbers

## 基本信息

- 日期：2026-05-19
- 主题：链表 - 模拟、分区与位置重组
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/2.add-two-numbers.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/add-two-numbers/) + [leetcode.ca 镜像页](https://leetcode.ca/all/2.html) + 本地源码
- 查询日期：2026-05-19

## 用户思路概述

1. 用 `dummy` 和 `tail` 构造新的结果链表，避免单独处理结果头结点。
2. 先同时遍历 `l1` 和 `l2`，每一位相加后生成一个新节点，并用 `plus` 保存进位。
3. 当其中一条链表结束后，把 `p` 指向还没有遍历完的那一条链表。
4. 继续处理剩余节点，同时带上前面留下的进位。
5. 遍历结束后，如果仍有进位，再追加一个新节点。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`
- 空间复杂度：`O(max(n, m))`
- 复杂度来源：两条链表的每个节点最多访问一次；额外空间主要来自新构造的结果链表。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p=l1, *q=l2;
        ListNode dummy(-1);       // 哑节点稳定承接结果链表头。
        ListNode *tail = &dummy;  // tail 始终指向结果链表尾部。
        int plus=0;               // 保存当前位产生的进位。

        while(p!=nullptr && q!=nullptr) {
            int sum=p->val+q->val+plus;
            tail->next = new ListNode(sum%10);
            plus = sum/10;

            p = p->next;
            q = q->next;
            tail = tail->next;
        }

        if(p == nullptr) {
            p = q; // 复用 p 继续处理更长链表的剩余部分。
        }

        while(p != nullptr) {
            int sum=p->val+plus;
            tail->next = new ListNode(sum%10);
            plus = sum/10;

            p=p->next;
            tail = tail->next;
        }

        if(plus != 0) {
            tail->next = new ListNode(plus); // 处理最高位额外进位。
        }

        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 逐位模拟 | 能正确把节点值、进位和结果节点对应起来。 | 核心题意理解正确。 | 保持“当前位结果 + 下一位进位”的拆分思路。 |
| 长度不同 | 用第二段循环处理剩余链表。 | 能覆盖两条链表长度不等的情况。 | 可以把三段逻辑合并为一个循环，减少分支重复。 |
| 末尾进位 | 最后单独追加 `plus` 节点。 | 能覆盖 `[9] + [9]` 这类边界。 | 最优模板中把 `carry != 0` 放进循环条件，边界更统一。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确性完整，哑节点和尾指针使用稳定。 | 同时遍历和剩余遍历分成两套循环，逻辑略重复。 | 可以提交，适合先建立逐位模拟感觉。 |
| 推荐最优解 | 用一个循环覆盖两条链表、长度差和最终进位。 | 需要习惯把空节点视为当前位的 `0`。 | 适合作为链表数位模拟的固定模板。 |

## 最优解法

1. 用哑节点和尾指针构造结果链表。
2. 循环条件写成 `l1 != nullptr || l2 != nullptr || carry != 0`，统一覆盖两条链表未结束和最后进位。
3. 每轮先从 `carry` 开始累加，再分别读取两条链表当前节点。
4. 当前位写入 `sum % 10`，下一轮进位更新为 `sum / 10`。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(max(n, m))`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            // 每轮只生成当前位节点，carry 保存下一位进位。
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
            carry = sum / 10;
        }

        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `p/q/tail/plus`。 | `l1/l2/tail/carry`。 | 状态本质一致，命名可更贴近题意。 |
| 更新逻辑 | 先处理共同长度，再处理剩余长度。 | 一个循环统一推进。 | 把“空链表当前位当作 0”作为模板。 |
| 边界处理 | 覆盖长度不同和末尾进位。 | 循环条件自然覆盖这些边界。 | 减少末尾补丁式分支。 |
| 复杂度 | `O(n + m)` / `O(max(n, m))`。 | `O(n + m)` / `O(max(n, m))`。 | 已达到最优，主要改进代码表达。 |

## 下一步建议

建议用一个循环重写一遍当前题，把 `carry` 放进循环条件。这样后续遇到链表版模拟、数组版加法或字符串加法时，模板会更短也更不容易漏最高位进位。

## 后续练习

1. `445. Add Two Numbers II` - 练习当数位顺序变化后，如何重新组织模拟过程。
2. `67. Add Binary` - 把同样的进位模型迁移到字符串上。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/2.add-two-numbers.cpp`
- 新函数名：`addTwoNumbersOpt`
- 保留用户原实现：是
