class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if ((m + n - 1) % 2 == 1)
            return false;
        vector<vector<bool>> dp(n, vector<bool>(m + n, false));
        if (grid[0][0] == ')')
            return false;
        dp[0][1] = true;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;
                vector<bool> current(m + n, false);
                int change = (grid[i][j] == '(') ? 1 : -1;
                for (int balance = 0; balance < m + n; balance++) {
                    int newBalance = balance + change;
                    if (newBalance < 0)
                        continue;
                    bool possible = false;
                    if (i > 0 && dp[j][balance])
                        possible = true;
                    if (j > 0 && dp[j - 1][balance])
                        possible = true;
                    if (possible)
                        current[newBalance] = true;
                }
                dp[j] = current;
            }
        }
        return dp[n - 1][0];
    }
};