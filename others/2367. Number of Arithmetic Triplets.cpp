class Solution {
public:
  int arithmeticTriplets(vector<int>& nums, int diff) {
    unordered_set<int> previous_nums;
    int result = 0;
    for (auto num : nums) {
      previous_nums.insert(num);
      if (previous_nums.find(num - diff) == previous_nums.end() ||
          previous_nums.find(num - (2 * diff)) == previous_nums.end()) {
        continue;
      }
      ++result;
    }
    return result;
  }
};
