class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        int size = static_cast<int>(A.size());
        if (0 == size) {
            // error handling
            return -1;
        }

        vector<int> forward_maximum(size, 0);
        vector<int> backward_minimum(size, 0);
        int temp = A[0];
        for (int i = 0; i < size; ++i) {
            if (temp < A[i]) {
                temp = A[i];
            }
            forward_maximum[i] = temp;
        }

        temp = A[size - 1];
        for (int i = size - 1; i > -1; --i) {
            if (temp > A[i]) {
                temp = A[i];
            }
            backward_minimum[i] = temp;
        }
        for (int i = 1; i < size; ++i) {
            if (forward_maximum[i - 1] <= backward_minimum[i]) {
                return i;
            }
        }
        // error handling
        return -1;
    }
};