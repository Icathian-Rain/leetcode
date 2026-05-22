#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int firstTrue(int n, const function<bool(int)>& check) {
        int left = 0;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (check(middle)) {
                right = middle;  // middle 可能是第一个 true，保留。
            } else {
                left = middle + 1;  // middle 是 false，连同左侧一起排除。
            }
        }

        return left;  // left == n 表示不存在 true。
    }

public:
    int searchInsert(vector<int>& nums, int target) {
        return firstTrue(static_cast<int>(nums.size()), [&](int index) {
            return nums[index] >= target;
        });
    }

    char nextGreatestLetter(vector<char>& letters, char target) {
        int index = firstTrue(static_cast<int>(letters.size()), [&](int i) {
            return letters[i] > target;
        });

        return index == static_cast<int>(letters.size()) ? letters[0] : letters[index];
    }
};

int main() {
    Solution solution;

    vector<int> nums = {1, 3, 5, 6};
    cout << "searchInsert([1,3,5,6], 5) = " << solution.searchInsert(nums, 5) << '\n';
    cout << "searchInsert([1,3,5,6], 2) = " << solution.searchInsert(nums, 2) << '\n';

    vector<char> letters = {'c', 'f', 'j'};
    cout << "nextGreatestLetter(['c','f','j'], 'c') = "
         << solution.nextGreatestLetter(letters, 'c') << '\n';
    cout << "nextGreatestLetter(['c','f','j'], 'j') = "
         << solution.nextGreatestLetter(letters, 'j') << '\n';

    return 0;
}
