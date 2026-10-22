class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                k = i;
                break;
            }
        }
        bool is_forward = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(k + i) % n] != i) {
                is_forward = false;
                break;
            }
        }
        bool is_backward = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(k - i + n) % n] != i) {
                is_backward = false;
                break;
            }
        }
        int ans = 1e9;
        if (is_forward) {
            ans = min(ans, k);       
            ans = min(ans, n - k + 2);  
        }
        if (is_backward) {
            ans = min(ans, n - k); 
            ans = min(ans, k + 2);     
        }
        return ans == 1e9 ? -1 : ans;
    }
};
