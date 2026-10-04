class Solution {
public:
    int memo[105][105]; // -1: unvisited, 0: false, 1: true

    bool solve(const string& s, int i, int count) {
        if (count < 0) return false;
        if (i == s.length()) return count == 0;
        if (memo[i][count] != -1) return memo[i][count];

        bool ans = false;
        if (s[i] == '(') {
            ans = solve(s, i + 1, count + 1);
        } else if (s[i] == ')') {
            ans = solve(s, i + 1, count - 1);
        } else {
            ans = solve(s, i + 1, count + 1) ||
                  solve(s, i + 1, count - 1) ||
                  solve(s, i + 1, count);
        }

        return memo[i][count] = ans;
    }

    bool checkValidString(string s) {
        memset(memo, -1, sizeof(memo));
        return solve(s, 0, 0);
    }
};