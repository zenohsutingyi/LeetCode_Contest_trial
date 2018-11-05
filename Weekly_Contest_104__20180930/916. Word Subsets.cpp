class Solution {
public:
    vector<size_t> toLetterCount(const string& word) {
        vector<size_t> letter_count(26, 0);
        for (const auto& letter : word) {
            ++letter_count[letter - 'a'];
        }
        return letter_count;
    }
    bool isUniversal(const string& word, const vector<size_t>& universal_threshold) {
        vector<size_t> letter_count = toLetterCount(word);
        for (size_t i = 0; i < letter_count.size(); ++i) {
            if (letter_count[i] < universal_threshold[i]) {
                return false;
            }
        }
        return true;
    }
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<string> ret;
        vector<size_t> universal_threshold(26, 0);
        // update universal_threshold by each word in B
        for (const auto& word : B) {
            vector<size_t> letter_count = toLetterCount(word);
            for (size_t i = 0; i < letter_count.size(); ++i) {
                if (letter_count[i] > universal_threshold[i]) {
                    universal_threshold[i] = letter_count[i];
                }
            }
        }
        // check each word in A if it's universal
        for (const auto& word : A) {
            if (isUniversal(word, universal_threshold)) {
                ret.push_back(word);
            }
        }
        return ret;
    }
};