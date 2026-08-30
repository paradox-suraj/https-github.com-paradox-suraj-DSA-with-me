class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        auto [mn, mx]=minmax_element(nums.begin(), nums.end());
        int i=mn-nums.begin(), j=mx-nums.begin(), n=nums.size();
        if (i>j) swap(i, j);
        return min({i+1+n-j, j+1, n-i});
    }
};