#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <functional>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <bit>

using namespace std;
using namespace std::chrono;

// Local
#define LOCAL

// --- 便捷宏定义 ---
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define pb push_back
#define mp make_pair

// 测试断言宏
#define EXPECT_EQ(a, b) do { \
    auto _a = (a), _b = (b); \
    if (_a == _b) cout << "✓ PASS" << endl; \
    else cout << "✗ FAIL: expected " << _b << ", got " << _a << endl; \
} while(0)

// 浮点数断言宏
#define EXPECT_DOUBLE_EQ(a, b) do { \
    auto _a = (a), _b = (b); \
    if (doubleEqual(_a, _b)) cout << "✓ PASS" << endl; \
    else cout << "✗ FAIL: expected " << _b << ", got " << _a << endl; \
} while(0)

// --- 数据结构定义 ---

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Node {
    int val;
    vector<Node*> children;
    Node() : val(0) {}
    Node(int x) : val(x) {}
    Node(int x, vector<Node*> _children) : val(x), children(_children) {}
};

struct RandomListNode {
    int val;
    RandomListNode *next;
    RandomListNode *random;
    RandomListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

// --- 打印工具 (增强版) ---

// 前向声明
template<typename T> void print(const T& val);

// 辅助函数：打印单个值（不换行）
template<typename T>
void printValue(const T& val) {
    cout << val;
}

// 特化：打印 pair（不换行）
template<typename T1, typename T2>
void printValue(const pair<T1, T2>& p) {
    cout << "(" << p.first << ", " << p.second << ")";
}

// 打印 pair（带换行版本）
template<typename T1, typename T2>
void print(const pair<T1, T2>& p) {
    printValue(p);
    cout << endl;
}

// 打印 vector
template<typename T>
void print(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        if constexpr (is_same_v<T, string>) {
            cout << "\"" << vec[i] << "\"";
        } else {
            printValue(vec[i]);
        }
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// 打印 vector<vector<T>> (矩阵)
template<typename T>
void print(const vector<vector<T>>& matrix) {
    cout << "[" << endl;
    for (const auto& row : matrix) {
        cout << "  [";
        for (size_t i = 0; i < row.size(); ++i) {
            cout << row[i];
            if (i < row.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

// 打印 set/unordered_set
template<typename T>
void print(const set<T>& s) {
    cout << "{";
    auto it = s.begin();
    for (size_t i = 0; i < s.size(); ++i, ++it) {
        cout << *it;
        if (i < s.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

template<typename T>
void print(const unordered_set<T>& s) {
    cout << "{";
    auto it = s.begin();
    size_t cnt = 0;
    for (; it != s.end(); ++it, ++cnt) {
        cout << *it;
        if (cnt < s.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

// 打印 map/unordered_map
template<typename K, typename V>
void print(const map<K, V>& m) {
    cout << "{";
    auto it = m.begin();
    for (size_t i = 0; i < m.size(); ++i, ++it) {
        cout << it->first << ": " << it->second;
        if (i < m.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

template<typename K, typename V>
void print(const unordered_map<K, V>& m) {
    cout << "{";
    auto it = m.begin();
    size_t cnt = 0;
    for (; it != m.end(); ++it, ++cnt) {
        cout << it->first << ": " << it->second;
        if (cnt < m.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
}

// 打印基础类型
template<typename T>
void print(const T& val) {
    cout << val << endl;
}

// 打印链表
void print(ListNode* head) {
    cout << "List: ";
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// 可视化打印二叉树（层序遍历）
void printTree(TreeNode* root) {
    if (!root) {
        cout << "Empty tree" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    cout << "Tree (level-order): [";
    bool first = true;
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (!first) cout << ", ";
        first = false;
        if (node) {
            cout << node->val;
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null";
        }
    }
    cout << "]" << endl;
}

// 美化打印二叉树（结构化显示）
void printTreeStructure(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << root->val << endl;
    if (root->left || root->right) {
        if (root->left) {
            printTreeStructure(root->left, prefix + (isLeft ? "│   " : "    "), true);
        } else {
            cout << prefix << (isLeft ? "│   " : "    ") << "├── null" << endl;
        }
        if (root->right) {
            printTreeStructure(root->right, prefix + (isLeft ? "│   " : "    "), false);
        } else {
            cout << prefix << (isLeft ? "│   " : "    ") << "└── null" << endl;
        }
    }
}

// --- 构建工具 (增强版) ---

// 数组转链表
ListNode* buildList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    for (int num : nums) {
        cur->next = new ListNode(num);
        cur = cur->next;
    }
    return dummy->next;
}

// 层序遍历数组转二叉树 (支持 "null")
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        if (i < nodes.size() && nodes[i] != "null") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "null") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// 简化版：直接用整数数组构建二叉树（-1 表示 null）
TreeNode* buildTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// 构建图的邻接表
vector<vector<int>> buildGraph(int n, const vector<vector<int>>& edges, bool directed = false) {
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        if (!directed) graph[edge[1]].push_back(edge[0]);
    }
    return graph;
}

// --- 内存管理工具 ---

// 释放链表内存
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// 释放二叉树内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// --- 性能测试工具 ---

class Timer {
    time_point<high_resolution_clock> start_time;
public:
    Timer() : start_time(high_resolution_clock::now()) {}

    void reset() {
        start_time = high_resolution_clock::now();
    }

    double elapsed() const {
        auto end_time = high_resolution_clock::now();
        return duration_cast<microseconds>(end_time - start_time).count() / 1000.0;
    }

    void show(const string& msg = "Elapsed") const {
        cout << msg << ": " << fixed << setprecision(3) << elapsed() << " ms" << endl;
    }
};

// 自动计时宏
#define TIME_IT(code) do { \
    Timer _timer; \
    code; \
    _timer.show("Time"); \
} while(0)

// --- 实用工具函数 ---

// 生成随机数组
vector<int> randomArray(int n, int minVal = 0, int maxVal = 100) {
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = minVal + rand() % (maxVal - minVal + 1);
    }
    return res;
}

// 比较两个浮点数
bool doubleEqual(double a, double b, double eps = 1e-9) {
    return abs(a - b) < eps;
}

// 比较两个 vector 是否相等
template<typename T>
bool vectorEqual(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// 比较两个链表是否相等
bool listEqual(ListNode* l1, ListNode* l2) {
    while (l1 && l2) {
        if (l1->val != l2->val) return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == nullptr && l2 == nullptr;
}