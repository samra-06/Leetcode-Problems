#include <bits/stdc++.h>
using namespace std;
class Solution {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy;
    vector<int> head, pos, bit;
    string s;
    void dfs1(int u, int p) {
        parent[u] = p;
        sz[u] = 1;
        heavy[u] = -1;
        int largest = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > largest) {
                largest = sz[v];
                heavy[u] = v;
            }
        }
    }
    void dfs2(int u, int h) {
        head[u] = h;
        pos[u] = ++timer;
        if (heavy[u] != -1) {
            dfs2(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            dfs2(v, v);
        }
    }
    void updateBIT(int idx, int val) {
        while (idx <= n) {
            bit[idx] ^= val;
            idx += idx & -idx;
        }
    }
    int queryBIT(int idx) {
        int ans = 0;
        while (idx > 0) {
            ans ^= bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }
    int rangeQuery(int l, int r) {
        return queryBIT(r) ^ queryBIT(l - 1);
    }
    int pathQuery(int u, int v) {
        int mask = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            mask ^= rangeQuery(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        mask ^= rangeQuery(pos[u], pos[v]);
        return mask;
    }
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        this->n = n;
        this->s = s;
        timer = 0;
        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        parent.assign(n, 0);
        depth.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        bit.assign(n + 1, 0);
        dfs1(0, -1);
        dfs2(0, 0);
        for (int u = 0; u < n; u++) {
            updateBIT(pos[u], 1 << (s[u] - 'a'));
        }
        vector<bool> ans;
        for (string &q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;
            if (type == "update") {
                char c;
                ss >> c;
                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');
                updateBIT(pos[u], oldMask ^ newMask);
                s[u] = c;
            } else {
                int v;
                ss >> v;
                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }
        return ans;
    }
};
