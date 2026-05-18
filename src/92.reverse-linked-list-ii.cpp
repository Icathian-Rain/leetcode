/*
 * @lc app=leetcode.cn id=92 lang=cpp
 * @lcpr version=30204
 *
 * [92] 反转链表 II
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
    ListNode* reverseBetweenOpt(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        ListNode* beforeLeft = &dummy;

        for (int i = 1; i < left; ++i) {
            beforeLeft = beforeLeft->next;
        }

        ListNode* sublistTail = beforeLeft->next;
        for (int i = 0; i < right - left; ++i) {
            // 每轮把 sublistTail 后面的节点搬到区间头部，区间尾部始终由 sublistTail 承接。
            ListNode* moving = sublistTail->next;
            sublistTail->next = moving->next;
            moving->next = beforeLeft->next;
            beforeLeft->next = moving;
        }

        return dummy.next;
    }

public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(-1, head);

        ListNode*pre = &dummy, *cur = head;
        ListNode*leftTail = pre;
        for(int i=1; i<=right; i++) {
            if(i < left) {
                pre = pre->next;
                cur = cur->next;
                leftTail = leftTail->next;
            } else {
                ListNode* nxt = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nxt;
            }
            
        }
        leftTail->next->next=cur;
        leftTail->next = pre;
        return dummy.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n4\n
// @lcpr case=end

// @lcpr case=start
// [5]\n1\n1\n
// @lcpr case=end

 */

