# 题解点评 - 981. Time Based Key-Value Store

## 基本信息

- 日期：2026-05-23
- 主题：二分查找 - 综合复盘与设计迁移加练
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/981.time-based-key-value-store.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 用哈希表按 `key` 保存该 key 的所有历史版本。
2. 每条历史记录保存为 `{timestamp, value}`，调用 `set` 时追加到对应数组末尾。
3. 调用 `get` 时，先判断 key 是否存在。
4. 对该 key 的历史时间轴做二分，寻找第一个 `timestamp > 查询时间` 的位置。
5. 如果位置为 `0`，说明没有可用历史值；否则返回前一个记录的 value。

## 用户解法复杂度

- `set` 时间复杂度：`O(1)` 均摊
- `get` 时间复杂度：`O(log m)`，其中 `m` 是该 key 的历史版本数量
- 空间复杂度：`O(totalSet)`，保存所有历史版本
- 复杂度来源：哈希表定位 key，单个 key 内的版本数组按时间戳递增，查询时二分。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pis=pair<int, string>;
class TimeMap {
public:
    unordered_map<string, vector<pis>> mp;
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value}); // 依赖题目保证同一 key 的 timestamp 递增。
    }
    
    string get(string key, int timestamp) {
        if(mp.find(key) == mp.end()) {
            return "";
        }
        vector<pis>& arr=mp[key];
        int n=arr.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(arr[m].first > timestamp) {
                r=m; // 找第一个时间戳大于查询时间的位置。
            } else {
                l=m+1;
            }
        }
        
        return l==0? "" : arr[l-1].second; // 前一个版本就是最后一个不超过查询时间的值。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 数据结构设计 | 哈希表映射到时间有序数组 | 正确支持按 key 独立查询历史版本 | 继续强调 `set` 追加成立依赖时间戳递增约束 |
| 边界语义 | 找第一个 `timestamp > query`，返回前一位 | 正确处理等于查询时间和没有更早版本 | 这正是 `upper_bound` 语义，可沉淀成模板 |
| 查询写法 | `find` 后又用 `mp[key]` 取数组 | 正确但会做一次额外哈希查找 | 用迭代器 `it->second` 更直接，也避免误插入习惯 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 核心结构正确，二分边界稳定，复杂度最优 | `mp[key]` 在查询中表达略松，成员公开 | 适合本题直接提交 |
| 推荐最优解 | 用 `upper_bound` 表达“第一个大于查询时间”，查询逻辑更语义化 | 自定义比较器需要熟悉参数顺序 | 适合作为时间轴版本查询模板 |

## 最优解法

1. `set` 时把每个 key 的历史值追加到数组中，利用题目保证时间戳递增。
2. `get` 时先通过哈希表找到 key 对应的历史数组。
3. 用 `upper_bound` 找到第一个时间戳大于查询时间的记录。
4. 如果该位置是数组开头，说明没有可用版本；否则返回前一个记录。

- 最优 `set` 时间复杂度：`O(1)` 均摊
- 最优 `get` 时间复杂度：`O(log m)`
- 最优空间复杂度：`O(totalSet)`

### 最优解代码

```cpp
class TimeMap {
    using Record = pair<int, string>;
    unordered_map<string, vector<Record>> recordsByKey;

public:
    TimeMap() = default;
    
    void set(string key, string value, int timestamp) {
        recordsByKey[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto it = recordsByKey.find(key);
        if (it == recordsByKey.end()) {
            return "";
        }

        const vector<Record>& records = it->second;
        auto pos = upper_bound(
            records.begin(),
            records.end(),
            timestamp,
            [](int time, const Record& record) {
                return time < record.first;
            }
        );

        if (pos == records.begin()) {
            return "";
        }
        --pos; // upper_bound 找到第一个大于 timestamp 的版本，前一个才是可用版本。
        return pos->second;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `mp` 公开保存所有 key 的版本 | 私有 `recordsByKey` 保存版本 | 设计题建议隐藏内部状态 |
| 更新逻辑 | `set` 直接追加 | 相同 | 明确依赖 timestamp 递增 |
| 边界处理 | 手写二分找第一个大于查询时间 | `upper_bound` 直接表达同一语义 | 两种写法都掌握即可 |
| 复杂度 | `set O(1)`，`get O(log m)` | 相同 | 已达最优 |

## 下一步建议

进入下一题即可。复盘时重点把它和 `34` 的 `upper_bound(target) - 1` 对齐：一个查值范围右边界，一个查时间轴历史版本。

## 后续练习

1. `729. My Calendar I` - 继续练习按时间轴维护区间并查询冲突。
2. `1146. Snapshot Array` - 同样是版本化查询，很适合迁移这题的 key 到历史数组结构。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/981.time-based-key-value-store.cpp`
- 新函数名：`getOpt`
- 保留用户原实现：是
