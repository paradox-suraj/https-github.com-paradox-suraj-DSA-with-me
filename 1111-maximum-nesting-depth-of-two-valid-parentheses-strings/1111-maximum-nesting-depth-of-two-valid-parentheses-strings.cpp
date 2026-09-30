class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans(seq.size());
        
        for (int i = 0; i < seq.size(); ++i) {
            // If seq[i] == '(', bitwise condition checks (i & 1)
            // If seq[i] == ')', bitwise condition checks !(i & 1)
            ans[i] = (seq[i] == '(') ? (i & 1) : (1 - (i & 1));
            
            // Equivalent one-liner:
            // ans[i] = (i & 1) ^ (seq[i] == '(');
        }
        
        return ans;
    }
};