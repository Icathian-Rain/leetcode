/*
 * @lc app=leetcode.cn id=206 lang=cpp
 * @lcpr version=30204
 *
 * [206] 反转链表
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
    ListNode* reverseListOpt(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            // 先保存后续入口，再改写 current->next，避免丢失剩余链表。
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }

public:
    ListNode* s1(ListNode* head) {
        // 迭代方法
        ListNode *cur = head, *pre = nullptr;
        while(cur != nullptr) {
            ListNode *tmp = cur->next;
            cur->next = pre;

            pre = cur;
            cur = tmp;
        }
        return pre;


    }

    ListNode* s2(ListNode* head) {
        // 递归方法
        if(head == nullptr) return nullptr;
        if(head->next == nullptr) return head;

        ListNode *nxt = s2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return nxt;




    }
    ListNode* reverseList(ListNode* head) {
        // return s1(head);
        return s2(head);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

