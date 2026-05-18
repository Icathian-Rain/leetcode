/*
 * @lc app=leetcode.cn id=143 lang=cpp
 * @lcpr version=30204
 *
 * [143] 重排链表
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
    ListNode* firstHalfTailOpt(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverseListOpt(ListNode* head) {
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

    void mergeAlternatingOpt(ListNode* first, ListNode* second) {
        while (second != nullptr) {
            ListNode* nextFirst = first->next;
            ListNode* nextSecond = second->next;

            // second 已是反转后的后半段头部，交替插入到 first 后面。
            first->next = second;
            second->next = nextFirst;
            first = nextFirst;
            second = nextSecond;
        }
    }

    void reorderListOpt(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        ListNode* firstTail = firstHalfTailOpt(head);
        ListNode* secondHead = reverseListOpt(firstTail->next);
        firstTail->next = nullptr; // 先切断两段，避免合并时尾部残留形成环。
        mergeAlternatingOpt(head, secondHead);
    }

public:
    ListNode* middleList(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverse(ListNode *head) {
        ListNode* pre =nullptr;
        ListNode* cur = head;
        while(cur != nullptr) {
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }

    void mergeList(ListNode* h1, ListNode* h2) {
        ListNode* p1=h1, *p2 = h2;

        while(p1 != nullptr && p2!= nullptr) {
            ListNode* nxt1 = p1->next;
            ListNode* nxt2 = p2->next;
            
            p1->next = p2;
            p1 = nxt1;

            p2->next = nxt1;
            p2 = nxt2;
        }
    }


    void reorderList(ListNode* head) {
        if(head == nullptr) return ;
        ListNode* mid = middleList(head);
        ListNode* h1 = head;
        ListNode* h2 = mid->next;
        mid->next = nullptr;
        h2 = reverse(h2);
        mergeList(h1, h2);
        return ;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

 */

