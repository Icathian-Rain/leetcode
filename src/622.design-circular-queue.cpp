/*
 * @lc app=leetcode.cn id=622 lang=cpp
 * @lcpr version=30204
 *
 * [622] 设计循环队列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class MyCircularQueue {

public:
    vector<int> q;
    int front;
    int rear;
    int sz;
    int capacity;
    vector<int> qOpt;
    int frontOpt;
    int sizeOpt;
    int capacityOpt;
    MyCircularQueue(int k) {
        front = 0;
        rear = 0;
        sz = 0;
        capacity = k;
        q.resize(capacity);
        frontOpt = 0;
        sizeOpt = 0;
        capacityOpt = k;
        qOpt.resize(capacityOpt);
    }

    bool enQueueOpt(int value) {
        if(sizeOpt == capacityOpt) {
            return false;
        }
        int rearIndex = (frontOpt + sizeOpt) % capacityOpt;
        qOpt[rearIndex] = value;
        sizeOpt++;
        return true;
    }

    bool deQueueOpt() {
        if(sizeOpt == 0) {
            return false;
        }
        frontOpt = (frontOpt + 1) % capacityOpt;
        sizeOpt--;
        return true;
    }

    int FrontOpt() {
        if(sizeOpt == 0) {
            return -1;
        }
        return qOpt[frontOpt];
    }

    int RearOpt() {
        if(sizeOpt == 0) {
            return -1;
        }
        // rear 是最后一个有效元素，而不是下一个可写位置。
        return qOpt[(frontOpt + sizeOpt - 1) % capacityOpt];
    }

    bool isEmptyOpt() {
        return sizeOpt == 0;
    }

    bool isFullOpt() {
        return sizeOpt == capacityOpt;
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

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
// @lc code=end



