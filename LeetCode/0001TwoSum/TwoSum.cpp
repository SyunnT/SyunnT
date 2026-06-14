#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        decltype(map.begin()) it;
        for (int i = 0; i < nums.size(); ++i) {
            if ((it = map.find(target - nums[i])) != map.end()) {
                return {it->second, i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    return 0;
}