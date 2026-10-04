class Solution {
public:
    bool checkValidString(std::string s) {
        int min_open = 0; // Minimum possible open brackets needed
        int max_open = 0; // Maximum possible open brackets possible

        for (char c : s) {
            if (c == '(') {
                min_open++;
                max_open++;
            } else if (c == ')') {
                min_open--;
                max_open--;
            } else { // c == '*'
                min_open--; // Treat as ')'
                max_open++; // Treat as '('
            }

            // If maximum possible open brackets drops below 0,
            // we have seen too many ')' that cannot be matched by any '(' or '*'
            if (max_open < 0) {
                return false;
            }

            // min_open cannot drop below 0; extra '*' can just be empty strings ""
            if (min_open < 0) {
                min_open = 0;
            }
        }

        // Valid if 0 falls within the range [min_open, max_open]
        return min_open == 0;
    }
};