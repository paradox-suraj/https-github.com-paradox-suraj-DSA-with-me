class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int ans = 0;

        for (int x : s) {
            // only check streaks from the start
            if (!s.count(x - 1)) {
                int curr = x;
                int len = 1;

                while (s.count(curr + 1)) {
                    curr++;
                    len++;
                }

                ans = max(ans, len);
            }
        }

        return ans;
    }
};