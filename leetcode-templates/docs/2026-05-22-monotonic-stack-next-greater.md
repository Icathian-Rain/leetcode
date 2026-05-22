# 算法模板 - 单调栈等待结算

## 基本信息

- 日期：2026-05-22
- 主题：第 3 周栈与队列
- 目标：维护一组等待被未来元素解决的下标，并在条件满足时回填答案
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-05-22-monotonic-stack-next-greater.md`
- 测试代码路径：`leetcode-templates/code/2026-05-22-monotonic-stack-next-greater.cpp`
- 资料来源：本地周计划、既有题解与复盘记录，未联网校准

## 适用信号

- 题目要求找右侧第一个更大、更小、更高温度或下一个满足条件的元素
- 当前元素到来时，能解决一批之前尚未确定答案的位置
- 每个元素最多被加入和弹出一次，适合摊还 `O(n)`

## 核心思路

1. 栈里保存还没有找到答案的下标，而不是只保存值。
2. 当前元素能解决栈顶时，持续弹出栈顶并回填答案。
3. 弹出结束后，当前下标进入等待栈。
4. 没有被解决的位置保留默认答案，例如 `-1` 或 `0`。

## 关键边界

- 严格更大时，相等不能弹出；更大等于时才用 `<=`
- 需要返回距离、位置或回填原数组时，必须保存下标
- 环形数组通常扫描两轮，但每个下标只在第一轮入栈
- 如果题目是“左侧第一个”，可以从左到右换条件，也可以从右到左扫描

## 复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`

## 模板代码

```cpp
class Solution {
public:
    vector<int> daysUntilWarmer(vector<int>& temperatures) {
        vector<int> ans(temperatures.size(), 0);
        vector<int> waiting;

        for (int i = 0; i < static_cast<int>(temperatures.size()); ++i) {
            while (!waiting.empty() && temperatures[waiting.back()] < temperatures[i]) {
                int previous = waiting.back();
                waiting.pop_back();
                ans[previous] = i - previous; // 题目要距离，所以用当前下标减等待下标。
            }
            waiting.push_back(i);
        }

        return ans;
    }

    vector<int> nextGreaterCircular(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        vector<int> waiting;

        for (int i = 0; i < 2 * n; ++i) {
            int index = i % n;
            while (!waiting.empty() && nums[waiting.back()] < nums[index]) {
                ans[waiting.back()] = nums[index];
                waiting.pop_back();
            }
            if (i < n) {
                waiting.push_back(index);
            }
        }

        return ans;
    }
};
```

## 运行样例

### 样例 1

- 输入：`temperatures = [73,74,75,71,69,72,76,73]`
- 输出：`[1,1,4,2,1,1,0,0]`
- 说明：每个下标等待右侧第一个更高温度来结算天数差。

### 样例 2

- 输入：`nums = [1,2,1]`
- 输出：`[2,-1,2]`
- 说明：扫描两轮后，最后一个 `1` 可以在回绕处找到下一个更大值。

## 套用提醒

- 先问自己：栈里保存的是“等待答案的人”，还是“候选边界”。
- 找下一个更大和直方图面积都用单调栈，但前者是回填答案，后者是弹出时结算区间贡献。
- 比较符决定相等元素的归属，重复值多的题必须单独手推。
