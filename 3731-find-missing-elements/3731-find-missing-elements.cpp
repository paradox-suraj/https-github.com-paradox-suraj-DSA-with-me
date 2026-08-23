class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {

        int maxm = *max_element(nums.begin(), nums.end());
        int minm = *min_element(nums.begin(), nums.end());

        vector<int> ans;
        vector<int> freq(101, 0);

        for (int num : nums) {
            freq[num]++;
        }

        for (int i = minm; i <= maxm; i++) {
            if (freq[i] == 0) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};