/*
 * @lc app=leetcode.cn id=83 lang=cpp
 * @lcpr version=30204
 *
 * [83] 删除排序链表中的重复元素
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
    ListNode* deleteDuplicatesOpt(ListNode* head) {
        ListNode* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                // 有序链表中重复节点相邻，直接跳过后一个重复节点。
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }

        return head;
    }

public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dummy = new ListNode(-101, head);
        ListNode *cur = head, *pre = dummy;
        while(cur != nullptr) {
            ListNode* nxt = cur->next;
            if(cur->val == pre->val) {
                pre->next = nxt;
                delete cur;

                cur = nxt;
            } else {
                pre = cur;
                cur = nxt;
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
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2,3,3]\n
// @lcpr case=end

 */

