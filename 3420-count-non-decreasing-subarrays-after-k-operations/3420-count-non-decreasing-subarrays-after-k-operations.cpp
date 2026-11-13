class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n) LOG++;

        // Finding the next greater element for every index
        vector<int> nextGreater(n, n), st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i]) {
                st.pop_back();
            }

            if (!st.empty()) {
                nextGreater[i] = st.back();
            }

            st.push_back(i);
        }

        // Prefix sum to get the original subarray sum quickly
        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Binary lifting tables
        vector<vector<int>> jump(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> mxSum(
            LOG, vector<long long>(n + 1, 0)
        );

        // From each index, we can extend the current maximum
        // until we reach the next greater element
        for (int i = 0; i < n; i++) {
            jump[0][i] = nextGreater[i];
            mxSum[0][i] =
                1LL * nums[i] * (nextGreater[i] - i);
        }

        // Precomputing jumps of size 2^j
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = jump[j - 1][i];

                jump[j][i] = jump[j - 1][mid];
                mxSum[j][i] =
                    mxSum[j - 1][i] + mxSum[j - 1][mid];
            }
        }

        // Calculates how many increments are needed
        // to make nums[l...r] non-decreasing
        auto getCost = [&](int l, int r) -> long long {
            int pos = l;
            int end = r + 1;
            long long maximumSum = 0;

            // Jump over complete segments where the maximum
            // value remains the same
            for (int j = LOG - 1; j >= 0; j--) {
                if (pos < n && jump[j][pos] <= end) {
                    maximumSum += mxSum[j][pos];
                    pos = jump[j][pos];
                }
            }

            // Handle the remaining partial segment
            if (pos < end) {
                maximumSum += 1LL * nums[pos] * (end - pos);
            }

            // Difference gives the total increments required
            return maximumSum - (pref[end] - pref[l]);
        };

        long long answer = 0;
        int right = 0;

        // Sliding window: for every left endpoint,
        // find the maximum valid right endpoint
        for (int left = 0; left < n; left++) {
            right = max(right, left);

            // Expand the window while the required operations
            // are within the allowed limit k
            while (right + 1 < n &&
                   getCost(left, right + 1) <= k) {
                right++;
            }

            // All subarrays from left to right are valid
            answer += right - left + 1;
        }

        return answer;
    }
};