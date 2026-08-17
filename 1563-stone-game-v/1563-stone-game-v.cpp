class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // Prefix sum
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        // dp[l][r] = maximum score from l...r
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Length of the current subarray
        for (int len = 2; len <= n; len++) {

            for (int l = 0; l + len <= n; l++) {

                int r = l + len - 1;

                // Try every possible split
                for (int k = l; k < r; k++) {

                    int leftSum =
                        prefix[k + 1] - prefix[l];

                    int rightSum =
                        prefix[r + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {

                        dp[l][r] = max(
                            dp[l][r],
                            leftSum + dp[l][k]
                        );

                    }
                    else if (rightSum < leftSum) {

                        dp[l][r] = max(
                            dp[l][r],
                            rightSum + dp[k + 1][r]
                        );

                    }
                    else {

                        dp[l][r] = max({
                            dp[l][r],
                            leftSum + dp[l][k],
                            rightSum + dp[k + 1][r]
                        });
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};