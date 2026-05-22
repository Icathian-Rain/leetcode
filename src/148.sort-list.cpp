/*
 * @lc app=leetcode.cn id=148 lang=cpp
 * @lcpr version=30204
 *
 * [148] 排序链表
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
    ListNode* splitOpt(ListNode* head, int size) {
        for (int i = 1; head != nullptr && i < size; ++i) {
            head = head->next;
        }

        if (head == nullptr) {
            return nullptr;
        }

        ListNode* second = head->next;
        head->next = nullptr; // 切断前一段，避免合并时串回旧链表。
        return second;
    }

    ListNode* mergeSortedListsOpt(ListNode* first, ListNode* second) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (first != nullptr && second != nullptr) {
            if (first->val <= second->val) {
                tail->next = first;
                first = first->next;
            } else {
                tail->next = second;
                second = second->next;
            }
            tail = tail->next;
        }

        tail->next = (first != nullptr) ? first : second;
        return dummy.next;
    }

    ListNode* sortListOpt(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        int length = 0;
        for (ListNode* node = head; node != nullptr; node = node->next) {
            ++length;
        }

        ListNode dummy(0, head);
        for (int step = 1; step < length; step <<= 1) {
            ListNode* current = dummy.next;
            ListNode* tail = &dummy;

            while (current != nullptr) {
                ListNode* left = current;
                ListNode* right = splitOpt(left, step);
                current = splitOpt(right, step);

                // 每轮合并两个长度最多为 step 的有序段。
                tail->next = mergeSortedListsOpt(left, right);
                while (tail->next != nullptr) {
                    tail = tail->next;
                }
            }
        }

        return dummy.next;
    }

public:
    ListNode* sortList(ListNode* head) {
        vector<int> arr;
        ListNode* p=head;
        while(p != nullptr) {
            arr.push_back(p->val);
            p=p->next;
        }
        sort(arr.begin(), arr.end());
        int n=arr.size();
        p = head;
        for(int i=0; i<n; i++, p=p->next) {
            p->val = arr[i];
        }
        return head;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,2,1,3]\n
// @lcpr case=end

// @lcpr case=start
// [-1,5,3,4,0]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */
