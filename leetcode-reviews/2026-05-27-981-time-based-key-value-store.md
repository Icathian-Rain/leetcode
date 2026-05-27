# 题解点评 - 981. Time Based Key-Value Store

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 7 天综合复盘与设计迁移
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/981.time-based-key-value-store.cpp`
- 资料来源：LeetCode 官方题目页、既有本地点评
- 查询日期：2026-05-27

## 用户思路概述

1. 用哈希表把每个 `key` 映射到一组按时间递增的历史记录。
2. `set` 时直接追加 `{timestamp, value}`。
3. `get` 时在该 key 的历史数组中二分第一个 `timestamp > 查询时间` 的位置。
4. 若该位置为开头，说明没有可用版本；否则返回前一个版本。

## 用户解法复杂度

- `set` 时间复杂度：`O(1)` 均摊
- `get` 时间复杂度：`O(log m)`，`m` 是该 key 的历史版本数
- 空间复杂度：`O(totalSet)`
- 复杂度来源：哈希表按 key 分组，单个 key 内用有序时间数组二分。

## 用户代码注释版

```cpp
using pis=pair<int, string>;
class TimeMap {
public:
    unordered_map<string, vector<pis>> mp;
    
    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value}); // 依赖题目保证 timestamp 递增。
    }
    
    string get(string key, int timestamp) {
        if(mp.find(key) == mp.end()) return "";
        vector<pis>& arr=mp[key];

        int l=0, r=arr.size();
        while(l<r) {
            int m=l+(r-l)/2;
            if(arr[m].first > timestamp) r=m; // 第一个大于查询时间的位置。
            else l=m+1;
        }
        
        return l==0? "" : arr[l-1].second;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 设计建模 | 正确按 key 拆分时间轴 | 支持高效历史版本查询 | 明确 `set` 的递增时间戳是数组有序的前提 |
| 边界语义 | 找第一个大于查询时间，再回退一位 | 正确处理等于和早于最早版本 | 可直接对应 `upper_bound` |
| 封装性 | `mp` 为 public | 不影响 LeetCode 通过，但设计感略弱 | 推荐把存储结构设为 private |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 数据结构和二分边界都正确 | 查询中 `find` 后再 `mp[key]` 表达略松 | 适合直接提交 |
| 推荐最优解 | 用 `upper_bound` 表达边界语义，更像库模板 | 比较器参数顺序需要熟悉 | 适合版本化查询类题 |

## 最优解法

1. `set` 将同一 key 的版本追加到数组。
2. `get` 先通过哈希表找到对应时间轴。
3. 用 `upper_bound` 找第一个时间戳大于查询时间的记录，返回它的前一个版本。

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
        auto pos = upper_bound(records.begin(), records.end(), timestamp,
            [](int time, const Record& record) {
                return time < record.first;
            });

        if (pos == records.begin()) {
            return "";
        }
        --pos; // 第一个大于 timestamp 的前一个版本才可用。
        return pos->second;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 公开 `mp` | 私有 `recordsByKey` | 设计题更强调封装 |
| 更新逻辑 | 追加历史版本 | 相同 | 说清时间戳递增约束 |
| 边界处理 | 手写第一个大于 | `upper_bound` | 两种写法都值得保留 |
| 复杂度 | 最优 | 最优 | 已达标 |

## 下一步建议

进入整周复盘：把 `981` 和 `34` 对齐理解，都是“找第一个大于目标的位置，再取前一个合法答案”。

## 后续练习

1. `1146. Snapshot Array` - 同样是按下标保存版本历史。
2. `729. My Calendar I` - 继续训练时间轴上的边界判断。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/981.time-based-key-value-store.cpp`
- 新函数名：`getOpt`
- 保留用户原实现：是
