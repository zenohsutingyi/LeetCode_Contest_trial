class Solution {
public:
    int kSimilarity(const string& A, const string& B) {
        size_t size = A.size();
        if (size < 2) {
            return 0;
        }

        // remove the letters no need to be swapped
        string new_a;
        string new_b;
        for (size_t i = 0; i < size; ++i) {
            if (A[i] != B[i]) {
                new_a.push_back(A[i]);
                new_b.push_back(B[i]);
            }
        }
        if (new_a.empty()) {
            return 0;
        }

        // For the first letter in A, we count how many swaps we need for each matched letter in B
        int better_ret = -1;
        vector<int> other_ret_list;
        for (size_t swap_index = 1; swap_index < new_a.size(); ++swap_index) {
            if (new_a[0] != new_b[swap_index]) {
                continue;
            }
            string next_a = new_a;
            string next_b = new_b;
            next_a.erase(0, 1);
            next_b.erase(0, 1);
            if (new_b[0] == new_a[swap_index]) {
                next_a.erase(swap_index - 1, 1);
                next_b.erase(swap_index - 1, 1);
                better_ret = 1 + kSimilarity(next_a, next_b);
                break;
            } else {
                next_b[swap_index - 1] = new_b[0];
                other_ret_list.push_back(1 + kSimilarity(next_a, next_b));
            }
        }
        if (better_ret != -1) {
            return better_ret;
        }
        
        int ret = *min_element(other_ret_list.cbegin(), other_ret_list.cend());
        return ret;
    }
};