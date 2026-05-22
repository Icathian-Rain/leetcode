# 算法模板 - 频次统计与签名分组

## 基本信息

- 日期：2026-05-22
- 主题：第 1 周数组与哈希
- 目标：把字符、数字或对象转成可比较的频次状态或签名 key
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-frequency-counting-signature.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-frequency-counting-signature.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目要求判断两个对象是否“由同一批元素组成”
- 题目要求按某种等价关系分组，例如异位词、相同频次、相同约束状态
- 元素范围较小，能用定长数组统计；元素范围较大或 key 稀疏，适合用哈希表

## 核心思路

1. 先判断状态只需要比较真假、计数缺口，还是要作为分组 key。
2. 小字符集优先用定长数组保存频次，状态稳定且常数小。
3. 要分组时，把频次数组编码成不会冲突的字符串或结构化 key。
4. 扫描过程中如果维护缺口，注意频次跨过 `0` 的时机代表状态变化。

## 关键边界

- 字符集大小要和题目输入一致，例如仅小写字母、ASCII 或任意字符
- 分组签名必须有分隔符，避免 `[1, 11]` 和 `[11, 1]` 拼接冲突
- 只判断能否构造时，某个频次变成负数即可提前返回
- 如果输入包含大写、数字或 Unicode，不能直接套 `ch - 'a'`

## 复杂度

- 时间复杂度：`O(totalLength * C)` 或 `O(totalLength)`，取决于签名构造方式
- 空间复杂度：`O(groups * C)` 或 `O(C)`，其中 `C` 是状态维度

## 模板代码

```cpp
class Solution {
private:
    string signature(const string& word) {
        array<int, 26> count{};
        for (char ch : word) {
            ++count[ch - 'a'];
        }

        string key;
        for (int value : count) {
            key += '#';
            key += to_string(value); // 分隔符避免不同频次拼接成同一个 key。
        }
        return key;
    }

public:
    vector<vector<string>> groupByFrequency(vector<string>& words) {
        unordered_map<string, vector<string>> groups;
        for (const string& word : words) {
            groups[signature(word)].push_back(word);
        }

        vector<vector<string>> ans;
        for (auto& [_, group] : groups) {
            ans.push_back(move(group));
        }
        return ans;
    }

    bool canBuildFrom(string target, string source) {
        array<int, 26> count{};
        for (char ch : source) {
            ++count[ch - 'a'];
        }
        for (char ch : target) {
            if (--count[ch - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
```

## 运行样例

### 样例 1

- 输入：`words = ["eat","tea","tan","ate","nat","bat"]`
- 输出：按异位词分成 3 组
- 说明：`eat/tea/ate` 的 26 维频次签名一致，因此进入同一组。

### 样例 2

- 输入：`target = "aa", source = "ab"`
- 输出：`false`
- 说明：第二个 `a` 会让源频次变成负数，说明资源不足。

## 套用提醒

- 只比较两个字符串时，频次数组通常比哈希表更简单。
- 要把状态当 key 时，优先写一个独立 `signature` 函数，避免分组逻辑里混入编码细节。
- 如果题目要求一对一映射，频次不够，需要额外维护双向映射关系。
