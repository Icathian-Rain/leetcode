/*
 * @lc app=leetcode.cn id=876 lang=cpp
 * @lcpr version=30204
 *
 * [876] 链表的中间结点
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
    ListNode* middleNodeOpt(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            // fast 每次走两步，slow 每次走一步；偶数长度时 slow 正好停在第二个中点。
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

public:
    pair<ListNode* ,int> dfs(ListNode* head, int preCnt) {
        if(head == nullptr) return {nullptr, 0};
        auto [ans, nxtCnt] = dfs(head->next, preCnt+1);
        if((preCnt == nxtCnt) || (preCnt == nxtCnt+1)) {
            return {head, nxtCnt+1};
        } else {
            return {ans, nxtCnt+1};
        }
    }


    ListNode* middleNode(ListNode* head) {
        auto [ans, cnt] = dfs(head, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5,6]\n
// @lcpr case=end

 */

