class Solution {
public:
    bool checkValidString(string s) {
        stack<int> openIndices;
        stack<int> starIndices;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                openIndices.push(i);
            } else if (s[i] == '*') {
                starIndices.push(i);
            } else { // ')'
                if (!openIndices.empty()) {
                    openIndices.pop();
                } else if (!starIndices.empty()) {
                    starIndices.pop();
                } else {
                    return false;
                }
            }
        }

        // Match remaining '(' with '*' that appear AFTER them
        while (!openIndices.empty() && !starIndices.empty()) {
            if (openIndices.top() > starIndices.top()) {
                return false; // '*' is before '(', cannot act as ')'
            }
            openIndices.pop();
            starIndices.pop();
        }

        return openIndices.empty();
    }
};