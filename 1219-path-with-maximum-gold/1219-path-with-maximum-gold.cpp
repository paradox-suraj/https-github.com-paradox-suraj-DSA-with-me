class Solution {
    int m, n;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int dfs(vector<vector<int>>& grid, int r, int c) {
        int original_gold = grid[r][c];
        grid[r][c] = 0; // Mark visited

        int max_branch = 0;
        for (const auto& dir : directions) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                max_branch = max(max_branch, dfs(grid, nr, nc));
            }
        }

        grid[r][c] = original_gold; // Backtrack
        return original_gold + max_branch;
    }

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int max_gold = 0;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] > 0) {
                    max_gold = max(max_gold, dfs(grid, r, c));
                }
            }
        }

        return max_gold;
    }
};