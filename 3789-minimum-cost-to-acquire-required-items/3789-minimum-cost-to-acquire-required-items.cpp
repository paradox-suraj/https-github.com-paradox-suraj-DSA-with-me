class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long c1 = cost1, c2 = cost2, cb = costBoth, n1 = need1, n2 = need2;
        long long mn = min(n1, n2);
        long long mx = max(n1, n2);

        long long separate = c1 * n1 + c2 * n2;
        long long overlap = mn * cb + (n1 - mn) * c1 + (n2 - mn) * c2;
        long long all = mx * cb;

        return min({separate, overlap, all});
    }
};