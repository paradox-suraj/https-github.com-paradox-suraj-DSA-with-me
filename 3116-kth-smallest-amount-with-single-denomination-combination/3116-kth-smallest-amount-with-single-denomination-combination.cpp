class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());

        vector<long long> c;                          
        for (int x : coins) {
            bool red = false;
            for (long long y : c) if (x % y == 0) { red = true; break; }
            if (!red) c.push_back(x);                
        }
        int n = c.size();

        auto count = [&](long long x) -> long long {
            long long total = 0;
            for (int mask = 1; mask < (1 << n); ++mask) {
                long long l = 1;
                bool big = false;
                for (int i = 0; i < n; ++i)
                    if (mask >> i & 1) {
                        l = lcm(l, c[i]);
                        if (l > x) { big = true; break; }   
                    }
                if (big) continue;
                total += (__builtin_popcount(mask) & 1) ? x / l : -(x / l);
            }
            return total;
        };

        long long lo = 1, hi = c[0] * (long long)k;   
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;       
            if (count(mid) >= k) hi = mid;
            else                 lo = mid + 1;
        }
        return lo;
    }
};