/*
 * @lc app=leetcode.cn id=86 lang=cpp
 * @lcpr version=30204
 *
 * [86] 分隔链表
 */
// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    ListNode* partitionOpt(ListNode* head, int x) {
        ListNode beforeDummy(0);
        ListNode afterDummy(0);
        ListNode* beforeTail = &beforeDummy;
        ListNode* afterTail = &afterDummy;

        while (head != nullptr) {
            ListNode* nextNode = head->next;
            head->next = nullptr; // 先断开旧连接，避免分区后尾部残留。

            if (head->val < x) {
                beforeTail->next = head;
                beforeTail = head;
            } else {
                afterTail->next = head;
                afterTail = head;
            }

            head = nextNode;
        }

        beforeTail->next = afterDummy.next;
        return beforeDummy.next;
    }

public:
    ListNode* partition(ListNode* head, int x) {
        ListNode low, high;
        ListNode*p = &low, *q=&high;
        ListNode*cur = head;
        while(cur != nullptr) {
            if(cur->val < x) {
                p->next = cur;
                p=p->next;
            } else {
                q->next = cur;
                q=q->next;
            }
            cur = cur->next;
        }

        p->next = high.next;
        q->next = nullptr;

        return low.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,4,3,2,5,2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [2,1]\n2\n
// @lcpr case=end

 */
