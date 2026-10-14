class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // Impossible if sum exceeds max possible with all 9s
        if (sum > 9 * num) return "";
        
        string res(num, '0');
        
        // Fill largest possible digits from left to right
        for (int i = 0; i < num && sum > 0; i++) {
            int d = min(9, sum);
            res[i] = '0' + d;
            sum -= d;
        }
        
        return res;
    }
};