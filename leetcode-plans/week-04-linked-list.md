# 第 04 周 - 链表

## 本周目标

建立对“节点身份”和“连接关系”的敏感度。到本周结束时，你应该能在动手前先说清：哪些节点会被保留，哪些连接会被改写，返回的新头在哪里，以及操作过程中是否可能断链、成环或丢失后续节点。

当前进度：已完成第 6 天训练。下一步进入第 7 天“综合复盘与设计迁移”，重点复盘整周的头结点变化、尾部收口、节点身份和多阶段重接。

资料校准：题号、英文题名和难度已通过 LeetCode 题目资料与 leetcode.ca 镜像页校准；第 6 天题目于 2026-05-20 复核。

## 与第 3 周衔接

第 3 周你已经训练了状态进入、离开和结算时机。链表题会继续要求这种状态感，但失误成本更直接：一个连接改错，就可能丢掉整段后续节点，或者让链表进入无限循环。因此本周每道题都要把“当前节点、前驱节点、后继节点、返回头结点”画清楚。

## 前置知识

- `ListNode` 的基本结构和 LeetCode C++ 提交格式
- 空链表、单节点、双节点的边界推演
- 头结点变化时如何稳定返回新头
- 修改连接前先保存后续节点的习惯
- 能用小样例手推每一次 `next` 指向变化

## 每日计划

### 第 1 天 - 基础连接改写

1. `206. Reverse Linked List` (`简单`) - 练习从最小单元开始改写节点连接，并确认返回的新头。
2. `21. Merge Two Sorted Lists` (`简单`) - 练习在两个有序链表之间选择节点并保持结果链表连续。
3. `83. Remove Duplicates from Sorted List` (`简单`) - 练习在有序链表中跳过重复节点，同时保留仍然有效的后续部分。

### 第 2 天 - 删除、定位与头结点边界

1. `203. Remove Linked List Elements` (`简单`) - 练习批量删除目标节点，尤其处理开头连续命中的情况。
2. `876. Middle of the Linked List` (`简单`) - 练习在一次遍历过程中定位链表内部的目标位置。
3. `19. Remove Nth Node From End of List` (`中等`) - 练习从尾部计数定位删除目标，并覆盖删除头结点的边界。

### 第 3 天 - 关系识别与前后比较

1. `141. Linked List Cycle` (`简单`) - 练习判断链表是否存在重复访问关系，并避免无限遍历。
2. `160. Intersection of Two Linked Lists` (`简单`) - 练习识别两条链表是否共享同一段节点，而不是只比较节点值。
3. `234. Palindrome Linked List` (`简单`) - 练习在链表结构上比较前后顺序，并处理奇偶长度差异。

### 第 4 天 - 局部重排

1. `24. Swap Nodes in Pairs` (`中等`) - 练习按固定小组改写相邻节点连接，并保留下一组入口。
2. `92. Reverse Linked List II` (`中等`) - 练习只改变指定区间内的连接，同时接回区间外节点。
3. `143. Reorder List` (`中等`) - 练习把链表拆成多个阶段处理，并保证最终结构不丢节点、不成环。

### 第 5 天 - 模拟、分区与位置重组

1. `2. Add Two Numbers` (`中等`) - 练习在链表上逐位构造新结果，并处理长度不同和末尾进位。
2. `86. Partition List` (`中等`) - 练习按条件重组节点，同时保持各部分内部相对顺序。
3. `328. Odd Even Linked List` (`中等`) - 练习根据位置关系重排链表，并在最后重新拼接两段结构。

### 第 6 天 - 复杂引用与分组改写

1. `138. Copy List with Random Pointer` (`中等`) - 练习复制含额外引用的链表，确保新旧节点关系完全分离。
2. `61. Rotate List` (`中等`) - 练习根据长度和移动次数重定位链表头尾。
3. `25. Reverse Nodes in k-Group` (`困难`) - 练习按固定大小处理多段节点，并保留不足一组的尾部结构。

### 第 7 天 - 综合复盘与设计迁移

1. `82. Remove Duplicates from Sorted List II` (`中等`) - 对比第 1 天去重题，练习删除整段重复值并保留真正唯一的节点。
2. `148. Sort List` (`中等`) - 练习在链表限制下完成全局有序化，并关注复杂度要求。
3. `146. LRU Cache` (`中等`) - 把链表连接维护迁移到设计题中，练习同时满足查询、更新和淘汰要求。

## 本周关注清单

- 每次改 `next` 前，先确认是否已经保存后续入口。
- 任何可能删除头结点的题，都先单独手推空链表、单节点和头部连续命中的样例。
- 不只比较节点值；相交、复制和设计题尤其要关注节点身份。
- 链表重排题完成后，用“节点数量是否一致、尾部是否置空、是否可能成环”做收尾检查。
- 困难题先画一组节点的局部变化，再推广到多组，不急着一次写完整循环。

## 本周节奏建议

- 第 1-2 天：把基本连接改写练稳，不追求快，重点是不丢节点。
- 第 3-4 天：开始处理关系识别和局部重排，所有题都建议画指针图。
- 第 5-6 天：进入多阶段题和复杂引用题，写代码前先列出阶段边界。
- 第 7 天：复盘本周所有“头结点变化”和“尾部收口”的错误点，为下一周二分查找切换思维做准备。

## 进度更新 - 2026-05-15

- 今日完成：`206. Reverse Linked List`、`21. Merge Two Sorted Lists`、`83. Remove Duplicates from Sorted List`
- 当前主题：第 1 天 - 基础连接改写

### 通用解题模板

- 适用条件：题目要求在原链表上改写连接、构造结果链表，或跳过某些相邻节点。
- 核心骨架：先保存后继入口，再改写当前节点连接；如果结果头可能变化，用一个稳定的头前位置承接结果；每轮更新后确认尾指针或当前指针仍指向有效节点。
- 关键边界：空链表、单节点、头结点变化、尾部是否需要置空或接剩余链表；输入节点是否需要释放要看题目环境，LeetCode 题解通常只改连接。
- 复杂度：时间通常为 `O(n)` 或 `O(n + m)`，空间通常为 `O(1)`。

```cpp
class Solution {
public:
    ListNode* relinkTemplate(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next; // 改连接前先保存后续入口。

            if (/* current 需要被跳过或重接 */) {
                previous->next = nextNode;
            } else {
                previous = current;
            }

            current = nextNode;
        }

        return dummy.next;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `206. Reverse Linked List` | 待提交验证，源码逻辑检查通过 | 同时写出迭代和递归版本，迭代版能先保存后继再改 `next`，核心动作正确。 | 公开函数当前调用递归版，建议把迭代版作为默认提交模板，空间更稳。 | [查看](../leetcode-reviews/2026-05-15-206-reverse-linked-list.md) |
| `21. Merge Two Sorted Lists` | 待提交验证，源码逻辑检查通过 | 能用哑节点和尾指针稳定构造结果链表，空链表边界也覆盖。 | 剩余链表可以一次性接上，减少重复分支。 | [查看](../leetcode-reviews/2026-05-15-21-merge-two-sorted-lists.md) |
| `83. Remove Duplicates from Sorted List` | 待提交验证，源码逻辑检查通过 | 能利用有序链表的相邻重复关系跳过节点，也有保存后继的意识。 | 当前依赖哑节点特殊值并手动 `delete` 输入节点；LeetCode 中更推荐只改连接。 | [查看](../leetcode-reviews/2026-05-15-83-remove-duplicates-from-sorted-list.md) |

- 暴露问题：今天的连接改写基础不错，尤其是 206 的 `tmp` 保存后继和 21 的哑节点都很到位。主要需要沉淀两点：第一，LeetCode 链表题通常不要求手动释放输入节点；第二，哑节点不是为了凑代码，而是为“头结点可能变化”提供稳定前驱。
- 下一步安排：进入第 2 天删除、定位与头结点边界。下一组题会继续放大“头部连续删除”“一次遍历定位中间或倒数位置”这些边界，做题前先手推空链表、单节点和删除头结点样例。

## 进度更新 - 2026-05-16

- 今日完成：`203. Remove Linked List Elements`、`876. Middle of the Linked List`、`19. Remove Nth Node From End of List`
- 当前主题：第 2 天 - 删除、定位与头结点边界

### 通用解题模板

- 适用条件：题目要求删除链表中的目标节点，且头结点也可能被删除。
- 核心骨架：用哑节点提供稳定前驱；扫描时先保存后继入口；删除当前节点时前驱不动，保留当前节点时前驱才推进。
- 关键边界：空链表、单节点、头部连续命中、删除尾节点；在线提交通常只改连接，不手动释放输入节点。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode* deleteTemplate(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next; // 改连接前先保存后续入口。
            if (/* current 是要删除的节点 */) {
                previous->next = nextNode;
            } else {
                previous = current;
            }
            current = nextNode;
        }

        return dummy.next;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `203. Remove Linked List Elements` | 待提交验证，源码逻辑检查通过 | 能用哑节点统一处理删除头结点和头部连续命中的情况。 | 删除时手动 `delete` 输入节点；训练中更推荐只改连接。 | [查看](../leetcode-reviews/2026-05-16-203-remove-linked-list-elements.md) |
| `876. Middle of the Linked List` | 待提交验证，源码逻辑检查通过 | 递归计数能正确处理奇偶长度，并返回偶数长度的第二个中点。 | 状态略绕且空间为 `O(n)`；建议迁移到常数空间的一趟定位写法。 | [查看](../leetcode-reviews/2026-05-16-876-middle-of-the-linked-list.md) |
| `19. Remove Nth Node From End of List` | 待提交验证，源码逻辑检查通过 | 用哑节点覆盖删除头结点，递归回溯定位倒数节点正确。 | 递归栈空间为 `O(n)`，还没有落实 follow-up 的一趟常数空间写法。 | [查看](../leetcode-reviews/2026-05-16-19-remove-nth-node-from-end-of-list.md) |

- 暴露问题：今天三题正确性都不错，头结点边界也抓住了。主要需要收束两件事：第一，链表题默认只改连接，不主动 `delete` 输入节点；第二，定位类题尽量优先想“一趟扫描中的相对位置”，减少递归回溯带来的额外空间和解释成本。
- 下一步安排：进入第 3 天关系识别与前后比较。下一组题会继续使用相对移动和节点身份判断，完成后重点复盘“比较的是节点本身还是节点值”，以及是否可能因为遍历策略进入无限循环。

## 进度更新 - 2026-05-17

- 今日完成：`141. Linked List Cycle`、`160. Intersection of Two Linked Lists`、`234. Palindrome Linked List`
- 当前主题：第 3 天 - 关系识别与前后比较

### 通用解题模板

- 适用条件：题目要求识别链表内部关系、同步比较两个位置，或用相对移动抵消长度 / 位置差。
- 核心骨架：先明确比较目标是节点身份还是节点值；再设计两个指针的移动规则，让它们在目标位置相遇、同步比较或同时到达空。
- 关键边界：空链表、单节点、无环 / 无相交、奇偶长度；如果题目要求保持结构，反转或重接后要恢复。
- 复杂度：时间 `O(n)` 或 `O(n + m)`，空间 `O(1)`。

```cpp
class Solution {
public:
    bool relationTemplate(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            // 用两个指针的相对移动，把位置关系转成相遇、同步或分段比较。
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `141. Linked List Cycle` | 待提交验证，源码逻辑检查通过 | 能用一快一慢两个指针判断重复访问关系，空指针检查顺序正确。 | 推荐也掌握同起点版本，方便迁移到中点和后续分段题。 | [查看](../leetcode-reviews/2026-05-17-141-linked-list-cycle.md) |
| `160. Intersection of Two Linked Lists` | 待提交验证，源码逻辑检查通过 | 正确比较节点身份，并用长度差对齐两条链表的剩余路径。 | 可补一版换路指针写法，减少显式计数，让模板更短。 | [查看](../leetcode-reviews/2026-05-17-160-intersection-of-two-linked-lists.md) |
| `234. Palindrome Linked List` | 待提交验证，源码逻辑检查通过 | 递归回溯配合前向指针能正确完成前后值比较。 | 当前空间为 `O(n)`；建议掌握定位中点、反转后半段、比较后恢复的 `O(1)` 写法。 | [查看](../leetcode-reviews/2026-05-17-234-palindrome-linked-list.md) |

- 暴露问题：今天最大的进步是已经开始把链表题看成“节点关系”而不是单纯遍历值。主要需要继续收束两点：第一，明确每题比较的是节点身份还是节点值；第二，递归能帮助理解前后比较，但遇到 follow-up 要能切换到常数空间的指针与反转方案。
- 下一步安排：进入第 4 天局部重排。下一组题会从“识别关系”进入“主动改写关系”，完成后重点检查每段链表是否接回、尾部是否置空，以及是否可能形成环。

## 进度更新 - 2026-05-18

- 今日完成：`24. Swap Nodes in Pairs`、`92. Reverse Linked List II`、`143. Reorder List`
- 当前主题：第 4 天 - 局部重排

### 通用解题模板

- 适用条件：题目要求在链表中处理固定小组、指定区间或多阶段重排，并且只能改节点连接。
- 核心骨架：先锁定当前局部的前驱、头、尾和后继入口；改连接前保存下一段入口；局部处理完成后再接回前后两侧。
- 关键边界：空链表、单节点、不足一组、反转区间从头开始、尾部是否置空；多阶段题先切断旧连接，避免合并后成环。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    ListNode* relinkGroupTemplate(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* beforeGroup = &dummy;

        while (/* 当前局部足够处理 */) {
            ListNode* groupHead = beforeGroup->next;
            ListNode* afterGroup = /* 提前保存下一段入口 */;

            // 在局部内部改写连接；过程中始终保留 beforeGroup 和 afterGroup。

            beforeGroup->next = /* 局部处理后的新头 */;
            groupHead->next = afterGroup;
            beforeGroup = groupHead;
        }

        return dummy.next;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `24. Swap Nodes in Pairs` | 待提交验证，源码逻辑检查通过 | 能用哑节点和当前组前驱稳定交换相邻两节点，并保存下一组入口。 | 链式写法略紧，建议复盘 `previous -> first -> second -> nextPair` 四个位置。 | [查看](../leetcode-reviews/2026-05-18-24-swap-nodes-in-pairs.md) |
| `92. Reverse Linked List II` | 待提交验证，源码逻辑检查通过 | 能保存区间前驱和右侧入口，最终接回反转后的局部链表。 | 当前反转过程会临时跨出区间，建议掌握更清晰的头插法。 | [查看](../leetcode-reviews/2026-05-18-92-reverse-linked-list-ii.md) |
| `143. Reorder List` | 待提交验证，源码逻辑检查通过 | 能拆成找中点、反转后半段、交替合并三阶段，且合并前主动断开两段。 | 辅助函数可私有化；继续强调尾部收口，避免旧连接残留成环。 | [查看](../leetcode-reviews/2026-05-18-143-reorder-list.md) |

- 暴露问题：今天整体完成质量很好，尤其 `143` 已经具备复杂链表题的阶段拆解能力。主要需要继续沉淀两个习惯：第一，局部重排前先命名前驱、局部头尾和后继入口；第二，反转或合并前先判断旧连接是否需要切断，收尾时检查是否可能成环。
- 下一步安排：进入第 5 天模拟、分区与位置重组。下一组题会继续训练“构造新链表或重组原链表”的耐心，完成后重点观察不同长度、条件分区和位置分组下的尾部连接是否稳定。

## 进度更新 - 2026-05-19

- 今日完成：`2. Add Two Numbers`、`86. Partition List`、`328. Odd Even Linked List`
- 当前主题：第 5 天 - 模拟、分区与位置重组

### 通用解题模板

- 适用条件：题目要求构造一条新结果链表，或把原链表按某个规则拆成两段及以上再拼接。
- 核心骨架：用稳定头结点和尾指针承接结果；每次接入节点前先确认是否需要保存后继入口；接入后更新对应尾指针，最后把多段链表按题意拼回。
- 关键边界：空链表、单节点、两段之一为空、长度不同、末尾进位或旧尾部连接残留；重组原节点时尤其要检查尾部是否置空。
- 复杂度：时间 `O(n)` 或 `O(n + m)`，空间通常为 `O(1)`；如果题目要求构造新链表，结果链表本身为必要输出空间。

```cpp
class Solution {
public:
    ListNode* buildOrSplitTemplate(ListNode* head) {
        ListNode firstDummy(0);
        ListNode secondDummy(0);
        ListNode* firstTail = &firstDummy;
        ListNode* secondTail = &secondDummy;

        while (head != nullptr) {
            ListNode* nextNode = head->next; // 改连接前先保存后续入口。
            head->next = nullptr;

            if (/* 当前节点属于第一段 */) {
                firstTail->next = head;
                firstTail = head;
            } else {
                secondTail->next = head;
                secondTail = head;
            }

            head = nextNode;
        }

        firstTail->next = secondDummy.next;
        return firstDummy.next;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `2. Add Two Numbers` | 待提交验证，源码逻辑检查通过 | 能用哑节点和尾指针逐位构造结果链表，长度不同和末尾进位都覆盖。 | 当前把共同长度和剩余长度拆成两套循环，可统一成一个循环减少重复。 | [查看](../leetcode-reviews/2026-05-19-2-add-two-numbers.md) |
| `86. Partition List` | 待提交验证，源码逻辑检查通过 | 两条子链稳定分区，保留了各部分内部相对顺序，尾部置空意识很好。 | 建议接入节点前先保存 `nextNode` 并断开旧连接，让局部结构更稳。 | [查看](../leetcode-reviews/2026-05-19-86-partition-list.md) |
| `328. Odd Even Linked List` | 待提交验证，源码逻辑检查通过 | 正确按位置奇偶分组，而不是按节点值分组，并在最后切断旧尾部连接。 | 可以进一步掌握直接维护奇尾、偶尾的原地写法，减少计数器和哑节点。 | [查看](../leetcode-reviews/2026-05-19-328-odd-even-linked-list.md) |

- 暴露问题：今天三题整体正确性不错，尤其两个重组题都注意到了尾部置空，这是链表拼接题里很关键的收尾动作。下一步要继续强化两个习惯：第一，改连接前先保存后继入口；第二，遇到长度差、分区或位置分组时，优先抽象成“稳定尾指针承接结果”的模板。
- 下一步安排：进入第 6 天复杂引用与分组改写。下一组题会把今天的尾指针、头尾重定位和分段处理继续放大，完成后重点观察新旧节点关系是否分离、移动次数是否归一化，以及不足一组的尾部结构是否保持原样。

## 进度更新 - 2026-05-20

- 今日完成：`138. Copy List with Random Pointer`、`61. Rotate List`、`25. Reverse Nodes in k-Group`
- 当前主题：第 6 天 - 复杂引用与分组改写

### 通用解题模板

- 适用条件：题目要求先定位一段链表或一组关联节点，再临时改写连接、恢复原结构或接回后续部分。
- 核心骨架：先锁定局部的前驱、头、尾和后继入口；所有内部改写都围绕这几个锚点展开；局部完成后立刻接回前后两侧，再推进到下一段。
- 关键边界：空链表、单节点、不足一组、整圈移动、额外引用为空；如果临时形成环或交错结构，最后必须拆开或切断。
- 复杂度：时间 `O(n)`，空间通常为 `O(1)`；如果使用映射保存旧新节点关系，则空间为 `O(n)`。

```cpp
class Solution {
public:
    ListNode* segmentRewriteTemplate(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* beforeSegment = &dummy;

        while (head != nullptr) {
            ListNode* segmentTail = beforeSegment;
            for (int i = 0; i < k; ++i) {
                segmentTail = segmentTail->next;
                if (segmentTail == nullptr) {
                    return dummy.next;
                }
            }

            ListNode* afterSegment = segmentTail->next; // 保存局部后继入口。

            // 在 [head, segmentTail] 内部改写连接，过程中不丢 afterSegment。

            beforeSegment->next = /* 局部处理后的新头 */;
            /* 局部处理后的新尾 */->next = afterSegment;
            beforeSegment = /* 局部处理后的新尾 */;
            head = afterSegment;
        }

        return dummy.next;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `138. Copy List with Random Pointer` | 待提交验证，源码逻辑检查通过 | 旧节点到新节点的映射清晰，能正确处理任意 `random` 引用和空引用。 | 哈希表写法空间为 `O(n)`；进阶可用交错节点把映射关系转成连接关系。 | [查看](../leetcode-reviews/2026-05-20-138-copy-list-with-random-pointer.md) |
| `61. Rotate List` | 待提交验证，源码逻辑检查通过 | 能先统计长度并对 `k` 取模，再通过头尾重接定位新头。 | 建议用更明确的 `newTail/newHead` 命名，减少右移位置换算时的心智负担。 | [查看](../leetcode-reviews/2026-05-20-61-rotate-list.md) |
| `25. Reverse Nodes in k-Group` | 待提交验证，源码逻辑检查通过 | 能先检查一组是否足够，再保存后继入口、反转并接回，不足一组保持原样。 | 当前通过临时切断来复用普通反转，正确但可进一步沉淀“组前、组头、组尾、组后”的固定模板。 | [查看](../leetcode-reviews/2026-05-20-25-reverse-nodes-in-k-group.md) |

- 暴露问题：今天整体完成质量很稳，尤其 `25` 已经抓住困难链表题最关键的“先确认边界，再改连接”。下一步重点收束三件事：第一，额外引用题要明确新旧节点身份是否彻底分离；第二，头尾重定位题要先归一化移动次数；第三，分组题要固定命名组前、组头、组尾和组后入口。
- 下一步安排：进入第 7 天综合复盘与设计迁移。最后一天会把本周的删除、重排、全局整理和设计维护放到一起比较，完成后重点观察你能否在动手前先说清“哪些节点保留、哪些连接改写、返回头在哪里、尾部是否需要收口”。
