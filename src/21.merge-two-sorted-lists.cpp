/*
 * @lc app=leetcode.cn id=21 lang=cpp
 * @lcpr version=30204
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoListsOpt(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // 其中一条链表剩余部分本来就是有序的，直接接到结果尾部。
        tail->next = (list1 != nullptr) ? list1 : list2;
        return dummy.next;
    }

public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();
        ListNode *t = dummy;
        ListNode *p = list1, *q = list2;
        while(p != nullptr || q != nullptr) {
            if(p == nullptr) {
                t->next = q;
                q = q->next;
                t = t->next;
            } else if(q == nullptr) {
                t->next = p;
                p = p->next;
                t = t->next;
            } else {
                if(p->val < q->val) {
                    t->next = p;
                    p = p->next;
                    t = t->next;
                } else {
                    t->next = q;
                    q = q->next;
                    t = t->next;
                }
            }
        }
        ListNode *res = dummy->next;
        delete dummy;
        return res;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,4]\n[1,3,4]\n
// @lcpr case=end

// @lcpr case=start
// []\n[]\n
// @lcpr case=end

// @lcpr case=start
// []\n[0]\n
// @lcpr case=end

 */

