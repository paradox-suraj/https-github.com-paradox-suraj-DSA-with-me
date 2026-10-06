class Solution {
public:
    int minAddToMakeValid(string s) {
        int open_needed = 0;
        int insertions = 0;

        for (char c : s) {
            if (c == '(') {
                open_needed++;
            } else {
                if (open_needed > 0) {
                    open_needed--;
                } else {
                    insertions++;
                }
            }
        }

        return insertions + open_needed;
    }
};