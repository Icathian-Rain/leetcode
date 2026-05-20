/*
 * @lc app=leetcode.cn id=61 lang=cpp
 * @lcpr version=30204
 *
 * [61] 旋转链表
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
    ListNode* rotateRightOpt(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }

        int length = 1;
        ListNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
            ++length;
        }

        int shift = k % length;
        if (shift == 0) {
            return head;
        }

        int stepsToNewTail = length - shift - 1;
        ListNode* newTail = head;
        for (int i = 0; i < stepsToNewTail; ++i) {
            newTail = newTail->next;
        }

        ListNode* newHead = newTail->next;
        tail->next = head;       // 先把首尾接成环，再从新尾部切开。
        newTail->next = nullptr;
        return newHead;
    }

public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        ListNode*p = head;
        ListNode*tail;
        int len=0;
        while(p!=nullptr) {
            len++;
            if(p->next == nullptr) {
                tail = p;
            }
            p=p->next;

        }
        k = k%len;
        if(k == 0) return head;

        tail->next = head;
        int t = len-k;
        p = head;
        for(int i=0; i<t-1; i++) {
            p = p->next;
        }
        ListNode*ans = p->next;
        p->next = nullptr;
        return ans;




    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [0,1,2]\n4\n
// @lcpr case=end

 */
