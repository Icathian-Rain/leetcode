/*
 * @lc app=leetcode.cn id=82 lang=cpp
 * @lcpr version=30204
 *
 * [82] 删除排序链表中的重复元素 II
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
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            bool duplicated = false;
            while (current->next != nullptr && current->val == current->next->val) {
                duplicated = true;
                current = current->next;
            }

            if (duplicated) {
                // current 已停在重复段最后一个节点，previous 直接接到重复段之后。
                previous->next = current->next;
            } else {
                previous = previous->next;
            }

            current = current->next;
        }

        return dummy.next;
    }

public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-1, head);
        ListNode*pre = &dummy, *cur=head;
        while(cur != nullptr && cur->next != nullptr) {
            if(cur->val == cur->next->val) {
                int val = cur->val;
                ListNode* p=cur->next->next;
                delete cur->next;
                delete cur;
                while(p != nullptr && p->val == val) {
                    ListNode* tmp=p->next;
                    delete p;
                    p = tmp;
                }
                pre->next = p;
                cur = p;
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
// [1,2,3,3,4,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,1,2,3]\n
// @lcpr case=end

 */
