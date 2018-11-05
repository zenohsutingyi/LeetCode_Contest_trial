namespace {
    int decimalLength(int number) {
        int ret = 0;
        while (number > 0) {
            ++ret;
            number /= 10;
        }
        return ret;
    }
};

class PalindromeGenerator {
public:
    PalindromeGenerator(int R, int L, bool even_length = false)
        :   start_(R),
            end_(L),
            even_length_(even_length) {
        initFactor();
    };
    bool initFactor() {
        int start_length = decimalLength(start_);
        if (even_length_ != (start_length % 2 == 0)) {
            // initialize factor value by the minimum with digits length
            int factor_length = (start_length / 2) + 1;
            factor_ = factorMinimum(factor_length);
            return true;
        }
        // initialize factor value by the left half digits of range start
        factor_ = start_;
        int temp = start_;
        while (temp > 9) {
            temp /= 100;
            factor_ /= 10;
        }
        return true;
    }
    int factorMinimum(int length) {
        if (length <= 0) {
            return -1;
        }
        int ret = 1;
        while (length > 1) {
            ret *= 10;
            --length;
        }
        return ret;
    }
    int next() {
        if (-1 == start_ || -1 == end_) {
            return -1;
        }
        // generate a palindrome by factor and keep it in range
        int ret = toPalindrome(factor_, even_length_);
        while (ret < start_) {
            ++factor_;
            ret = toPalindrome(factor_, even_length_);
        }
        ++factor_;
        if (ret > end_) {
            // return -1 if out of range
            ret = -1;
        }
        return ret;
    }
    long long toPalindrome(int factor, bool even_length) {
        int temp = factor;
        long long ret = factor;
        // skip repeating the last digit in factor for palindorme with odd length
        if (even_length) {
            ret *= 10;
            ret += factor % 10;
        }
        temp /= 10;
        while (temp > 0) {
            ret *= 10;
            ret += temp % 10;
            temp /= 10;
        }
        return ret;
    }
    long long toPalindrome(int factor) {
        return toPalindrome(factor, even_length_);
    }
private:
    int start_ = -1;
    int end_ = -1;
    int factor_ = -1;
    bool even_length_ = false;
};

class Solution {
public:
    bool isPalindrome(const string& original_str) {
        string reversed_str = original_str;
        std::reverse(reversed_str.begin(), reversed_str.end());
        return original_str == reversed_str;
    }
    template <typename T>
    bool isPalindrome(T number) {
        auto original_str = std::to_string(number);
        return isPalindrome(original_str);
    }
    int superpalindromesInRange(string L, string R) {
        int ret = 0;
        // setup for generator by range and digits length
        long long num_left = std::stoll(L, nullptr, 0);
        long long num_right = std::stoll(R, nullptr, 0);
        int root_start = static_cast<int>(ceil(sqrt(num_left)));
        int root_end = static_cast<int>(floor(sqrt(num_right)));
        
        // check superpalindromes with even length in range
        PalindromeGenerator generator(root_start, root_end, true);
        int palindrome = -1;
        // count for superpalindromes
        while (-1 != (palindrome = generator.next())) {
            long long square = palindrome;
            square = square * square;
            if (isPalindrome(square)) {
                ++ret;
            }
        }
        // check superpalindromes with odd length in rangerange
        generator = PalindromeGenerator(root_start, root_end, false);
        palindrome = -1;
        // count for superpalindromes
        while (-1 != (palindrome = generator.next())) {
            long long square = palindrome;
            square = square * square;
            if (isPalindrome(square)) {
                ++ret;
            }
        }
        return ret;
    }
};