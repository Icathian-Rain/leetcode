/*
 * @lc app=leetcode.cn id=138 lang=cpp
 * @lcpr version=30204
 *
 * [138] 随机链表的复制
 */


// @lcpr-template-start
#include <unordered_map>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
// @lcpr-template-end
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
    Node* copyRandomListOpt(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* current = head;
        while (current != nullptr) {
            Node* copied = new Node(current->val);
            copied->next = current->next;
            current->next = copied;
            current = copied->next;
        }

        current = head;
        while (current != nullptr) {
            if (current->random != nullptr) {
                // 新节点紧跟在旧节点后面，旧 random 的 next 就是对应新 random。
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }

        Node* copiedHead = head->next;
        current = head;
        while (current != nullptr) {
            Node* copied = current->next;
            current->next = copied->next;
            copied->next = (copied->next == nullptr) ? nullptr : copied->next->next;
            current = current->next;
        }

        return copiedHead;
    }

public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;
        Node dummy(-1);
        Node*pre = &dummy, *cur = head;
        while(cur != nullptr) {
            Node* newNode = new Node(cur->val);
            mp[cur] = newNode;

            pre->next = newNode;
            pre = pre->next;
            cur = cur->next;
        }

        pre = &dummy, cur = head;
        while(cur != nullptr) {
            if(mp.find(cur->random) != mp.end()) {
                pre->next->random = mp[cur->random];
            }
            pre = pre->next;
            cur = cur->next;
        }
        return dummy.next;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [[7,null],[13,0],[11,4],[10,2],[1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1],[2,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[3,null],[3,0],[3,null]]\n
// @lcpr case=end

 */
