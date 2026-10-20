class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n + 1, 0), nxt(n + 1, n);

        // prefix sum of adjacent drops
        for (int i = 0; i + 1 < n; i++)
            pre[i + 1] = pre[i] + (nums[i] > nums[i + 1] ? 1 : 0);

        // next drop index from i
        for (int i = n - 2; i >= 0; i--)
            nxt[i] = nums[i] > nums[i + 1] ? i : nxt[i + 1];

        int ans = 0;
        // test all divisors of n
        for (int k = 1; k <= n; k++) {
            if (n % k)
                continue;

            int prev = 0;
            bool ok = true;

            // validate each block of length k
            for (int s = 0; s < n; s += k) {
                int e = s + k - 1;
                int c = pre[e] - pre[s];
                int mn, mx;

                // more than 1 drop cannot be fixed by rotation
                if (c > 1) {
                    ok = false;
                    break;
                }

                if (c == 1) {
                    // boundary check for valid circular sorted order
                    if (nums[e] > nums[s]) {
                        ok = false;
                        break;
                    }
                    int j = nxt[s];
                    mn = nums[j + 1];
                    mx = nums[j];
                } else {
                    // block is already non-decreasing
                    mn = nums[s];
                    mx = nums[e];
                }

                // blocks must be sorted relative to each other
                if (mn < prev) {
                    ok = false;
                    break;
                }
                prev = mx;
            }

            if (ok)
                ans += k;
        }

        return ans;
    }
};