# 题解点评 - 622. Design Circular Queue

## 基本信息

- 日期：2026-05-14
- 主题：栈与队列 - 队列窗口与模拟面试
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/622.design-circular-queue.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用固定长度数组 `q` 保存队列元素。
2. `front` 表示当前队首下标，`rear` 表示下一个可写入位置。
3. `sz` 表示当前元素个数，`capacity` 表示容量。
4. 入队时先判断是否已满，把值写到 `rear`，再让 `rear` 环形右移。
5. 出队时先判断是否为空，再让 `front` 环形右移。
6. 查询队尾时，因为 `rear` 是下一个可写位置，所以真实队尾是 `(rear - 1 + capacity) % capacity`。

## 用户解法复杂度

- 每个接口时间复杂度：`O(1)`
- 空间复杂度：`O(k)`
- 复杂度来源：固定数组保存最多 `k` 个元素，所有操作只更新常数个变量。

## 用户代码注释版

```cpp
class MyCircularQueue {
public:
    vector<int> q;
    int front;    // 当前队首位置。
    int rear;     // 下一个可写入位置，不是当前队尾。
    int sz;
    int capacity;

    MyCircularQueue(int k) {
        front = 0;
        rear = 0;
        sz = 0;
        capacity = k;
        q.resize(capacity);
    }

    bool enQueue(int value) {
        if(sz == capacity) {
            return false;
        }
        q[rear] = value;
        rear = (rear+1)%capacity;
        sz++;
        return true;
    }

    bool deQueue() {
        if(sz == 0) return false;
        front = (front+1)%capacity;
        sz--;
        return true;
    }

    int Front() {
        if(sz == 0) return -1;
        return q[front];
    }

    int Rear() {
        if(sz == 0) return -1;
        return q[(rear-1+capacity)%capacity];
    }

    bool isEmpty() {
        return sz == 0;
    }

    bool isFull() {
        return sz == capacity;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 指针语义 | `rear` 定义为下一个可写位置。 | 正确，入队逻辑自然。 | 复盘时明确 `Rear()` 不能直接返回 `q[rear]`。 |
| 空满判断 | 使用 `sz` 区分空和满。 | 避免牺牲一个数组空位，容量利用完整。 | 设计题中 `size` 是最直观稳妥的方案。 |
| 环形移动 | 使用取模处理首尾回绕。 | 能稳定处理多次入队出队。 | 手推容量为 3 的满、空、回绕序列。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 接口完整，`rear` 语义和取模处理正确。 | 需要一直记住 `rear` 是下一个写入位置。 | 适合直接提交。 |
| 推荐最优解 | 用 `front + size` 计算写入和队尾位置，只维护一个首指针。 | 需要理解下标公式。 | 适合减少一个 `rear` 状态。 |

## 最优解法

1. 用数组保存固定容量元素。
2. 维护 `front` 和 `size`。
3. 入队位置为 `(front + size) % capacity`。
4. 出队时移动 `front` 并减少 `size`。
5. 队尾位置为 `(front + size - 1) % capacity`。

- 最优单接口时间复杂度：`O(1)`
- 最优空间复杂度：`O(k)`

### 最优解代码

```cpp
class MyCircularQueue {
    vector<int> data;
    int frontIndex = 0;
    int currentSize = 0;
    int capacity = 0;

public:
    MyCircularQueue(int k) : data(k), capacity(k) {
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        int rearIndex = (frontIndex + currentSize) % capacity;
        data[rearIndex] = value;
        ++currentSize;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        frontIndex = (frontIndex + 1) % capacity;
        --currentSize;
        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[frontIndex];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        // rear 是最后一个有效元素，而不是下一个可写位置。
        return data[(frontIndex + currentSize - 1) % capacity];
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `front/rear/sz/capacity`。 | `front/size/capacity`。 | 两种都正确，少维护一个派生状态会更不容易错。 |
| 更新逻辑 | 入队移动 `rear`，出队移动 `front`。 | 入队通过公式计算写入位置，出队移动 `front`。 | 推荐理解两种 rear 语义。 |
| 边界处理 | 空、满、回绕都覆盖。 | 同样覆盖。 | 当前实现稳定。 |
| 复杂度 | `O(1)` / `O(k)` | `O(1)` / `O(k)` | 已达到最优。 |

## 下一步建议

进入窗口最大值。循环队列这题的重点不是算法难度，而是每个变量的语义必须始终一致。

## 后续练习

1. `239. Sliding Window Maximum` - 继续使用双端队列维护窗口候选。
2. `641. Design Circular Deque` - 同类设计题，加入双端操作。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/622.design-circular-queue.cpp`
- 新函数名：`enQueueOpt`、`deQueueOpt`、`FrontOpt`、`RearOpt`、`isEmptyOpt`、`isFullOpt`
- 保留用户原实现：是
