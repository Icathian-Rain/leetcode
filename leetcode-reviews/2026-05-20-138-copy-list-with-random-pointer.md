# 题解点评 - 138. Copy List with Random Pointer

## 基本信息

- 日期：2026-05-20
- 主题：链表 - 复杂引用与分组改写
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/138.copy-list-with-random-pointer.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/copy-list-with-random-pointer/) + [leetcode.ca 镜像页](https://leetcode.ca/all/138.html) + 本地源码
- 查询日期：2026-05-20

## 用户思路概述

1. 第一轮遍历原链表，为每个旧节点创建一个新节点，并用 `unordered_map<Node*, Node*>` 记录旧节点到新节点的映射。
2. 同时用 `dummy` 和 `pre` 把新节点按 `next` 顺序串成一条新链表。
3. 第二轮再次遍历旧链表，通过 `mp[cur->random]` 找到当前新节点应指向的随机新节点。
4. 如果 `cur->random` 是 `nullptr`，由于构造函数已经把新节点的 `random` 初始化为空，所以可以保持不动。
5. 最后返回 `dummy.next` 作为复制链表头。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：两轮线性遍历；哈希表为每个旧节点保存一个对应的新节点。

## 用户代码注释版

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp; // 旧节点 -> 新节点。
        Node dummy(-1);
        Node*pre = &dummy, *cur = head;

        while(cur != nullptr) {
            Node* newNode = new Node(cur->val);
            mp[cur] = newNode;

            pre->next = newNode; // 先复制普通 next 链。
            pre = pre->next;
            cur = cur->next;
        }

        pre = &dummy, cur = head;
        while(cur != nullptr) {
            if(mp.find(cur->random) != mp.end()) {
                // 当前新节点是 pre->next，random 通过旧节点映射到新节点。
                pre->next->random = mp[cur->random];
            }
            pre = pre->next;
            cur = cur->next;
        }
        return dummy.next;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 深拷贝 | 能为每个旧节点创建独立新节点，而不是复用旧节点。 | 题意理解正确。 | 继续保持“节点身份必须分离”的意识。 |
| 随机引用 | 用哈希表把旧 `random` 转成新 `random`。 | 能正确处理任意前向、后向或自指引用。 | 这是本题最直观、最稳的写法。 |
| 空引用处理 | `nullptr` 没有进表，新节点默认 `random = NULL`。 | 正确覆盖空随机指针。 | 可以显式判断 `cur->random != nullptr`，表达更直接。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 两轮遍历清晰，旧新节点映射非常直观。 | 需要 `O(n)` 额外哈希表。 | 面试解释友好，适合先保证正确性。 |
| 推荐最优解 | 把新节点插入旧节点后面，利用相邻关系省掉哈希表。 | 需要三阶段处理，并且最后必须恢复旧链表。 | 适合本周“节点身份和连接关系”训练。 |

## 最优解法

1. 第一轮把每个新节点插到对应旧节点后面，形成 `旧1 -> 新1 -> 旧2 -> 新2` 的交错结构。
2. 第二轮设置新节点的 `random`：如果旧节点的 `random` 不为空，那么新节点的 `random` 就是 `旧 random` 后面的那个新节点。
3. 第三轮把交错链表拆开，同时恢复旧链表并连好新链表。
4. 整个过程中不需要哈希表，但要非常注意拆分时不能丢掉下一组旧节点入口。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`，不计新链表本身。

### 最优解代码

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* current = head;
        while (current != nullptr) {
            Node* copied = new Node(current->val);
            copied->next = current->next;
            current->next = copied;
            current = copied->next;
        }

        current = head;
        while (current != nullptr) {
            if (current->random != nullptr) {
                // 新节点紧跟在旧节点后面，旧 random 的 next 就是对应新 random。
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }

        Node* copiedHead = head->next;
        current = head;
        while (current != nullptr) {
            Node* copied = current->next;
            current->next = copied->next;
            copied->next = (copied->next == nullptr) ? nullptr : copied->next->next;
            current = current->next;
        }

        return copiedHead;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 哈希表记录旧到新映射。 | 旧节点和新节点相邻存放。 | 把映射关系转成链表结构关系。 |
| 更新逻辑 | 先复制 `next`，再通过表补 `random`。 | 先交错插入，再补 `random`，最后拆分。 | 练习多阶段改写时保存下一段入口。 |
| 边界处理 | 空链表自然返回空，空 `random` 保持默认值。 | 显式处理空链表和空 `random`。 | 两种写法都正确。 |
| 复杂度 | `O(n)` / `O(n)`。 | `O(n)` / `O(1)`。 | 进阶目标是减少哈希表空间。 |

## 下一步建议

建议先保留哈希表解法作为稳妥提交模板，再单独重写一遍交错链表写法。重点不是背代码，而是说清三阶段：插入副本、设置随机指针、拆开并恢复。

## 后续练习

1. `133. Clone Graph` - 继续练习“旧对象到新对象”的映射关系。
2. `146. LRU Cache` - 把节点身份和引用维护迁移到设计题。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/138.copy-list-with-random-pointer.cpp`
- 新函数名：`copyRandomListOpt`
- 保留用户原实现：是
