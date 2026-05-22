#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    string signature(const string& word) {
        array<int, 26> count{};
        for (char ch : word) {
            ++count[ch - 'a'];
        }

        string key;
        for (int value : count) {
            key += '#';
            key += to_string(value); // 分隔符避免不同频次拼接成同一个 key。
        }
        return key;
    }

public:
    vector<vector<string>> groupByFrequency(vector<string>& words) {
        unordered_map<string, vector<string>> groups;
        for (const string& word : words) {
            groups[signature(word)].push_back(word);
        }

        vector<vector<string>> ans;
        for (auto& [_, group] : groups) {
            sort(group.begin(), group.end());
            ans.push_back(move(group));
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

    bool canBuildFrom(string target, string source) {
        array<int, 26> count{};
        for (char ch : source) {
            ++count[ch - 'a'];
        }
        for (char ch : target) {
            if (--count[ch - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;

    vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto groups = solution.groupByFrequency(words);
    cout << "groupByFrequency size = " << groups.size() << '\n'; // 期望输出：3
    for (const auto& group : groups) {
        for (const string& word : group) {
            cout << word << ' ';
        }
        cout << '\n';
    }

    cout << boolalpha;
    cout << "canBuildFrom(\"aa\", \"aab\") = "
         << solution.canBuildFrom("aa", "aab") << '\n'; // 期望输出：true
    cout << "canBuildFrom(\"aa\", \"ab\") = "
         << solution.canBuildFrom("aa", "ab") << '\n'; // 期望输出：false

    return 0;
}
