class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int cnt[30] = {0};

        for (int x : nums)
            for (int b = 0; b < 30; b++)
                if (x >> b & 1) cnt[b]++;

        long long ans = 0;
        for (int i = 0; i < k; i++) {
            long long cur = 0;
            for (int b = 0; b < 30; b++) {
                if (cnt[b] > 0) {
                    cur |= (1LL << b);
                    cnt[b]--;
                }
            }
            ans = (ans + cur * cur) % MOD;
        }
        return ans;
    }
};