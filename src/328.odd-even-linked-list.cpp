/*
 * @lc app=leetcode.cn id=328 lang=cpp
 * @lcpr version=30204
 *
 * [328] 奇偶链表
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
    ListNode* oddEvenListOpt(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* oddTail = head;
        ListNode* evenHead = head->next;
        ListNode* evenTail = evenHead;

        while (evenTail != nullptr && evenTail->next != nullptr) {
            // oddTail 维护奇数位置尾部，evenTail 维护偶数位置尾部。
            oddTail->next = evenTail->next;
            oddTail = oddTail->next;
            evenTail->next = oddTail->next;
            evenTail = evenTail->next;
        }

        oddTail->next = evenHead;
        return head;
    }

public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode odd, even;
        ListNode*p = &odd, *q=&even;
        ListNode*cur = head;
        int idx = 1;
        while(cur != nullptr) {
            if(idx %2 == 1) {
                p->next = cur;
                p=p->next;
            } else {
                q->next = cur;
                q=q->next;
            }
            cur = cur->next;
            idx++;
        }

        p->next = even.next;
        q->next = nullptr;

        return odd.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [2,1,3,5,6,4,7]\n
// @lcpr case=end

 */
