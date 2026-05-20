/*
 * @lc app=leetcode.cn id=25 lang=cpp
 * @lcpr version=30204
 *
 * [25] K 个一组翻转链表
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
using pll=pair<ListNode*, ListNode*>;
class Solution {
    pll reverseSegmentOpt(ListNode* head, ListNode* tail) {
        ListNode* afterTail = tail->next;
        ListNode* previous = afterTail;
        ListNode* current = head;

        while (previous != tail) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return {tail, head};
    }

    ListNode* reverseKGroupOpt(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* beforeGroup = &dummy;

        while (head != nullptr) {
            ListNode* tail = beforeGroup;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr) {
                    return dummy.next;
                }
            }

            ListNode* afterGroup = tail->next;
            // 只反转 [head, tail]，afterGroup 始终作为下一段入口保留。
            tie(head, tail) = reverseSegmentOpt(head, tail);
            beforeGroup->next = head;
            tail->next = afterGroup;

            beforeGroup = tail;
            head = afterGroup;
        }

        return dummy.next;
    }

public:

    pll reverseList(ListNode* head, ListNode* tail) {
        ListNode*pre = nullptr;
        ListNode*cur = head;
        while(cur != nullptr) {
            ListNode* nxt=cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return {tail, head};

    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(-1, head);
        ListNode*pre = &dummy, *cur=head;
        while(cur != nullptr) {
            ListNode*tail = pre;
            for(int i=0; i<k; i++) {
                tail = tail->next;
                if(tail == nullptr) {
                    return dummy.next;
                }
            }
            ListNode*nxt = tail->next;

            pre->next = nullptr;
            tail->next = nullptr;

            tie(cur, tail) = reverseList(cur, tail);

            pre->next = cur;
            tail->next = nxt;

            pre = tail;
            cur = nxt;
        }
        return dummy.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n3\n
// @lcpr case=end

 */
