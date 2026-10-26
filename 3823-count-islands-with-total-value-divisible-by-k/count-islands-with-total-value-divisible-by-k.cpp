class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        function<long long(int, int)> dfs = [&](int r, int c) -> long long {
            if (r < 0 || c < 0 || r >= m || c >= n ||
                grid[r][c] == 0)
                return 0;
            long long sum = grid[r][c];
            grid[r][c] = 0;
            sum += dfs(r + 1, c);
            sum += dfs(r - 1, c);
            sum += dfs(r, c + 1);
            sum += dfs(r, c - 1);
            return sum;
        };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long sum = dfs(i, j);
                    if (sum % k == 0)
                        count++;
                }
            }
        }
        return count;
    }
};