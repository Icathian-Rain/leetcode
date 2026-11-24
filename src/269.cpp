#include "../header.h"
using namespace std;

class Solution {
    string alienOrderOpt(vector<string>& words) {
        vector<vector<int>> next(26);          // 建边: ch1 -> ch2 表示 ch1 在前
        vector<int> indeg(26, 0);
        vector<bool> seen(26, false);          // 出现过的字母
        for (const string& w : words) {
            for (char c : w) seen[c - 'a'] = true;
        }
        // 相邻对是充分信息: 全序约束由相邻对传递
        for (size_t i = 0; i + 1 < words.size(); i++) {
            const string& a = words[i];
            const string& b = words[i + 1];
            size_t k = 0;
            while (k < a.size() && k < b.size() && a[k] == b[k]) k++;
            if (k == a.size() && k == b.size()) continue;   // 完全相等: 无信息
            if (k == b.size()) return "";   // b 是 a 的真前缀: 非法
            // 在首个不同位得到一条字符大小先序边
            if (a[k] != b[k] && !containsEdge(next, a[k] - 'a', b[k] - 'a')) {
                next[a[k] - 'a'].push_back(b[k] - 'a');
                indeg[b[k] - 'a']++;
            }
        }
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (seen[i] && indeg[i] == 0) q.push(i);
        }
        string ans;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ans.push_back(static_cast<char>('a' + u));
            for (int v : next[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        // 输出长度不足 = 有环: 非法
        return static_cast<int>(ans.size()) == static_cast<int>(count(seen.begin(), seen.end(), true))
                   ? ans : string("");
    }

    bool containsEdge(const vector<vector<int>>& g, int u, int v) {
        return find(g[u].begin(), g[u].end(), v) != g[u].end();
    }

public:
    string alienOrder(vector<string>& words) {
        int n=words.size();
        // cmp[a][b]: 
        // -1: a<b, 1: a>b
        vector<bool> vis(26, false);
        vector<int> inDeg(26, 0);
        vector<vector<int>> next(26);
        vector<vector<int>> cmp(26, vector<int>(26, 0));
        for(int i=0; i<n; i++) {
            string a=words[i];
            for(int k=0; k<a.size(); k++) {
                vis[a[k]-'a'] = true;
            }
            for(int j=i+1; j<n; j++) {
                string b=words[j];
                // a < b
                int k=0;
                for(k=0; k<min(a.size(), b.size()); k++) {
                    if(a[k] == b[k]) continue;
                    // a[k] < b[k]
                    if(cmp[a[k]-'a'][b[k]-'a'] == 1) {
                        return "";
                    }
                    else if(cmp[a[k]-'a'][b[k]-'a'] == 0) {
                        cmp[a[k]-'a'][b[k]-'a'] = -1;
                        cmp[b[k]-'a'][a[k]-'a'] = 1;
                        inDeg[b[k]-'a']++;
                        next[a[k]-'a'].push_back(b[k]-'a');
                    }
                    break;
                }
                if(k == min(a.size(), b.size())) {
                    if(a.size() > b.size()) {
                        return "";
                    }
                }
            }
        }
        string ans="";
        queue<int> q;
        for(int i=0; i<26; i++) {
            if(vis[i] == true && inDeg[i] == 0) {
                ans.push_back(i+'a');
                q.push(i);
            }
        }

        while(!q.empty()) {
            auto p=q.front(); q.pop();
            for(auto nxt: next[p]) {
                inDeg[nxt]--;
                if(inDeg[nxt] == 0) {
                    ans.push_back(nxt+'a');
                    q.push(nxt);
                }
            }
        }
        return ans.size() == count(vis.begin(), vis.end(), true) ? ans : "";
    }
};

int main() {
    Solution sol;
    vector<vector<string>> tests = {
        {"wrt", "wrf", "er", "ett", "rftt"},
        {"z", "x"},
        {"z", "x", "z"},
        {"abc", "ab"},
        {"ab", "ac"}
    };
    for (int i = 0; i < tests.size(); i++) {
        cout << "Test " << i + 1 << ": ";
        cout << "\"" << sol.alienOrder(tests[i]) << "\"" << endl;
    }
    return 0;
}