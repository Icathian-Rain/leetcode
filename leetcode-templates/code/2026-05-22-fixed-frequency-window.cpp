#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void addDiff(array<int, 26>& diff, int& different, int index, int delta) {
        int before = diff[index];
        int after = before + delta;
        if (before == 0 && after != 0) {
            ++different;
        } else if (before != 0 && after == 0) {
            --different;
        }
        diff[index] = after;
    }

public:
    vector<int> findAnagramStarts(string text, string pattern) {
        vector<int> ans;
        if (pattern.size() > text.size()) {
            return ans;
        }

        array<int, 26> diff{};
        int different = 0;
        for (char ch : pattern) {
            addDiff(diff, different, ch - 'a', 1);
        }

        int windowSize = static_cast<int>(pattern.size());
        for (int right = 0; right < static_cast<int>(text.size()); ++right) {
            addDiff(diff, different, text[right] - 'a', -1);
            if (right >= windowSize) {
                addDiff(diff, different, text[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                ans.push_back(right - windowSize + 1);
            }
        }

        return ans;
    }

    bool containsPermutation(string text, string pattern) {
        return !findAnagramStarts(text, pattern).empty();
    }
};

int main() {
    Solution solution;

    auto starts = solution.findAnagramStarts("cbaebabacd", "abc");
    cout << "findAnagramStarts(\"cbaebabacd\", \"abc\") = ";
    for (int index : starts) {
        cout << index << ' ';
    }
    cout << "\n"; // 期望输出：0 6

    cout << boolalpha;
    cout << "containsPermutation(\"eidbaooo\", \"ab\") = "
         << solution.containsPermutation("eidbaooo", "ab") << '\n'; // 期望输出：true
    cout << "containsPermutation(\"eidboaoo\", \"ab\") = "
         << solution.containsPermutation("eidboaoo", "ab") << '\n'; // 期望输出：false

    return 0;
}
