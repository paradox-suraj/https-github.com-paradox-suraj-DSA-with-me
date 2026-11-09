class Solution {
public:
    static const int EMPTY_0 = 0, EMPTY_1 = 1, SINGLE_UNCOUNTED = 2, SINGLE_COUNTED = 3, MULTI = 4;
    
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), count = 0;
        vector<int>& status = grid[0];
        for (int i = 0; i < m; ++i) {
            int hits = 0, last_hit = -1;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    ++hits;
                    last_hit = j;
                    if (status[j] <= EMPTY_1) status[j] = SINGLE_COUNTED;
                    else {
                        if (status[j] == SINGLE_UNCOUNTED) ++count;
                        status[j] = MULTI;
                    }
                }
            }
            if (hits == 1) {
                count += (status[last_hit] == MULTI);
                if (status[last_hit] == SINGLE_COUNTED) status[last_hit] = SINGLE_UNCOUNTED;
            } else count += hits;
        }
        return count;
    }
};