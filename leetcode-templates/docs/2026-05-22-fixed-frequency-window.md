# 算法模板 - 固定长度频次窗口

## 基本信息

- 日期：2026-05-22
- 主题：第 2 周双指针与滑动窗口
- 目标：维护一个和目标等长的窗口，并用频次差判断是否匹配
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-fixed-frequency-window.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-fixed-frequency-window.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目要求判断某个排列、异位词或等长片段是否出现在字符串里
- 窗口长度固定为目标串长度
- 只要比较频次，不关心窗口内字符顺序

## 核心思路

1. 用 `diff[c]` 表示目标串和当前窗口在字符 `c` 上的频次差。
2. 用 `different` 记录还有多少字符的差值不为 `0`，避免每轮比较整张表。
3. 右端加入字符时减少对应差值；窗口超长时，左端字符离开并恢复差值。
4. 当窗口长度达到目标长度且 `different == 0` 时，窗口就是一个匹配片段。

## 关键边界

- 目标串比文本长时直接返回无匹配
- 只有窗口长度达到目标长度后才能记录答案
- `different` 的更新必须看差值从 `0` 到非 `0`，或从非 `0` 回到 `0`
- 字符集不是小写字母时，要扩大数组或改用哈希表

## 复杂度

- 时间复杂度：`O(n + C)`，其中 `C` 是字符集大小
- 空间复杂度：`O(C)`

## 模板代码

```cpp
class Solution {
private:
    void addDiff(array<int, 26>& diff, int& different, int index, int delta) {
        int before = diff[index];
        int after = before + delta;
        if (before == 0 && after != 0) {
            ++different;
        } else if (before != 0 && after == 0) {
            --different;
        }
        diff[index] = after;
    }

public:
    vector<int> findAnagramStarts(string text, string pattern) {
        vector<int> ans;
        if (pattern.size() > text.size()) {
            return ans;
        }

        array<int, 26> diff{};
        int different = 0;
        for (char ch : pattern) {
            addDiff(diff, different, ch - 'a', 1);
        }

        int windowSize = static_cast<int>(pattern.size());
        for (int right = 0; right < static_cast<int>(text.size()); ++right) {
            addDiff(diff, different, text[right] - 'a', -1);
            if (right >= windowSize) {
                addDiff(diff, different, text[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                ans.push_back(right - windowSize + 1);
            }
        }

        return ans;
    }
};
```

## 运行样例

### 样例 1

- 输入：`text = "cbaebabacd", pattern = "abc"`
- 输出：`[0, 6]`
- 说明：长度为 `3` 的窗口在起点 `0` 和 `6` 处频次完全匹配。

### 样例 2

- 输入：`text = "eidboaoo", pattern = "ab"`
- 输出：`[]`
- 说明：所有长度为 `2` 的窗口都无法让 `different` 归零。

## 套用提醒

- 输出所有起点时返回数组；只判断是否存在时，命中后直接返回 `true`。
- 这类题的核心不是移动指针，而是维护差值状态准确。
- 如果窗口长度不固定，就不要硬套本模板，应切换到可变窗口。
