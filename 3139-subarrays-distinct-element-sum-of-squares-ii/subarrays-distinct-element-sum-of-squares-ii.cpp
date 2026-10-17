class Solution {
    long long MOD = 1000000007;
    vector<long long> sum, lazy;
    int n;
    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        long long add = lazy[node];
        long long len = r - l + 1;
        int mid = (l + r) / 2;
        sum[node * 2] =
            (sum[node * 2] + add * (mid - l + 1)) % MOD;
        sum[node * 2 + 1] =
            (sum[node * 2 + 1] + add * (r - mid)) % MOD;
        lazy[node * 2] = (lazy[node * 2] + add) % MOD;
        lazy[node * 2 + 1] = (lazy[node * 2 + 1] + add) % MOD;
        lazy[node] = 0;
    }
    void update(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            sum[node] = (sum[node] + (r - l + 1)) % MOD;
            lazy[node] = (lazy[node] + 1) % MOD;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);
        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
    }
    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) {
            return sum[node];
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        long long left = query(node * 2, l, mid, ql, qr);
        long long right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return (left + right) % MOD;
    }
public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        sum.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
        vector<int> last(100001, -1);
        long long current = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];
            long long oldSum = query(1, 0, n - 1, prev + 1, i);
            update(1, 0, n - 1, prev + 1, i);
            current = (current + 2 * oldSum + (i - prev)) % MOD;
            ans = (ans + current) % MOD;
            last[nums[i]] = i;
        }
        return ans;
    }
};