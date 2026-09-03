class Solution {
public:
    bool uniformArray(vector<int>& nums) {
        int mini = *min_element(nums.begin(), nums.end());

        if (mini % 2 == 1)
            return 1;

        for (int x : nums) {
            if (x % 2 == 1)
                return 0;
        }

        return 1;
    }
};