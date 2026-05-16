# 题解点评 - 876. Middle of the Linked List

## 基本信息

- 日期：2026-05-16
- 主题：链表 - 删除、定位与头结点边界
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/876.middle-of-the-linked-list.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/middle-of-the-linked-list/) + [leetcode.ca 镜像页](https://leetcode.ca/all/876.html) + 本地源码
- 查询日期：2026-05-16

## 用户思路概述

1. 用递归从头走到链表末尾，递归参数 `preCnt` 记录当前节点前面有多少个节点。
2. 递归返回时用 `nxtCnt` 表示当前节点后面已经统计出的节点数量。
3. 如果 `preCnt == nxtCnt`，说明当前节点是奇数长度链表的中点。
4. 如果 `preCnt == nxtCnt + 1`，说明当前节点是偶数长度链表的第二个中点。
5. 公开函数调用 `dfs(head, 0)` 并返回递归过程中保存的答案节点。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个节点递归访问一次，递归调用栈深度为链表长度。

## 用户代码注释版

```cpp
class Solution {
public:
    pair<ListNode* ,int> dfs(ListNode* head, int preCnt) {
        if(head == nullptr) return {nullptr, 0};
        auto [ans, nxtCnt] = dfs(head->next, preCnt+1); // 回溯时 nxtCnt 是当前节点右侧长度。
        if((preCnt == nxtCnt) || (preCnt == nxtCnt+1)) {
            return {head, nxtCnt+1}; // 奇数取正中，偶数取第二个中点。
        } else {
            return {ans, nxtCnt+1};  // 当前不是中点，沿用后面找到的答案。
        }
    }

    ListNode* middleNode(ListNode* head) {
        auto [ans, cnt] = dfs(head, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 偶数长度规则 | 用 `preCnt == nxtCnt + 1` 返回第二个中点。 | 规则判断是对的，能过 `[1,2,3,4,5,6]`。 | 继续保持对题目返回要求的敏感度。 |
| 解法复杂度 | 使用递归统计左右长度。 | 正确但额外占用 `O(n)` 调用栈。 | 本题更推荐一次遍历、常数空间的定位方式。 |
| 状态表达 | `preCnt/nxtCnt` 需要回溯理解。 | 代码能跑，但读者要反推计数含义。 | 链表定位题优先使用直接表达位置关系的指针。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 对奇偶中点的数学判断正确。 | 递归状态绕，空间不是最优。 | 适合理解“中点左右长度关系”。 |
| 推荐最优解 | 一趟扫描，常数空间，偶数长度自然停在第二中点。 | 需要准确写出循环条件。 | 最适合链表中点、环检测、分段题的迁移。 |

## 最优解法

1. 用 `slow` 和 `fast` 都从头结点出发。
2. 每轮让 `slow` 走一步，`fast` 走两步。
3. 当 `fast` 走到末尾或越过末尾时，`slow` 正好停在中点。
4. 因为循环条件是 `fast != nullptr && fast->next != nullptr`，偶数长度时 `slow` 会停在第二个中点。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            // fast 每次走两步，slow 每次走一步；偶数长度时 slow 正好停在第二个中点。
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `preCnt/nxtCnt/ans`。 | `slow/fast`。 | 用指针速度差直接表达中点位置。 |
| 更新逻辑 | 先递归到底，再回溯判断。 | 一边遍历一边定位。 | 把“左右长度关系”转成“走速关系”。 |
| 边界处理 | 题目保证非空，单节点可返回自身。 | 同样覆盖单节点和双节点。 | 循环条件必须同时检查 `fast` 和 `fast->next`。 |
| 复杂度 | `O(n)` / `O(n)`。 | `O(n)` / `O(1)`。 | 去掉递归栈。 |

## 下一步建议

建议把本题用 `slow/fast` 默写一遍，再手推长度 `1、2、5、6`。中点题的价值在于把“位置比例”转成“两个指针的推进速度”。

## 后续练习

1. `141. Linked List Cycle` - 继续使用不同速度的指针识别链表关系。
2. `234. Palindrome Linked List` - 需要先定位中点，再处理前后部分比较。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/876.middle-of-the-linked-list.cpp`
- 新函数名：`middleNodeOpt`
- 保留用户原实现：是

