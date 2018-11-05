class Solution {
public:
    int greatestCommonDivisor(int x, int y) {
        int temp = 0;
        while (0 != y) {
            x %= y;
            temp = y;
            y = x;
            x = temp;
        }
        return x;
    }
    bool hasCommonDivisor(set<int>& numbers) {
        int size = static_cast<int>(numbers.size());
        if (0 == size) {
            return false;
        } else if (1 == size) {
            return true;
        }
        
        set<int> new_numbers;
        int temp = 0;
        auto it = numbers.cbegin();
        const int first = *it;
        ++it;
        for (; it != numbers.cend(); ++it) {
            temp = greatestCommonDivisor(first, *it);
            if (1 == temp) {
                return false;
            }
            new_numbers.insert(temp);
        }
        
        return hasCommonDivisor(new_numbers);
    }
    bool hasGroupsSizeX(vector<int>& deck) {
        if (deck.empty()) {
            // error handling
            return false;
        }
        
        map<int, int> appearance_count;
        for (const auto& num : deck) {
            auto it = appearance_count.find(num);
            if (appearance_count.end() == it) {
                it = appearance_count.insert(std::pair<int, int>(num, 0)).first;
            }
            ++(it->second);
        }
        
        set<int> count_number;
        for (const auto& pair : appearance_count) {
            if (1 == pair.second) {
                return false;
            }
            count_number.insert(pair.second);
        }
        
        return hasCommonDivisor(count_number);
    }
};