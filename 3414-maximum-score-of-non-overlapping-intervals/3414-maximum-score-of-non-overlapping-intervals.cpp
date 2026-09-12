class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& I) {
        int n = I.size();
        vector<tuple<int,int,int,int>> A(n);
        for(int i=0; i<n; ++i) A[i] = {I[i][0], I[i][1], I[i][2], i};
        sort(A.begin(), A.end());
        vector<int> S(n);
        for(int i=0; i<n; ++i) S[i] = get<0>(A[i]);
        
        using P = pair<long long, vector<int>>;
        vector<vector<P>> dp(n + 1, vector<P>(5, {0, {}}));

        for(int i=n-1; i>=0; --i) {
            auto [l, r, w, id] = A[i];
            int nxt = upper_bound(S.begin(), S.end(), r) - S.begin();
            for(int k=1; k<=4; ++k) {
                P take = dp[nxt][k-1];
                take.first += w;
                take.second.push_back(id);
                sort(take.second.begin(), take.second.end());
                
                P best = dp[i+1][k];
                if(take.first > best.first || (take.first == best.first && (best.second.empty() || take.second < best.second)))
                    dp[i][k] = take;
                else dp[i][k] = best;
            }
        }
        return dp[0][4].second;
    }
};