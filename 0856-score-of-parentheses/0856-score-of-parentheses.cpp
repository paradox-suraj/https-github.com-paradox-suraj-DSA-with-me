class Solution {
private:
    int score(const string& s, int l, int r) {
        int balance = 0;
        
        // Find if the string splits into two balanced sub-expressions: A + B
        for (int i = l; i < r; ++i) {
            balance += (s[i] == '(' ? 1 : -1);
            if (balance == 0) {
                // Split point found: s[l...i] + s[i+1...r]
                return score(s, l, i) + score(s, i + 1, r);
            }
        }
        
        // If balance reached 0 only at r, s[l...r] is enclosed by s[l] and s[r]
        if (r - l == 1) {
            return 1; // Base case: "()"
        }
        
        // Enclosed case: (A) -> 2 * score(A)
        return 2 * score(s, l + 1, r - 1);
    }

public:
    int scoreOfParentheses(string s) {
        return score(s, 0, s.length() - 1);
    }
};