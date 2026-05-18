/*
 * @lc app=leetcode.cn id=160 lang=cpp
 * @lcpr version=30204
 *
 * [160] 相交链表
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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode *getIntersectionNodeOpt(ListNode *headA, ListNode *headB) {
        ListNode* pointerA = headA;
        ListNode* pointerB = headB;

        while (pointerA != pointerB) {
            // 两个指针分别走完 A+B 和 B+A，长度差会被第二段路径抵消。
            pointerA = (pointerA == nullptr) ? headB : pointerA->next;
            pointerB = (pointerB == nullptr) ? headA : pointerB->next;
        }

        return pointerA;
    }

public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB=0;
        ListNode *p = headA, *q = headB;
        while(p!=nullptr) {
            p = p->next;
            lenA++;
        }
        while(q!=nullptr) {
            q = q->next;
            lenB++;
        }

        p = headA;
        q = headB;
        if(lenA < lenB) {
            for(int i=0; i<(lenB - lenA); i++) {
                q=q->next;
            }
        } else {
            for(int i=0; i<(lenA - lenB); i++) {
                p=p->next;
            }
        }

        while(p!=nullptr && q!=nullptr) {
            if(p == q) return p;
            p = p->next;
            q = q->next;
        }
        return nullptr;




    }
};
// @lc code=end



/*
// @lcpr case=start
// 8\n[4,1,8,4,5]\n[5,6,1,8,4,5]\n2\n3\n
// @lcpr case=end

// @lcpr case=start
// 2\n[1,9,1,2,4]\n[3,2,4]\n3\n1\n
// @lcpr case=end

// @lcpr case=start
// 0\n[2,6,4]\n[1,5]\n3\n2\n
// @lcpr case=end

 */

