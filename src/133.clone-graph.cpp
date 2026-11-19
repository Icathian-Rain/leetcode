/*
 * @lc app=leetcode.cn id=133 lang=cpp
 * @lcpr version=30204
 *
 * [133] 克隆图
 */


// @lcpr-template-start
#include "../header.h"
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
// @lcpr-template-end
// @lc code=start

// Definition for a Node.



class Solution {
    Node* dfsClone(Node* node, unordered_map<Node*, Node*>& mp) {
        // 已有克隆直接返回：映射存在即"已发现"，天然处理环
        if (mp.count(node)) return mp[node];
        mp[node] = new Node(node->val);   // 先建克隆再递归，防止环上无限递归
        for (Node* nb : node->neighbors) {
            mp[node]->neighbors.push_back(dfsClone(nb, mp)); // 邻居的克隆递归生成
        }
        return mp[node];
    }

    Node* cloneGraphOpt(Node* node) {
        if (node == nullptr) return nullptr;
        unordered_map<Node*, Node*> mp; // 旧指针 -> 新克隆
        return dfsClone(node, mp);
    }

public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr) return node;
        unordered_map<Node*, Node*> mp;

        queue<Node*> q;
        q.push(node);
        mp[node] = new Node(node->val);
        while(!q.empty()) {
            Node* p = q.front(); q.pop();
            int n=p->neighbors.size();
            for(int i=0; i<n; i++) {
                if(mp.find(p->neighbors[i]) == mp.end()) {
                    q.push(p->neighbors[i]);
                    mp[p->neighbors[i]] = new Node(p->neighbors[i]->val);
                }
                mp[p]->neighbors.push_back(mp[p->neighbors[i]]);
            }
        }

        return mp[node];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,4],[1,3],[2,4],[1,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[]]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */

