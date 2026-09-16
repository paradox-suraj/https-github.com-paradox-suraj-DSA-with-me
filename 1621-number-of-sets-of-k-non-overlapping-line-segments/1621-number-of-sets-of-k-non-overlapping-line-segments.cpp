class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1000000007;

        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));
        vector<vector<long long>> sum(n, vector<long long>(k + 1, 0));

        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
            sum[i][0] = 1;
        }

        for (int j = 1; j <= k; j++) {
            long long running = 0;

            for (int i = 1; i < n; i++) {
                dp[i][j] = dp[i - 1][j];

                running += dp[i - 1][j - 1];
                running %= MOD;

                dp[i][j] += running;
                dp[i][j] %= MOD;
            }
        }

        return dp[n - 1][k];
    }
};