class Solution {
public:
    int digitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<pair<int, int>, int>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({{digitSum(nums[i]), nums[i]}, i});
        }
        sort(arr.begin(), arr.end());
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[arr[i].second] = i;
        }
        vector<bool> visited(n, false);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[i] == i) {
                continue;
            }
            int j = i;
            int cycle = 0;
            while (!visited[j]) {
                visited[j] = true;
                j = pos[j];
                cycle++;
            }
            ans += cycle - 1;
        }
        return ans;
    }
};