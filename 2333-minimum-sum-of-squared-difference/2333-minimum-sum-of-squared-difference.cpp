class Solution {
public:
    long long minSumSquareDiff(std::vector<int>& nums1, std::vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long totalOps = static_cast<long long>(k1) + k2;

        // 1. Calculate absolute differences and track the maximum difference
        int maxDiff = 0;
        for (int i = 0; i < n; ++i) {
            maxDiff = std::max(maxDiff, std::abs(nums1[i] - nums2[i]));
        }

        // 2. Count frequency of each difference
        std::vector<int> count(maxDiff + 1, 0);
        for (int i = 0; i < n; ++i) {
            count[std::abs(nums1[i] - nums2[i])]++;
        }

        // 3. Greedily reduce largest differences down by 1 level
        for (int d = maxDiff; d > 0 && totalOps > 0; --d) {
            if (count[d] == 0) continue;

            if (totalOps >= count[d]) {
                totalOps -= count[d];
                count[d - 1] += count[d];
                count[d] = 0;
            } else {
                count[d - 1] += totalOps;
                count[d] -= totalOps;
                totalOps = 0;
            }
        }

        // 4. Compute the final sum of squared differences
        long long minSquareSum = 0;
        for (long long d = 1; d <= maxDiff; ++d) {
            if (count[d] > 0) {
                minSquareSum += (long long)count[d] * d * d;
            }
        }

        return minSquareSum;
    }
};