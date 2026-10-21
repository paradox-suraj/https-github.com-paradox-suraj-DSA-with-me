class Solution {
public:
    int minOperations(string s) {
        if (is_sorted(s.begin(), s.end())) return 0;  //  sorted already
        if (s.size() == 2) return -1;  // only single letters can be sorted, which changes nothing
        auto [lo, hi] = minmax_element(s.begin() + 1, s.end() - 1);  // the middle's smallest and largest letters
        if (s[0] <= min(*lo, s.back()) || max(s[0], *hi) <= s.back()) return 1;  // the first letter is the smallest, or the last the largest
        return s.back() < *lo && *hi < s[0] ? 3 : 2;  // the middle sits strictly between the last letter and the first
    }
};