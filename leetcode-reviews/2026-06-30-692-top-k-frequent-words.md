# 题解点评 - 692. Top K Frequent Words

## 基本信息

- 日期：2026-06-30
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/692.top-k-frequent-words.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-06-30，信息待官方页面复核

## 用户思路概述

1. 先用哈希表统计每个单词出现次数。
2. 用 `{count, word}` 作为堆元素，让堆顶代表当前最应该被淘汰的候选。
3. 如果两个单词频次不同，频次更低者优先淘汰；如果频次相同，字典序更大的词优先淘汰。
4. 堆中最终保留前 `k` 个词，弹出后再反转，得到频次降序、同频字典序升序的答案。

## 用户解法复杂度

- 时间复杂度：`O(n + m log k + k)`，其中 `n` 是单词总数，`m` 是不同单词数；最后反转为 `O(k)`
- 空间复杂度：`O(m + k)`
- 复杂度来源：哈希表保存所有不同单词，固定大小堆保存当前前 `k` 个候选。

## 用户代码注释版

```cpp
using pis = pair<int, string>;
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n=words.size();
        unordered_map<string, int> cnt;
        for(int i=0; i<n; i++) {
            cnt[words[i]]++; // 先统计每个单词频次。
        }

        auto cmp = [](const pis& a, const pis& b)->bool {
            if (a.first != b.first) {
                return a.first > b.first; // 频次低的候选应该在堆顶，方便淘汰。
            }
            return a.second < b.second; // 同频时字典序更大的候选应该在堆顶。
        };

        priority_queue<pis, vector<pis>, decltype(cmp)> pq;
        for(auto [str, count]: cnt) {
            pq.push({count, str});
            while(pq.size() > k) {
                pq.pop(); // 弹掉当前最差候选。
            }
        }

        vector<string> ans;
        while(!pq.empty()) {
            auto [_, str] = pq.top();pq.pop();
            ans.push_back(str); // 弹出顺序是从差到好。
        }
        reverse(ans.begin(), ans.end()); // 反转成题目要求的答案顺序。
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 多关键字比较 | 同时处理频次和字典序 | 正确覆盖本题最容易错的规则 | 复盘时写出“答案顺序”和“淘汰顺序”两套规则 |
| 堆顶语义 | 让堆顶成为最差候选 | 固定大小堆才能正确弹出 | 以后 Top K 题先问自己：超过 `k` 时弹谁 |
| 输出顺序 | 弹出后反转 | 正确修复堆弹出顺序和答案顺序相反的问题 | 遇到要求有序输出时，不要只返回堆中元素 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 比较器方向正确，空间只保留 `k` 个候选 | 比较器不容易一眼看懂，需要注释或复盘辅助 | 需要在频次和字典序之间做 Top K |
| 推荐最优解 | 与用户方案一致，整理命名后更强调“最差候选” | 实现难点仍在比较器方向 | 本题最适合训练复合优先级的堆写法 |

## 最优解法

1. 统计每个单词频次。
2. 维护一个大小为 `k` 的堆，堆顶始终是当前 Top K 集合中最差的词。
3. 频次低的词更差；频次相同，字典序更大的词更差。
4. 遍历结束后，堆中词从差到好弹出，所以需要反转。

- 最优时间复杂度：`O(n + m log k)`
- 最优空间复杂度：`O(m + k)`

### 最优解代码

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count;
        for (const string& word : words) {
            ++count[word];
        }

        using Node = pair<int, string>;
        auto worseFirst = [](const Node& a, const Node& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            // 同频时字典序更大的词更差，应更早被弹出。
            return a.second < b.second;
        };

        priority_queue<Node, vector<Node>, decltype(worseFirst)> heap(worseFirst);
        for (const auto& [word, freq] : count) {
            heap.push({freq, word});
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<string> ans;
        while (!heap.empty()) {
            ans.push_back(heap.top().second);
            heap.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `{count, word}` | `{freq, word}` | 当前状态正确，变量名可更贴近语义 |
| 更新逻辑 | 入堆后超过 `k` 就弹出 | 同样逻辑 | `while` 可简化为 `if` |
| 边界处理 | 最后反转答案 | 同样反转 | 这是本题关键，必须保留 |
| 复杂度 | `O(n + m log k)` | `O(n + m log k)` | 复杂度已经符合 Top K 堆写法 |

## 下一步建议

补边界测试并做跟练题。建议手动测同频词较多的情况，例如 `["a","b","c"]` 且 `k = 2`，确认字典序更小的词排在前面。

## 后续练习

1. `347. Top K Frequent Elements` - 去掉字典序后，回看频次 Top K 的基础形态。
2. `451. Sort Characters By Frequency` - 练习频次排序和输出顺序之间的关系。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/692.top-k-frequent-words.cpp`
- 新函数名：`topKFrequentOpt`
- 保留用户原实现：是。
