/*
 * @lc app=leetcode.cn id=203 lang=cpp
 * @lcpr version=30204
 *
 * [203] 移除链表元素
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
    ListNode* removeElementsOpt(ListNode* head, int val) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            if (current->val == val) {
                // 删除当前节点时 previous 不动，继续承接后续可能被删除的节点。
                previous->next = nextNode;
            } else {
                previous = current;
            }
            current = nextNode;
        }

        return dummy.next;
    }

public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(-1, head);
        ListNode* pre = &dummy, *cur = head;
        while(cur != nullptr) {
            if(cur->val == val) {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
            } else {
                pre = pre->next;
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,6,3,4,5,6]\n6\n
// @lcpr case=end

// @lcpr case=start
// []\n1\n
// @lcpr case=end

// @lcpr case=start
// [7,7,7,7]\n7\n
// @lcpr case=end

 */

