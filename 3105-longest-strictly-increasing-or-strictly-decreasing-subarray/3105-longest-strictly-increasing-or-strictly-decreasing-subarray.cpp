class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        int best = 1;
        int start = 0;
        while (start < n - 1) {
            if (nums[start] == nums[start + 1]) {
                ++start;
                continue;
            }
            //main
            bool up = nums[start] < nums[start + 1];
            int end = start + 1;
            while (end + 1 < n && (nums[end] < nums[end + 1]) == up && nums[end] != nums[end + 1]) {
                ++end;
            }
            best = max(best, end - start + 1);
            start = end;
        }
        return best;
    }
};