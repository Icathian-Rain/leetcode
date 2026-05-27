# 第 05 周 - 二分查找

## 本周目标

把“看起来要遍历”的问题，转成“能排除一半搜索空间”的问题。到本周结束时，你应该能在动手前先说清：搜索范围是什么，答案是否一定存在，区间左右端点代表什么，循环什么时候停止，以及返回的是命中位置、插入位置、边界位置还是某个满足条件的最小 / 最大值。

当前进度：已完成第 3 天训练、第 5 天“答案范围与可行性检查”三题，并完成第 6 天峰值与困难边界中的 `162`、`1901`；`4` 已补最优解用于复盘。第 4 天“旋转与局部有序”尚未在计划中记录完成。

资料校准：题号、英文题名和难度已通过 LeetCode 中文题目页、leetcode.ca 镜像页与 LeetCode Wiki 资料校准；第 1 天题目于 2026-05-22 复核。

## 与第 4 周衔接

第 4 周链表题训练的是“节点身份”和“连接边界”。第 5 周会把注意力切到“区间边界”和“答案边界”：链表里一个 `next` 改错会断链，二分里一个端点收错会漏答案或死循环。两类题的共同点是：动手前必须先定义状态含义，写完后必须检查收尾条件。

## 前置知识

- 能区分数组下标和值本身
- 能写出 `left`、`right`、`mid` 并避免整数溢出
- 能判断目标是“找到某个值”还是“找到第一个 / 最后一个满足条件的位置”
- 能手推长度为 0、1、2 的边界样例
- 能解释循环结束时 `left` 和 `right` 各自停在哪里

## 每日计划

### 第 1 天 - 基础区间与插入位置

1. `704. Binary Search` (`简单`) - 练习在有序数组中查找目标值，并明确未命中时返回什么。
2. `35. Search Insert Position` (`简单`) - 练习目标不存在时返回应落入的位置。
3. `744. Find Smallest Letter Greater Than Target` (`简单`) - 练习在循环序列中寻找严格超过目标的元素，并覆盖回绕边界。

### 第 2 天 - 边界定位与近似答案

1. `278. First Bad Version` (`简单`) - 练习在一段状态变化中定位最早发生变化的位置。
2. `69. Sqrt(x)` (`简单`) - 练习在整数范围内寻找不超过目标的近似值。
3. `34. Find First and Last Position of Element in Sorted Array` (`中等`) - 练习在重复元素中定位目标出现的完整范围。

### 第 3 天 - 矩阵中的有序关系

1. `1351. Count Negative Numbers in a Sorted Matrix` (`简单`) - 练习利用二维结构中的行列顺序减少无效检查。
2. `74. Search a 2D Matrix` (`中等`) - 练习把二维位置和线性顺序对应起来。
3. `240. Search a 2D Matrix II` (`中等`) - 练习在行列同时有序但整体不连续的结构中缩小范围。

### 第 4 天 - 旋转与局部有序

1. `852. Peak Index in a Mountain Array` (`简单`) - 练习在先升后降的结构中定位转折位置。
2. `153. Find Minimum in Rotated Sorted Array` (`中等`) - 练习在整体被旋转后重新识别目标所在区域。
3. `33. Search in Rotated Sorted Array` (`中等`) - 练习在旋转后的数组中继续寻找指定目标。

### 第 5 天 - 答案范围与可行性检查

1. `875. Koko Eating Bananas` (`中等`) - 练习把速度选择转成一个有上下界的答案搜索。
2. `1011. Capacity To Ship Packages Within D Days` (`中等`) - 练习在约束条件下寻找最小可行容量。
3. `1283. Find the Smallest Divisor Given a Threshold` (`中等`) - 练习把数值选择和累计结果约束结合起来。

### 第 6 天 - 峰值、分割与困难边界

1. `162. Find Peak Element` (`中等`) - 练习在不要求唯一答案的场景中找到任意合法位置。
2. `1901. Find a Peak Element II` (`中等`) - 练习把一维位置判断迁移到二维结构。
3. `4. Median of Two Sorted Arrays` (`困难`) - 练习在两个有序序列之间定位全局中间位置。

### 第 7 天 - 综合复盘与设计迁移

1. `540. Single Element in a Sorted Array` (`中等`) - 练习利用成对结构变化定位唯一元素。
2. `658. Find K Closest Elements` (`中等`) - 练习在有序数组中确定一段最合适的连续结果。
3. `981. Time Based Key-Value Store` (`中等`) - 把本周的边界查找迁移到设计题中的历史版本查询。

## 本周关注清单

- 每道题动手前先写一句：我要找的是值、下标、边界，还是最小 / 最大可行答案。
- 统一检查 `mid` 计算方式，避免大整数范围下溢出。
- 循环条件不要凭感觉改；每次更新端点后，都要知道有没有保留潜在答案。
- 所有题都手推长度为 1 和 2 的样例，尤其是返回左端点还是右端点。
- 遇到“最小满足条件”或“最大满足条件”时，先写清最终返回值，不要边写边猜。
- 矩阵和设计题不要急着套模板，先确认一维顺序是否真实存在。

## 本周节奏建议

- 第 1-2 天：把基础区间、插入位置和左右边界写稳，重点观察循环结束时端点含义。
- 第 3-4 天：进入二维结构、旋转结构和局部有序结构，重点训练“哪一边可以被排除”。
- 第 5 天：切到答案范围题，重点把候选答案和检查函数拆开思考。
- 第 6 天：处理峰值和困难边界，不追求快，先画出当前位置和相邻位置关系。
- 第 7 天：做综合迁移，把本周模板迁移到成对结构、连续结果段和设计题时间轴。

## 进度更新 - 2026-05-22

- 今日完成：`704. Binary Search`、`35. Search Insert Position`、`744. Find Smallest Letter Greater Than Target`
- 当前主题：第 1 天 - 基础区间与插入位置

### 通用解题模板

- 适用条件：题目可以转成 `false...false true...true` 的单调判断，并要求找到第一个 `true` 的位置。
- 核心骨架：使用左闭右开区间 `[left, right)`；`check(middle) == true` 时，`middle` 可能是第一个 `true`，所以收缩右边界 `right = middle`；`check(middle) == false` 时，`middle` 和它左侧都可以排除，所以 `left = middle + 1`。
- 关键边界：循环结束后返回 `left`；如果 `left == n`，说明不存在 `true`；如果题目有回绕规则，就把 `left == n` 映射到题目要求的位置。
- 复杂度：时间 `O(log n)`，空间 `O(1)`。

```cpp
class Solution {
public:
    int firstTrueTemplate(int n) {
        int left = 0;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (check(middle)) {
                right = middle; // middle 可能是第一个 true，保留。
            } else {
                left = middle + 1; // middle 是 false，直接排除。
            }
        }

        return left; // left == n 表示不存在 true。
    }

private:
    bool check(int index) {
        // 按题意定义 index 是否已经进入 true 区间。
        return true;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `704. Binary Search` | 待提交验证，源码逻辑检查通过 | 同时写出手写二分和 `lower_bound` 版本，半开区间更新正确。 | 公开函数当前调用库函数；训练时建议优先复盘手写区间语义。 | [查看](../leetcode-reviews/2026-05-22-704-binary-search.md) |
| `35. Search Insert Position` | 待提交验证，源码逻辑检查通过 | 准确抓住“第一个大于等于目标”的边界语义。 | 继续强调 `right = middle` 是保留可能答案，不是漏更新。 | [查看](../leetcode-reviews/2026-05-22-35-search-insert-position.md) |
| `744. Find Smallest Letter Greater Than Target` | 待提交验证，源码逻辑检查通过 | 正确使用 `upper_bound` 语义，并覆盖所有字符都不大于目标时的回绕。 | 重点对比 `>= target` 和 `> target` 的比较符差异。 | [查看](../leetcode-reviews/2026-05-22-744-find-smallest-letter-greater-than-target.md) |

- 暴露问题：今天整体开局很好，已经能把边界题归纳到 `lower_bound / upper_bound` 语义上。主要注意两点：第一，提交可以用库函数，但训练阶段要能手写并解释区间含义；第二，边界题真正的风险往往是比较符差一位，比如 `< target`、`<= target` 对应的答案语义完全不同。
- 下一步安排：进入第 2 天边界定位与近似答案。下一组题会继续放大“第一个满足条件的位置”和“整数范围内的近似返回值”，完成后重点复盘循环结束时 `left` 停在哪里。

## 进度更新 - 2026-05-23

- 今日完成：`278. First Bad Version`、`69. Sqrt(x)`、`34. Find First and Last Position of Element in Sorted Array`
- 当前主题：第 2 天 - 边界定位与近似答案

### 通用解题模板

- 适用条件：题目要求在有序区间、版本序列或整数答案范围中找到第一个满足条件的位置、最后一个可行值，或目标值出现的左右边界。
- 核心骨架：先把目标写成一个单调判断；找左边界时保留第一个可能答案，找右边界时可以转成“第一个超过目标的位置减一”，找最大可行值时可以记录 `ans` 后继续向右尝试。
- 关键边界：`check(mid) == true` 时是否保留 `mid` 取决于目标语义；返回 `left`、`left - 1` 还是记录的 `ans` 必须在写循环前确定；乘法判断要用 `long long` 防溢出。
- 复杂度：时间 `O(log n)` 或 `O(log x)`，空间 `O(1)`。

```cpp
class Solution {
public:
    int firstTrueLike(int n) {
        int left = 0;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (check(middle)) {
                right = middle; // middle 可能是第一个满足条件的位置。
            } else {
                left = middle + 1; // middle 及其左侧都可以排除。
            }
        }

        return left;
    }

    int lastFeasibleLike(int x) {
        int left = 0;
        int right = x;
        int ans = 0;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (feasible(middle)) {
                ans = middle; // 当前值可行，继续寻找更大的可行值。
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return ans;
    }

private:
    bool check(int index) {
        return true;
    }

    bool feasible(int value) {
        return true;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `278. First Bad Version` | 待提交验证，源码逻辑检查通过 | 闭区间写法稳定，`bad` 分支保留中点的边界意识正确。 | 复盘时重点解释为什么 `isBadVersion(mid)` 为真时不能丢掉 `mid`。 | [查看](../leetcode-reviews/2026-05-23-278-first-bad-version.md) |
| `69. Sqrt(x)` | 待提交验证，源码逻辑检查通过 | 能把整数平方根转成“第一个过大位置减一”，并用 `long long` 避免乘法溢出。 | 建议同时掌握记录 `ans` 的“最后可行值”写法，口述更直接。 | [查看](../leetcode-reviews/2026-05-23-69-sqrt-x.md) |
| `34. Find First and Last Position of Element in Sorted Array` | 待提交验证，源码逻辑检查通过 | 同时写出手写边界和标准库边界版本，左右边界语义清楚。 | `s1/s2` 可改成更语义化的函数名；训练时继续优先手写比较符。 | [查看](../leetcode-reviews/2026-05-23-34-find-first-and-last-position-of-element-in-sorted-array.md) |

- 暴露问题：今天整体已经能把三类边界统一到二分模板里；主要风险不在正确性，而在返回语义是否提前确定。`69` 的 `left - 1`、`34` 的 `upper_bound - 1`、`278` 的直接返回 `left`，都应该在写循环前说清楚。
- 下一步安排：进入第 3 天矩阵中的有序关系。重点从一维边界切换到二维位置映射和行列顺序判断，做题前先确认这个矩阵是否真的存在一条可二分的一维顺序。

## 第 3 天 - 矩阵中的有序关系

今天承接：第 2 天已经把一维边界和整数答案范围写稳，接下来要练习在二维结构里识别可利用的顺序关系。

1. `1351. Count Negative Numbers in a Sorted Matrix` (`简单`) - 先从每行/每列的顺序关系入手，练习减少无效检查。
2. `74. Search a 2D Matrix` (`中等`) - 训练把二维位置映射到一个连续搜索范围，并确认边界转换无误。
3. `240. Search a 2D Matrix II` (`中等`) - 对比整体有序与行列有序的区别，练习选择更合适的搜索起点。

完成后重点复盘：每题先判断“能不能把二维矩阵当成一维有序数组”，再决定用区间边界还是行列推进。

## 进度更新 - 2026-05-24

- 今日完成：`1351. Count Negative Numbers in a Sorted Matrix`、`74. Search a 2D Matrix`、`240. Search a 2D Matrix II`
- 当前主题：第 3 天 - 矩阵中的有序关系

### 通用解题模板

- 适用条件：题目给出二维矩阵，并且行、列或行与行之间存在明确顺序关系，可以用这些关系排除一整段位置。
- 核心骨架：先判断矩阵是否能整体映射成一维有序数组；如果可以，用一维下标二分并转换回行列；如果只是行列分别有序，优先从右上角或左下角出发，每步排除一行或一列。
- 关键边界：二维转一维时注意 `row = index / cols`、`col = index % cols`；阶梯搜索时必须选一个能同时比较“左侧更小、下方更大”或对称关系的角；空矩阵和单行单列要单独手推。
- 复杂度：一维映射二分为时间 `O(log(mn))`、空间 `O(1)`；阶梯搜索为时间 `O(m+n)`、空间 `O(1)`。

```cpp
class Solution {
public:
    bool flattenedBinarySearch(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int left = 0;
        int right = rows * cols - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            int row = middle / cols;
            int col = middle % cols;
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return false;
    }

    bool staircaseSearch(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int row = 0;
        int col = cols - 1;

        while (row < rows && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] > target) {
                --col; // 当前列可以排除。
            } else {
                ++row; // 当前行可以排除。
            }
        }

        return false;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `1351. Count Negative Numbers in a Sorted Matrix` | 待提交验证，源码逻辑检查通过 | 能利用行列单调性让列指针只左移不重置，达到 `O(m+n)`。 | 复盘时重点说清为什么下一行不需要重新从最右侧开始。 | [查看](../leetcode-reviews/2026-05-24-1351-count-negative-numbers-in-a-sorted-matrix.md) |
| `74. Search a 2D Matrix` | 待提交验证，源码逻辑检查通过 | 先找候选行再行内二分，边界检查完整。 | 变量名中 `m` 有遮蔽；建议掌握一维映射二分，模板更统一。 | [查看](../leetcode-reviews/2026-05-24-74-search-a-2-d-matrix.md) |
| `240. Search a 2D Matrix II` | 待提交验证，源码逻辑检查通过 | 正确从右上角开始，每一步排除一行或一列，复杂度最优。 | 重点对比第 74 题：这里不能直接拍平成一维有序数组。 | [查看](../leetcode-reviews/2026-05-24-240-search-a-2-d-matrix-ii.md) |

- 暴露问题：今天整体表现很稳，尤其 `1351` 和 `240` 都已经抓住右上角阶梯搜索的移动依据。主要复盘点是矩阵题的前置判断：第 `74` 题有全局一维顺序，第 `240` 题只有行列分别有序，不能把两者混成同一个模板。
- 下一步安排：进入第 4 天旋转与局部有序。下一组题会从二维顺序切换到一维数组里的局部有序结构，重点判断当前哪一半仍然有序，以及目标是否落在那一半。

## 第 4 天 - 旋转与局部有序

今天承接：第 3 天已经训练了二维结构中的排除方向，接下来要在一维数组里识别局部有序段和转折点。

1. `852. Peak Index in a Mountain Array` (`简单`) - 先练习在单峰结构中定位转折位置。
2. `153. Find Minimum in Rotated Sorted Array` (`中等`) - 练习在旋转后重新识别哪一侧仍可能包含最小值。
3. `33. Search in Rotated Sorted Array` (`中等`) - 在局部有序结构里查找目标，训练先判断有序半边再排除。

完成后重点复盘：每轮不要只看 `mid` 和 `target`，先判断 `[left, mid]` 或 `[mid, right]` 哪一侧有序，再决定目标是否落在可保留区间。

## 进度更新 - 2026-05-26

- 今日完成：`875. Koko Eating Bananas`、`1011. Capacity To Ship Packages Within D Days`、`1283. Find the Smallest Divisor Given a Threshold`
- 当前主题：第 5 天 - 答案范围与可行性检查

### 通用解题模板

- 适用条件：题目要求寻找最小或最大满足约束的整数答案，并且候选答案越大或越小，可行性呈单调变化。
- 核心骨架：先确定答案上下界；写一个 `check(answer)` 判断候选答案是否可行；如果要找最小可行值，`check(mid)` 为真时保留 `mid` 并收缩右边界，否则排除左侧。
- 关键边界：上下界必须保证答案存在；`check` 内部要尽早退出；涉及除法向上取整时优先使用 `(value + divisor - 1) / divisor`，避免浮点 `ceil`；累加可能变大时使用 `long long`。
- 复杂度：时间通常为 `O(n log R)`，空间 `O(1)`，其中 `R` 是答案范围大小。

```cpp
class Solution {
public:
    int minFeasibleAnswer(vector<int>& nums) {
        int left = lowerBound(nums);
        int right = upperBound(nums);

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (check(nums, middle)) {
                right = middle; // middle 可行，继续寻找更小可行答案。
            } else {
                left = middle + 1; // middle 不可行，答案只能更大。
            }
        }

        return left;
    }

private:
    bool check(vector<int>& nums, int candidate) {
        // 按题意模拟速度、容量、除数等候选答案是否满足约束。
        return true;
    }

    int lowerBound(vector<int>& nums) {
        return 1;
    }

    int upperBound(vector<int>& nums) {
        return *max_element(nums.begin(), nums.end());
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `875. Koko Eating Bananas` | 待提交验证，源码逻辑检查通过 | 正确把速度建模成最小可行答案，二分方向和提前退出都到位。 | 建议把浮点 `ceil` 改成整数上取整，避免精度和表达风险。 | [查看](../leetcode-reviews/2026-05-26-875-koko-eating-bananas.md) |
| `1011. Capacity To Ship Packages Within D Days` | 待提交验证，源码逻辑检查通过 | 上下界选择准确，`check` 能保持包裹顺序并模拟天数。 | 复盘时强调包裹不能重排；变量名可从剩余容量改成当前载重，语义更直观。 | [查看](../leetcode-reviews/2026-05-26-1011-capacity-to-ship-packages-within-d-days.md) |
| `1283. Find the Smallest Divisor Given a Threshold` | 待提交验证，源码逻辑检查通过 | 正确识别除数越大、结果和越小的单调性，边界合理。 | 与 `875` 同样建议使用整数上取整，并说清可行区间在右侧。 | [查看](../leetcode-reviews/2026-05-26-1283-find-the-smallest-divisor-given-a-threshold.md) |

- 暴露问题：今天三题共同模式很清晰，已经能把“速度 / 容量 / 除数”抽象成候选答案，并写出可行性检查。主要需要收束两个实现习惯：第一，整数题尽量不用浮点 `ceil`；第二，`check` 函数里要用语义化变量说明正在模拟的约束。
- 下一步安排：如果第 4 天 `852/153/33` 已经完成，建议先补第 4 天总结，保持周计划顺序完整；如果还没做，则先回补旋转与局部有序，再进入第 6 天峰值、分割与困难边界。

## 进度更新 - 2026-05-27

- 今日完成：`162. Find Peak Element`、`1901. Find a Peak Element II`、`4. Median of Two Sorted Arrays`
- 当前主题：第 6 天 - 峰值、分割与困难边界

### 通用解题模板

- 适用条件：题目不要求唯一答案，而是要求找到任意合法位置；当前位置和相邻位置之间存在“沿更大方向继续走，一定能到达某个合法答案”的结构。
- 核心骨架：保持一个答案必然存在的搜索区间；每轮观察中点和相邻位置的大小关系；如果右侧或下方更大，就向更大方向收缩，否则保留当前侧。
- 关键边界：用闭区间可以让 `middle + 1` 的访问由 `left < right` 保证；二维题先取当前行或列的最大值，用它消掉另一个方向的邻居风险；困难题如果不共享这个峰值结构，应单独复盘，不强行套模板。
- 复杂度：一维峰值为时间 `O(log n)`、空间 `O(1)`；二维峰值按行二分为时间 `O(cols log rows)`、空间 `O(1)`。

```cpp
class Solution {
public:
    int peakLikeTemplate(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle; // 当前侧仍保证存在一个合法峰值。
            } else {
                left = middle + 1; // 沿上升方向继续，右侧必有峰值。
            }
        }

        return left;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `162. Find Peak Element` | 待提交验证，源码逻辑检查通过 | 能识别任意峰值即可，不执着于全局最大值；方向判断正确。 | 当前 `check` 分支较多，建议收束成只比较 `mid` 与 `mid + 1` 的闭区间写法。 | [查看](../leetcode-reviews/2026-05-27-162-find-peak-element.md) |
| `1901. Find a Peak Element II` | 待提交验证，源码逻辑检查通过 | 正确先取中间行最大值，再根据上下邻居决定行区间收缩方向。 | 复盘时重点说明为什么行最大值已经覆盖左右邻居，不需要再单独比较。 | [查看](../leetcode-reviews/2026-05-27-1901-find-a-peak-element-ii.md) |
| `4. Median of Two Sorted Arrays` | 未完成，已补最优解用于复盘 | 题目骨架已建立，适合单独拆出 `kth` 子问题训练。 | 原公开函数为空；这题不要套峰值模板，要单独练习两个有序序列间排除候选段。 | [查看](../leetcode-reviews/2026-05-27-4-median-of-two-sorted-arrays.md) |

- 暴露问题：`162` 和 `1901` 的峰值方向感已经建立，主要需要把“沿更大方向一定存在答案”沉淀成更简洁的闭区间不变量；`4` 仍是困难边界的短板，当前需要先能稳定写出第 `k` 小元素的排除逻辑。
- 下一步安排：建议先重写 `4` 的 `getKth`，再进入第 7 天综合复盘。第 7 天从 `540` 恢复较轻二分边界，再做 `658` 和 `981` 的迁移题。
