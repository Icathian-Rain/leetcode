#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
private:
    pair<ListNode*, ListNode*> reverseClosed(ListNode* head, ListNode* afterTail) {
        ListNode* previous = afterTail;
        ListNode* current = head;
        while (current != afterTail) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        return {previous, head}; // previous 是新头，head 变成新尾。
    }

public:
    ListNode* reverseKGroupLike(ListNode* head, int k) {
        if (k <= 1) {
            return head;
        }

        ListNode dummy(0, head);
        ListNode* beforeGroup = &dummy;

        while (true) {
            ListNode* groupTail = beforeGroup;
            for (int i = 0; i < k && groupTail != nullptr; ++i) {
                groupTail = groupTail->next;
            }
            if (groupTail == nullptr) {
                break;
            }

            ListNode* groupHead = beforeGroup->next;
            ListNode* afterGroup = groupTail->next;
            auto [newHead, newTail] = reverseClosed(groupHead, afterGroup);

            beforeGroup->next = newHead;
            beforeGroup = newTail;
        }

        return dummy.next;
    }
};

static ListNode* buildList(initializer_list<int> values) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int value : values) {
        tail->next = new ListNode(value);
        tail = tail->next;
    }
    return dummy.next;
}

static void printList(ListNode* head) {
    for (ListNode* current = head; current != nullptr; current = current->next) {
        cout << current->val;
        if (current->next != nullptr) {
            cout << " -> ";
        }
    }
    cout << '\n';
}

int main() {
    Solution solution;

    ListNode* first = buildList({1, 2, 3, 4, 5});
    cout << "reverseKGroupLike([1,2,3,4,5], 2) = ";
    printList(solution.reverseKGroupLike(first, 2)); // 期望输出：2 -> 1 -> 4 -> 3 -> 5

    ListNode* second = buildList({1, 2, 3, 4, 5});
    cout << "reverseKGroupLike([1,2,3,4,5], 3) = ";
    printList(solution.reverseKGroupLike(second, 3)); // 期望输出：3 -> 2 -> 1 -> 4 -> 5

    return 0;
}
