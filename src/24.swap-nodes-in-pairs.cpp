/*
 * @lc app=leetcode.cn id=24 lang=cpp
 * @lcpr version=30204
 *
 * [24] 两两交换链表中的节点
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
    ListNode* swapPairsOpt(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;

        while (previous->next != nullptr && previous->next->next != nullptr) {
            ListNode* first = previous->next;
            ListNode* second = first->next;
            ListNode* nextPair = second->next;

            // previous 始终指向当前二元组前驱，重接后 first 成为下一组前驱。
            previous->next = second;
            second->next = first;
            first->next = nextPair;
            previous = first;
        }

        return dummy.next;
    }

public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(-1, head);
        ListNode*pre = &dummy, *cur = head;
        while(cur != nullptr && cur->next != nullptr) {
            ListNode* nxt = cur->next->next;
            pre->next = cur->next;
            pre->next->next = cur;
            cur->next = nxt;
            pre = cur;
            cur = pre->next;
        }
        return dummy.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

