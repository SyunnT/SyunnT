#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

/// @brief: 方法选择控制宏
#define METHOD 2

class Solution
{
public:
#if METHOD == 1
    vector<int> twoSum(vector<int>& nums, int target)
    {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
#elif METHOD == 2
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        unordered_map<int, int>::iterator it;
        for (int i = 0; i < nums.size(); ++i) {
            int diff = target - nums[i];
            if ((it = map.find(diff)) != map.end()) {
                return {it->second, i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
#endif
};

void printResult(const vector<int>& nums, const vector<int>& ret, int target)
{
    cout << "输入：" << "nums = [";
    for (int i = 0; i < nums.size(); ++i) {
        if (i) {
            cout << ",";
        }
        cout << nums[i];
    }
    cout << "], target = " << target << endl;

    cout << "输出：";
    if (ret.empty()) {
        cout << "NULL";
    }
    else {
        cout << "[";
        for (int i = 0; i < ret.size(); ++i) {
            if (i) {
                cout << ",";
            }
            cout << ret[i];
        }
        cout << "]";
    }
    cout << endl;
}

int main()
{
    Solution s;

    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> ret1 = s.twoSum(nums1, target1);

    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> ret2 = s.twoSum(nums2, target2);

    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> ret3 = s.twoSum(nums3, target3);

    printResult(nums1, ret1, target1);
    printResult(nums2, ret2, target2);
    printResult(nums3, ret3, target3);

    return 0;
}
