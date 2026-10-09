class Solution {
public:
int minInsertions(string s) {
int unmatched_open = 0, ans = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            unmatched_open++;
        } else {
            // Ensure we have two closing brackets "))"
            if (i + 1 < s.size() && s[i + 1] == ')') {
                i++;
            } else {
                ans++;
            }

            // Match the closing pair with an opening bracket
            if (unmatched_open > 0) {
                unmatched_open--;
            } else {
                ans++;
            }
        }
    }

    return ans + unmatched_open * 2;
}

};