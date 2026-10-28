class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        bool flipped = m+1 < n;
        if (flipped) swap(m, n);

        // Rolling DP over the smaller dimension (n <= 31 since m * n <= 1000)
        vector<bitset<1024>> dp(n);
        dp[0].set(grid[0][0]);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                
                int val = flipped ? grid[j][i] : grid[i][j];
                bitset<1024> prev = dp[j]; // from top
                if (j > 0) prev |= dp[j - 1]; // from left
                
                bitset<1024> next_dp;
                for (int x = prev._Find_first(); x < 1024; x = prev._Find_next(x)) {
                    next_dp.set(x ^ val);
                }
                dp[j] = move(next_dp);
            }
        }

        return dp[n - 1]._Find_first();
    }
};