class Solution {
    int MOD = 1e9 + 7;
    vector<vector<long long>> comb;

    long long dfs(const vector<int>& nums) {
        if (nums.size() <= 2) return 1;
        int root = nums[0];
        vector<int> left, right;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < root) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }
        long long left_ways = dfs(left);
        long long right_ways = dfs(right);
        long long ways = comb[left.size() + right.size()][left.size()];
        return (ways * left_ways % MOD) * right_ways % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        comb.assign(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            comb[i][0] = comb[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
        return (dfs(nums) - 1 + MOD) % MOD;
    }
};