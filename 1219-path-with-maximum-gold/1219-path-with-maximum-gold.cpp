class Solution {
    int m, n;
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int dfs(vector<vector<int>>& grid, int r, int c) {
        int gold = grid[r][c];
        grid[r][c] = 0; // Mark visited

        int max_branch = 0;
        for (const auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                max_branch = max(max_branch, dfs(grid, nr, nc));
            }
        }

        grid[r][c] = gold; // Backtrack
        return gold + max_branch;
    }

    int countNeighbors(const vector<vector<int>>& grid, int r, int c) {
        int count = 0;
        for (const auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                count++;
            }
        }
        return count;
    }

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int total_gold = 0;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                total_gold += grid[r][c];
            }
        }

        int max_gold = 0;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                // Safe pruning: Only cells with <= 2 neighbors should be starting points.
                // A path will never strictly require starting at a cell with 3 or 4 neighbors.
                if (grid[r][c] > 0 && countNeighbors(grid, r, c) <= 2) {
                    max_gold = max(max_gold, dfs(grid, r, c));
                    if (max_gold == total_gold) {
                        return total_gold; // Early exit
                    }
                }
            }
        }

        return max_gold;
    }
};