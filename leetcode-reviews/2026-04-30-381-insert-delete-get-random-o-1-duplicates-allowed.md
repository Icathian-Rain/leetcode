# 题解点评 - 381. Insert Delete GetRandom O(1) - Duplicates allowed

## 基本信息

- 日期：2026-04-30
- 主题：数组与哈希 - 哈希组合与设计
- 难度：困难
- 本次结果：通过（用户反馈已完成）
- 对应源码：`src/381.insert-delete-get-random-o-1-duplicates-allowed.cpp`
- 资料来源：LeetCode 官方题页（题号与题名）+ LeetCode Wiki / LeetCode.ca（约束与题意）
- 查询日期：2026-04-30

## 用户思路概述

你沿用了 `380` 的数组随机访问思路，但把哈希表从 `val -> index` 改成了 `val -> unordered_set<int>`，用来记录某个值在数组中的所有位置。插入时把新元素追加到数组尾，并把尾下标加入对应集合；删除时任选一个待删除下标，用数组最后一个元素覆盖它，并同步更新最后一个元素的下标集合。

这是允许重复元素后最自然、也最常见的升级方案。

## 主要问题

- 整体实现没有阻塞级问题，重复元素、删除尾元素、删除非尾元素这几类关键路径都覆盖到了。
- `remove` 中 `mp[val].erase(idx)` 发生在移动尾元素之前，这一点是对的；但这段逻辑最容易出错，建议复盘时专门记住两种情况：`val == lastVal` 和 `idx == lastIdx`。你的代码在这两种情况下仍然成立。
- `unordered_set<int>` 的平均复杂度是 `O(1)`，但常数会比无重复版本更高；这是本题为了支持重复值必须付出的空间和维护成本。
- 和 `380` 一样，`rand() % arr.size()` 对 LeetCode 可接受，但不是工程级随机。

## 做得好的地方

- 正确识别出重复值不能再用单一下标，必须维护“值到一组下标”的映射。
- 删除流程的顺序处理得比较稳：先拿一个待删下标，再拿尾值，最后更新尾值的下标集合。
- 你没有尝试在 `vector` 中间删除元素，而是继续使用尾元素补洞，所以保住了平均 `O(1)`。

## 最优解法

推荐最优解是 `vector<int> values + unordered_map<int, unordered_set<int>> indices`。关键不变量是：对任意值 `x`，`indices[x]` 中的每个下标 `i` 都满足 `values[i] == x`。删除一个值时，任选它的一个下标 `removeIndex`，用尾元素 `lastValue` 覆盖该位置，再把 `lastValue` 的下标集合从 `lastIndex` 改到 `removeIndex`。

- 时间复杂度：`insert/remove/getRandom` 平均 `O(1)`
- 空间复杂度：`O(n)`

## 最优解代码

```cpp
class RandomizedCollection {
public:
    RandomizedCollection() = default;

    bool insert(int val) {
        bool isNewValue = !indices.count(val);
        indices[val].insert(values.size());
        values.push_back(val);
        return isNewValue;
    }

    bool remove(int val) {
        auto it = indices.find(val);
        if (it == indices.end()) {
            return false;
        }

        int removeIndex = *it->second.begin();
        int lastIndex = values.size() - 1;
        int lastValue = values.back();

        it->second.erase(removeIndex);

        if (removeIndex != lastIndex) {
            values[removeIndex] = lastValue;
            indices[lastValue].erase(lastIndex);
            indices[lastValue].insert(removeIndex);
        }

        values.pop_back();

        if (it->second.empty()) {
            indices.erase(it);
        }

        return true;
    }

    int getRandom() {
        return values[rand() % values.size()];
    }

private:
    vector<int> values;
    unordered_map<int, unordered_set<int>> indices;
};
```

## 对比与改进方向

你的实现和推荐最优解几乎一致。最值得保留的经验是：当一个值可能对应多个位置时，不要试图在数组里查找它，而是把“所有位置”也作为状态显式维护；每次数组位置变化，都同步修正对应集合。

## 下一步建议

可以进入第 7 天。建议在复盘里手推一组边界操作：`insert(1), insert(1), remove(1), remove(1)`，再手推 `insert(1), insert(2), remove(1)`，确认每一步 `values` 和 `indices` 的同步关系。

## 后续练习

1. `710. Random Pick with Blacklist` - 继续训练随机访问与哈希映射结合。
2. `146. LRU Cache` - 用哈希表 + 双向链表维护设计题不变量，适合作为结构设计迁移练习。

## 来源链接

- https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
- https://leetcode.doocs.org/en/lc/381/
- https://leetcode.ca/all/381.html
