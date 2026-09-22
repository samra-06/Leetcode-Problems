class Solution {
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    int n;
    vector<Node> tree;
    Node merge(Node left, Node right) {
        Node res;
        res.prod = (left.prod * right.prod) % k;
        for (int r = 0; r < k; r++) {
            res.cnt[r] += left.cnt[r];
        }
        for (int r = 0; r < k; r++) {
            int newRemainder = (left.prod * r) % k;
            res.cnt[newRemainder] += right.cnt[r];
        }

        return res;
    }

    void build(vector<int>& nums, int node, int l, int r) {
        if (l == r) {
            int val = nums[l] % k;

            tree[node].prod = val;
            tree[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(nums, 2 * node, l, mid);
        build(nums, 2 * node + 1, mid + 1, r);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int pos, int value) {
        if (l == r) {
            value %= k;

            tree[node] = Node();

            tree[node].prod = value;
            tree[node].cnt[value] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(2 * node, l, mid, pos, value);
        } else {
            update(2 * node + 1, mid + 1, r, pos, value);
        }

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;
        if (qr <= mid) {
            return query(2 * node, l, mid, ql, qr);
        }
        if (ql > mid) {
            return query(2 * node + 1, mid + 1, r, ql, qr);
        }
        Node left = query(2 * node, l, mid, ql, qr);
        Node right = query(2 * node + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }
public:
    vector<int> resultArray(vector<int>& nums,
                            int k,
                            vector<vector<int>>& queries) {
        this->k = k;
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
        vector<int> ans;
        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];
            update(1, 0, n - 1, index, value);
            Node res = query(1, 0, n - 1, start, n - 1);
            ans.push_back(res.cnt[x]);
        }
        return ans;
    }
};