class Solution {
public:
  bool equalFrequency(string word) {
    unordered_map<char, size_t> letter_count;
    for (auto letter : word) {
      ++letter_count[letter];
    }
    size_t letters = letter_count.size();
    if (letters == 1) {
      return true;
    }
    unordered_map<size_t, size_t> frequency_count;
    for (auto [letter, frequency] : letter_count) {
      ++frequency_count[frequency];
    }
    if (frequency_count.size() >= 3) {
      return false;
    }
    if (frequency_count.size() == 1) {
      return frequency_count.find(1) != frequency_count.end();
    }
    // frequency_count.size() == 2
    if (frequency_count.find(1) != frequency_count.end() && frequency_count[1] == 1) {
      return true;
    }
    return (word.size() - 1) % letters == 0;
  }
};
