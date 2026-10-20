class Solution {
public:
    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;
            bool possible = true;
            for (int start = 0; start < n; start += k) {
                int descents = 0;
                for (int i = start; i < start + k - 1; i++) {
                    if (nums[i] > nums[i + 1])
                        descents++;
                }
                if (descents > 1 ||
                    (descents == 1 &&
                     nums[start] < nums[start + k - 1])) {
                    possible = false;
                    break;
                }
                if (descents == 0 &&
                    nums[start] > nums[start + k - 1]) {
                    possible = false;
                    break;
                }
            }
            if (possible) {
                vector<int> rotated;
                rotated.reserve(n);
                for (int start = 0; start < n; start += k) {
                    int pivot = start;
                    for (int i = start; i < start + k - 1; i++) {
                        if (nums[i] > nums[i + 1]) {
                            pivot = i + 1;
                            break;
                        }
                    }
                    for (int i = pivot; i < start + k; i++)
                        rotated.push_back(nums[i]);
                    for (int i = start; i < pivot; i++)
                        rotated.push_back(nums[i]);
                }
                if (is_sorted(rotated.begin(), rotated.end()))
                    ans += k;
            }
        }
        return ans;
    }
};