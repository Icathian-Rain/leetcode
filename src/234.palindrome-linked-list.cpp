/*
 * @lc app=leetcode.cn id=234 lang=cpp
 * @lcpr version=30204
 *
 * [234] 回文链表
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
    ListNode* reverseListForPalindrome(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }

    bool isPalindromeOpt(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            // slow 停在前半段尾部，便于反转后半段并在结束后接回。
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* secondHalfHead = reverseListForPalindrome(slow->next);
        ListNode* first = head;
        ListNode* second = secondHalfHead;
        bool matched = true;

        while (matched && second != nullptr) {
            if (first->val != second->val) {
                matched = false;
            }
            first = first->next;
            second = second->next;
        }

        slow->next = reverseListForPalindrome(secondHalfHead);
        return matched;
    }

public:
    ListNode *pri;

    bool check(ListNode* cur) {
        if(cur == nullptr) return true;
        bool flag = check(cur->next);
        if(flag == false) {
            return false;
        }

        if(cur->val != pri->val) return false;
        pri = pri->next;
        return true;
    }

    bool isPalindrome(ListNode* head) {
        pri = head;
        return check(head);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n
// @lcpr case=end

 */

