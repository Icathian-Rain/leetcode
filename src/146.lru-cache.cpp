/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * @lcpr version=30204
 *
 * [146] LRU 缓存
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    unordered_map<int, DLinkedNode*> mp;
    DLinkedNode* head;
    DLinkedNode* tail;
    int cap;
    int size;

    void detachOpt(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void pushFrontOpt(DLinkedNode* node) {
        // head 和 tail 是哨兵节点，真实最近使用节点始终放在 head 后。
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    DLinkedNode* popBackOpt() {
        DLinkedNode* node = tail->prev;
        detachOpt(node);
        return node;
    }

    int getOpt(int key) {
        auto it = mp.find(key);
        if (it == mp.end()) {
            return -1;
        }

        DLinkedNode* node = it->second;
        detachOpt(node);
        pushFrontOpt(node);
        return node->value;
    }

    void putOpt(int key, int value) {
        auto it = mp.find(key);
        if (it != mp.end()) {
            DLinkedNode* node = it->second;
            node->value = value;
            detachOpt(node);
            pushFrontOpt(node);
            return;
        }

        DLinkedNode* node = new DLinkedNode(key, value);
        mp[key] = node;
        pushFrontOpt(node);
        ++size;

        if (size > cap) {
            DLinkedNode* removed = popBackOpt();
            mp.erase(removed->key);
            delete removed;
            --size;
        }
    }

public:
    LRUCache(int capacity) {
        cap=capacity;
        size=0;
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(mp.find(key) == mp.end()) return -1;
        auto p=mp[key];
        moveTohead(p);
        return p->value;
    }

    void put(int key, int value) {
        if(mp.find(key) == mp.end()) {
            // 不存在
            DLinkedNode*p = new DLinkedNode(key, value);
            mp[key]=p;
            addTohead(p);
            size++;
            if(size > cap) {
                DLinkedNode* toremove = removeTail();
                mp.erase(toremove->key);
                delete toremove;
                size--;
            }
        } else {
            auto p=mp[key];
            p->value = value;
            moveTohead(p);
        }
    }

    void removeNode(DLinkedNode* p) {
        auto pre = p->prev;
        auto nxt = p->next;
        pre->next = nxt;
        nxt->prev = pre;
    }

    void addTohead(DLinkedNode *p) {
        p->next = head->next;
        head->next->prev = p;
        head->next = p;
        p->prev = head;
    }

    void moveTohead(DLinkedNode* p) {
        removeNode(p);
        addTohead(p);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* p=tail->prev;
        removeNode(p);
        return p;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
