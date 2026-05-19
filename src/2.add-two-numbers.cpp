/*
 * @lc app=leetcode.cn id=2 lang=cpp
 * @lcpr version=30204
 *
 * [2] 两数相加
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
    ListNode* addTwoNumbersOpt(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            // 每轮只生成当前位节点，carry 保存下一位进位。
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
            carry = sum / 10;
        }

        return dummy.next;
    }

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p=l1, *q=l2;
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        int plus=0;
        while(p!=nullptr && q!=nullptr) {
            int sum=p->val+q->val+plus;
            tail->next = new ListNode(sum%10);
            plus = sum/10;

            p = p->next;
            q = q->next;
            tail = tail->next;
        }

        if(p == nullptr) {
            p = q;
        }

        while(p != nullptr) {
            int sum=p->val+plus;
            tail->next = new ListNode(sum%10);
            plus = sum/10;

            p=p->next;
            tail = tail->next;
        }

        if(plus != 0) {
            tail->next = new ListNode(plus);
        }

        return dummy.next;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,4,3]\n[5,6,4]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n[0]\n
// @lcpr case=end

// @lcpr case=start
// [9,9,9,9,9,9,9]\n[9,9,9,9]\n
// @lcpr case=end

// @lcpr case=start
// [1,8]\n[0]
// @lcpr case=end
 */
