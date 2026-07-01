# 题解点评 - 23. Merge k Sorted Lists

## 基本信息

- 日期：2026-07-01
- 主题：堆与优先队列
- 难度：困难
- 本次结果：通过倾向
- 对应源码：`src/23.merge-k-sorted-lists.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-07-01，信息待官方页面复核

## 用户思路概述

1. 用小根堆保存每条非空链表当前的头节点。
2. 每次弹出堆顶节点，把它接到答案链表尾部。
3. 如果该节点还有下一个节点，就把下一个节点放入堆。
4. 堆为空时，所有链表都已合并完成。

## 用户解法复杂度

- 时间复杂度：`O(N log k)`，其中 `N` 是所有节点总数，`k` 是链表数量。
- 空间复杂度：`O(k)`
- 复杂度来源：每个节点最多入堆和出堆一次，堆中最多同时保存 `k` 个节点。

## 用户代码注释版

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](const ListNode* a, const ListNode* b) -> bool {
            return a->val > b->val; // 小根堆：值更小的节点优先弹出。
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;
        for(auto p: lists) {
            if(p != nullptr) {
                pq.push(p); // 每条链表只放当前头节点。
            }
        }
        ListNode dummy;
        ListNode*p = &dummy;
        while(!pq.empty()) {
            auto q = pq.top(); pq.pop();
            p->next = q; // 把当前全局最小节点接到答案尾部。
            if(q->next != nullptr) {
                pq.push(q->next); // 推进 q 所在链表的下一个节点。
            }
            p = p->next;
        }
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 堆内状态 | 保存 `ListNode*` | 能直接复用原链表节点，不需要新建节点 | 复盘时强调堆里是“来源游标” |
| 推进规则 | 弹出哪个节点，就推进它的 `next` | 正确保持每条链表的有序来源 | 这是多路合并最核心的不变量 |
| 空链表边界 | 初始入堆时跳过 `nullptr` | 覆盖 `[]`、`[[]]` 等情况 | 继续保持入堆前判空 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 标准、稳定、复杂度达标 | 会改动原链表指针关系 | 需要原地合并多个有序链表 |
| 推荐最优解 | 与用户方案一致，命名更突出尾指针和候选语义 | 复杂度同样依赖 `log k` | 面试中最常见的可迁移写法 |

## 最优解法

1. 把每条非空链表的头节点加入小根堆。
2. 维护答案链表尾指针。
3. 每次弹出最小节点并接入答案。
4. 如果弹出节点还有后继节点，把后继节点加入堆。

- 最优时间复杂度：`O(N log k)`
- 最优空间复杂度：`O(k)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> heap(cmp);
        for (ListNode* head : lists) {
            if (head != nullptr) {
                heap.push(head);
            }
        }

        ListNode dummy;
        ListNode* tail = &dummy;
        while (!heap.empty()) {
            ListNode* node = heap.top();
            heap.pop();
            // 当前最小节点接入答案，再推进它所在链表。
            tail->next = node;
            tail = tail->next;
            if (node->next != nullptr) {
                heap.push(node->next);
            }
        }
        return dummy.next;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 节点指针小根堆 | 节点指针小根堆 | 当前正确 |
| 更新逻辑 | 弹出后推进 `next` | 同样逻辑 | 当前稳定 |
| 边界处理 | 跳过空链表 | 同样跳过 | 当前覆盖完整 |
| 复杂度 | `O(N log k)` | `O(N log k)` | 能对比两两合并的复杂度取舍 |

## 下一步建议

进入下一题。把这题作为“多路合并链表版”的代表题，重点记住堆中保存的是每个来源的当前游标。

## 后续练习

1. `373. Find K Pairs with Smallest Sums` - 把来源从链表换成组合坐标。
2. `378. Kth Smallest Element in a Sorted Matrix` - 把来源换成矩阵的每一行。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/23.merge-k-sorted-lists.cpp`
- 新函数名：`mergeKListsOpt`
- 保留用户原实现：是。
