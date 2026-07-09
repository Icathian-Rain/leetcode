# 第 09 周 - 堆与优先队列

## 本周目标

完成核心 8 周后，本周开始补扩展主题。堆与优先队列的目标不是“会调用 `priority_queue`”，而是能判断什么时候只需要维护局部前几名、什么时候需要动态取最大/最小、什么时候输入会持续变化但答案必须随时可查。到本周结束时，你应该能主动说清：堆里保存什么、堆大小为什么这样控制、弹出元素是否还会影响后续答案。

资料依据：默认扩展主题顺序与核心题池参考 `.codex/skills/leetcode-weekly-coach/references/topic-ladders.md`；题号、英文题名和难度按本地训练题池整理，记录日期为 2026-06-29。做题或生成点评时，再按单题继续核对官方信息。

## 与前 8 周衔接

前 8 周已经练过哈希计数、排序、滑动窗口、链表合并和动态规划。堆会把这些能力连接起来：哈希负责统计候选，排序意识帮助比较优先级，链表题会遇到多路合并，窗口题会遇到动态极值。本周重点是把“全量排序后取答案”推进成“只维护必要候选”。

## 前置知识

- 能区分最大堆和最小堆的优先级方向。
- 能用 `pair` 或自定义比较表达排序规则。
- 能判断堆中元素是否需要携带原始下标、频次、距离或链表节点。
- 能解释堆大小固定为 `k` 的意义。
- 能接受同一题可能有排序、堆、快速选择等多种做法。

## 每日计划

### 第 1 天 - 动态极值入口

1. `703. Kth Largest Element in a Stream` (`简单`) - 练习在持续加入元素时维护一个稳定的第 k 个结果。
2. `1046. Last Stone Weight` (`简单`) - 练习反复取出当前最大的两个元素并把结果放回候选集合。
3. `215. Kth Largest Element in an Array` (`中等`) - 练习在静态数组里只关心某个排名位置的结果。

### 第 2 天 - Top K 与距离排序

1. `347. Top K Frequent Elements` (`中等`) - 练习从频次统计结果中保留最重要的一小部分候选。
2. `973. K Closest Points to Origin` (`中等`) - 练习用比较规则维护距离意义下的前 k 个结果。
3. `692. Top K Frequent Words` (`中等`) - 练习在频次之外加入字典序这类次级排序要求。

### 第 3 天 - 多路合并

1. `23. Merge k Sorted Lists` (`困难`) - 练习同时推进多个有序来源，并每次取当前最小候选。
2. `373. Find K Pairs with Smallest Sums` (`中等`) - 练习从两个有序来源组合出较小结果，并避免一次性展开所有组合。
3. `378. Kth Smallest Element in a Sorted Matrix` (`中等`) - 练习在多行有序结构中逐步弹出候选。

### 第 4 天 - 任务调度与冷却约束

1. `621. Task Scheduler` (`中等`) - 练习在频次和间隔限制下安排任务顺序。
2. `767. Reorganize String` (`中等`) - 练习在相邻限制下持续选择当前最合适的字符。
3. `358. Rearrange String k Distance Apart` (`困难`) - 练习在更严格距离限制下维护暂时不可用的候选。

### 第 5 天 - 数据流中位数

1. `295. Find Median from Data Stream` (`困难`) - 练习把数据流分成左右两部分，并持续保持中间位置可查。
2. `480. Sliding Window Median` (`困难`) - 练习在窗口移动时维护中间值，同时处理过期元素。
3. `1825. Finding MK Average` (`困难`) - 练习维护多个区间的动态统计结果。

### 第 6 天 - 窗口与延迟删除

1. `239. Sliding Window Maximum` (`困难`) - 练习在移动窗口内维护当前最大值。
2. `1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit` (`中等`) - 练习同时关注窗口内最大值和最小值。
3. `218. The Skyline Problem` (`困难`) - 练习在扫描过程中维护仍然有效的最高候选。

### 第 7 天 - 综合复盘与方案取舍

1. `658. Find K Closest Elements` (`中等`) - 练习在多种可行策略之间选择更稳定的实现。
2. `451. Sort Characters By Frequency` (`中等`) - 回顾频次排序和候选维护的边界。
3. `895. Maximum Frequency Stack` (`困难`) - 练习同时维护频次和时间顺序这两种优先级。

## 本周关注清单

- 每题先写清堆里存的是值、下标、频次、距离还是节点。
- 固定大小堆题要能解释为什么超过 `k` 就弹出。
- 多关键字排序题要确认比较规则的主次顺序。
- 数据流题要关注插入、查询和删除三类操作是否都能支持。
- 有过期元素时，不急着删除所有旧元素，先判断什么时候需要清理堆顶。
- 每天复盘至少说明一次：如果不用堆而用排序，复杂度差在哪里。

## 本周节奏建议

- 第 1 天：先把堆的基本操作练顺，不追求复杂变体。
- 第 2 天：重点看 Top K 的候选保留逻辑。
- 第 3 天：进入多路合并，注意候选扩展顺序。
- 第 4 天：处理频次和距离限制，不要只凭直觉安排。
- 第 5 天：集中攻数据流，允许慢一点，但要把两边平衡讲清楚。
- 第 6 天：处理窗口和过期元素，重点练有效性判断。
- 第 7 天：做方案取舍，比较排序、堆、双指针和其他已学模式。

## 进度更新 - 2026-06-29

- 今日完成：`703. Kth Largest Element in a Stream`、`1046. Last Stone Weight`、`215. Kth Largest Element in an Array`
- 当前主题：堆与优先队列

### 通用解题模板

- 适用条件：题目只关心当前最大、最小、第 k 个、Top K 或每一步都要取出优先级最高的候选，而不需要完整排序所有元素。
- 核心骨架：把候选放入堆；如果只关心前 k 个结果，就用固定大小堆维护必要候选；如果每轮都要取当前极值，就弹出堆顶并按题意把新状态放回。
- 关键边界：固定大小堆超过 `k` 后要立刻弹出无用候选；反复取两个元素时循环条件应保证堆里至少有两个元素；返回前要处理堆为空的情况。
- 复杂度：固定大小堆通常为时间 `O(n log k)`、空间 `O(k)`；反复取极值通常为时间 `O(n log n)`、空间 `O(n)`。

```cpp
class Solution {
public:
    int keepTopK(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int num : nums) {
            heap.push(num);
            // 堆里只保留当前最大的 k 个候选。
            if (heap.size() > k) {
                heap.pop();
            }
        }
        return heap.top();
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `703. Kth Largest Element in a Stream` | 通过倾向 | 用小根堆稳定维护前 `k` 大元素，构造和追加逻辑一致 | 复盘时要能说清堆顶为什么正好是第 `k` 大，而不是当前最小值 | [查看](../leetcode-reviews/2026-06-29-703-kth-largest-element-in-a-stream.md) |
| `1046. Last Stone Weight` | 通过倾向 | 正确使用大根堆反复取出两块最重石头，空堆返回处理稳 | 可以把 `less<int>` 简化为默认写法，并删掉提交前调试痕迹 | [查看](../leetcode-reviews/2026-06-29-1046-last-stone-weight.md) |
| `215. Kth Largest Element in an Array` | 通过倾向 | 同时写出了快速选择和固定大小堆两种方案，方案意识很好 | 当前提交选择堆方案，复盘时要比较它和快速选择在复杂度与稳定性上的取舍 | [查看](../leetcode-reviews/2026-06-29-215-kth-largest-element-in-an-array.md) |

- 暴露问题：整体思路已经进入“维护必要候选”的节奏；下一步需要更主动地解释堆大小、堆顶语义和不同方案的复杂度取舍。
- 下一步安排：继续第 2 天 Top K 与距离排序训练，把“固定大小堆”迁移到频次、距离和字典序规则上。

## 进度更新 - 2026-06-30

- 今日完成：`973. K Closest Points to Origin`、`692. Top K Frequent Words`
- 当前主题：堆与优先队列

### 通用解题模板

- 适用条件：题目要求从一批候选中找前 `k` 个，并且优先级不是单纯数值大小，而是距离、频次、字典序等复合规则。
- 核心骨架：先把题目要求转成可比较的优先级；用固定大小堆保存当前最优的 `k` 个候选；堆顶放“当前保留集合里最应该淘汰的候选”。
- 关键边界：比较器要反着服务于“淘汰谁”；同频、同距离等并列情况要按题目要求补第二关键字；如果弹出顺序和答案顺序相反，最后需要反转。
- 复杂度：设候选数为 `n`，固定大小堆时间 `O(n log k)`，空间 `O(k)`；若需要先统计频次，额外统计时间 `O(n)`、空间 `O(m)`。

```cpp
class Solution {
public:
    vector<int> topKByScore(vector<pair<int, int>>& items, int k) {
        auto worseFirst = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(worseFirst)> heap(worseFirst);
        for (auto item : items) {
            heap.push(item);
            // 超过 k 时弹出当前最差候选。
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<int> ans;
        while (!heap.empty()) {
            ans.push_back(heap.top().second);
            heap.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `973. K Closest Points to Origin` | 通过倾向 | 能把点转换成距离和下标，并用固定大小大根堆淘汰最远候选 | 复盘时要说清比较器为什么让距离最大的点留在堆顶 | [查看](../leetcode-reviews/2026-06-30-973-k-closest-points-to-origin.md) |
| `692. Top K Frequent Words` | 通过倾向 | 比较器同时处理频次和字典序，最后反转答案顺序，关键细节到位 | 这是本日最值得复盘的题：比较器写的是“谁更差”，不是“答案谁在前” | [查看](../leetcode-reviews/2026-06-30-692-top-k-frequent-words.md) |

- 暴露问题：`973` 的优先级较单一，迁移顺畅；`692` 已经进入多关键字比较，后续要继续练“堆顶语义”和“答案顺序”分离。
- 下一步安排：可先复做旧题 `347. Top K Frequent Elements` 补齐第 2 天三题闭环，再进入第 3 天多路合并训练。

## 进度更新 - 2026-07-01

- 今日完成：`23. Merge k Sorted Lists`、`373. Find K Pairs with Smallest Sums`、`378. Kth Smallest Element in a Sorted Matrix`
- 当前主题：堆与优先队列

### 通用解题模板

- 适用条件：输入由多个已经有序的来源组成，答案需要按全局从小到大的顺序逐步产生，且不适合一次性展开所有候选。
- 核心骨架：每个来源先放入一个当前最小候选；每次弹出全局最小候选后，只推进它所属来源的下一个候选。
- 关键边界：初始入堆时跳过空来源；弹出候选后必须检查该来源是否还有下一个位置；组合题要避免把同一状态重复加入堆。
- 复杂度：若一共弹出 `t` 个结果、堆中最多维护 `k` 个来源，时间 `O(t log k)`，空间 `O(k)`。

```cpp
class Solution {
public:
    vector<int> mergeSources(vector<vector<int>>& sources) {
        using State = tuple<int, int, int>; // value, source index, position
        priority_queue<State, vector<State>, greater<State>> heap;
        for (int i = 0; i < sources.size(); ++i) {
            if (!sources[i].empty()) {
                heap.push({sources[i][0], i, 0});
            }
        }

        vector<int> ans;
        while (!heap.empty()) {
            auto [value, source, pos] = heap.top();
            heap.pop();
            ans.push_back(value);
            // 只推进被弹出来源的下一个候选。
            if (pos + 1 < sources[source].size()) {
                heap.push({sources[source][pos + 1], source, pos + 1});
            }
        }
        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `23. Merge k Sorted Lists` | 通过倾向 | 正确把每条链表头节点放入小根堆，并在弹出后推进同一链表 | 复盘时要说清堆里保存的是节点指针，不是值拷贝 | [查看](../leetcode-reviews/2026-07-01-23-merge-k-sorted-lists.md) |
| `373. Find K Pairs with Smallest Sums` | 通过倾向 | 只初始化每个 `nums1[i]` 搭配 `nums2[0]`，避免展开所有组合 | 重点复盘为什么只推进 `(i, j + 1)` 不会漏掉更小组合 | [查看](../leetcode-reviews/2026-07-01-373-find-k-pairs-with-smallest-sums.md) |
| `378. Kth Smallest Element in a Sorted Matrix` | 通过倾向 | 能把每一行当作一个有序来源，逐步弹出第 `k` 小 | 本题还存在值域二分方案，复盘时比较堆解法和二分解法的适用场景 | [查看](../leetcode-reviews/2026-07-01-378-kth-smallest-element-in-a-sorted-matrix.md) |

- 暴露问题：多路合并主线已经稳定；下一步要更主动地区分“候选来源推进”和“固定 Top K 淘汰”，这两类堆题虽然都用优先队列，但状态含义完全不同。
- 下一步安排：进入第 4 天任务调度与冷却约束训练，重点观察候选被暂时禁用后如何重新回到可选集合。

## 进度更新 - 2026-07-09

- 今日完成：`621. Task Scheduler`、`767. Reorganize String`
- 当前主题：堆与优先队列

### 通用解题模板

- 适用条件：题目围绕字符或任务频次展开，要求在相邻限制、冷却间隔或排列合法性约束下安排元素。
- 核心骨架：先统计频次；判断最高频元素是否会撑破可用空位；能用公式直接计数时优先用公式，必须构造结果时再按频次选择或填充位置。
- 关键边界：最高频次数是合法性的核心；多个最高频任务会共同占用最后一组位置；构造字符串时要保证同类字符不会落在相邻位置。
- 复杂度：统计频次为时间 `O(n)`，固定字符集空间 `O(1)`；若用堆模拟，时间通常为 `O(n log C)`，其中 `C` 是字符或任务种类数。

```cpp
class Solution {
public:
    bool canArrangeByFrequency(string s) {
        vector<int> freq(26, 0);
        int maxFreq = 0;
        for (char ch : s) {
            maxFreq = max(maxFreq, ++freq[ch - 'a']);
        }
        // 最高频字符不能超过可放置的非相邻槽位数量。
        return maxFreq <= (static_cast<int>(s.size()) + 1) / 2;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `621. Task Scheduler` | 通过倾向 | 没有陷入逐步模拟，而是抓住最高频任务决定最短框架 | 复盘时要能解释 `max(tasks.size(), frame)` 为什么覆盖任务填满空槽的情况 | [查看](../leetcode-reviews/2026-07-09-621-task-scheduler.md) |
| `767. Reorganize String` | 通过倾向 | 同时写出堆模拟和奇偶位填充，最终选择更直接的构造方案 | 重点复盘最高频字符先占偶数位为什么能避免相邻冲突 | [查看](../leetcode-reviews/2026-07-09-767-reorganize-string.md) |

- 暴露问题：你已经能把“堆取当前最高频”推进到“先判断最高频是否决定答案”的层次；后续要继续区分“需要构造过程”和“只需要最小长度/可行性”的题。
- 下一步安排：第 4 天的 `358. Rearrange String k Distance Apart` 尚未确认完成，可作为这组频次约束的拔高复盘题；如果先进入第 5 天，则重点关注数据流中两个有序部分如何维持平衡。
