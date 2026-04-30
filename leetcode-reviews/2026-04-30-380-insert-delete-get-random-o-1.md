# 题解点评 - 380. Insert Delete GetRandom O(1)

## 基本信息

- 日期：2026-04-30
- 主题：数组与哈希 - 哈希组合与设计
- 难度：中等
- 本次结果：通过（用户反馈已完成）
- 对应源码：`src/380.insert-delete-get-random-o-1.cpp`
- 资料来源：LeetCode 官方题页（题号与题名）+ LeetCode Wiki / LeetCode.ca（约束与题意）
- 查询日期：2026-04-30

## 用户思路概述

你用 `vector<int> arr` 保存当前集合中的值，用 `unordered_map<int, int> mp` 记录每个值在数组里的下标。插入时追加到数组尾部并记录下标；删除时把要删的位置和最后一个元素交换，再更新被移动元素的下标，最后弹出数组尾部并删除哈希表记录；随机访问时直接随机取数组下标。

这是本题的标准设计：数组负责 `getRandom` 的均匀随机，下标表负责 `insert/remove` 的平均 `O(1)` 定位。

## 主要问题

- 整体设计正确，没有阻塞级问题。
- `remove` 里即使删除的元素本来就是最后一个，也会执行一次 `swap` 和 `mp[arr[idx]] = idx`。这不会导致错误，因为随后会 `mp.erase(val)`，但可以写成统一覆盖尾元素的形式，少一点心智负担。
- `rand() % len` 能通过 LeetCode，但随机质量和取模偏差不是工程级随机。面试和本题提交可以接受；真实项目里应使用 `<random>`。

## 做得好的地方

- 抓住了“删除中间元素时用最后一个元素补洞”的关键动作，这是本题最核心的不变量。
- `mp` 存的是值到数组下标的映射，和 `arr` 始终互相校验，结构很清楚。
- `getRandom` 没有绕远路，直接利用数组连续下标完成均匀随机。

## 最优解法

推荐最优解就是数组 + 哈希表。关键不变量是：对任何存在的值 `x`，`values[index[x]] == x` 必须一直成立。删除时不能直接从数组中间擦除，否则会变成 `O(n)`；正确做法是把尾元素搬到被删除位置，再更新尾元素的新下标。

- 时间复杂度：`insert/remove/getRandom` 平均 `O(1)`
- 空间复杂度：`O(n)`

## 最优解代码

```cpp
class RandomizedSet {
public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (index.count(val)) {
            return false;
        }

        index[val] = values.size();
        values.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = index.find(val);
        if (it == index.end()) {
            return false;
        }

        int removeIndex = it->second;
        int lastValue = values.back();

        values[removeIndex] = lastValue;
        index[lastValue] = removeIndex;

        values.pop_back();
        index.erase(val);
        return true;
    }

    int getRandom() {
        return values[rand() % values.size()];
    }

private:
    vector<int> values;
    unordered_map<int, int> index;
};
```

## 对比与改进方向

你的版本已经是最优模式。后续可以把这个设计抽象成一句话：哈希表负责定位，数组负责随机和尾删；删除时只维护“被尾元素覆盖的位置”这一处映射。

## 下一步建议

进入 `381` 是合理推进。`381` 的难点就是把 `mp[val] = index` 升级成 `mp[val] = 一组 index`，并继续保持删除补洞的不变量。

## 后续练习

1. `381. Insert Delete GetRandom O(1) - Duplicates allowed` - 当前题的重复值版本，正好验证结构升级能力。
2. `146. LRU Cache` - 同样是组合数据结构设计，训练“两个结构之间的不变量同步”。

## 来源链接

- https://leetcode.com/problems/insert-delete-getrandom-o1/
- https://leetcode.doocs.org/en/lc/380/
- https://leetcode.ca/all/380.html
