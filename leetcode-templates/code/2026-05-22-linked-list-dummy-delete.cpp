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
public:
    ListNode* removeValue(ListNode* head, int value) {
        ListNode dummy(0, head);
        ListNode* previous = &dummy;
        ListNode* current = head;

        while (current != nullptr) {
            if (current->val == value) {
                previous->next = current->next; // 删除时 previous 不动，继续检查新后继。
            } else {
                previous = current;
            }
            current = previous->next;
        }

        return dummy.next;
    }

    ListNode* deleteDuplicatesKeepOne(ListNode* head) {
        ListNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }
        return head;
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

    ListNode* first = buildList({6, 6, 1, 2, 6});
    cout << "removeValue([6,6,1,2,6], 6) = ";
    printList(solution.removeValue(first, 6)); // 期望输出：1 -> 2

    ListNode* second = buildList({1, 1, 2, 3, 3});
    cout << "deleteDuplicatesKeepOne([1,1,2,3,3]) = ";
    printList(solution.deleteDuplicatesKeepOne(second)); // 期望输出：1 -> 2 -> 3

    return 0;
}
