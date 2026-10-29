class Solution {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree, heavy;
    vector<int> head, pos, seg;

    int charMask(char c) {
        return 1 << (c - 'a');
    }

    void dfs(int u, int p) {
        parent[u] = p;
        subtree[u] = 1;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
            subtree[u] += subtree[v];

            if (heavy[u] == -1 ||
                subtree[v] > subtree[heavy[u]]) {
                heavy[u] = v;
            }
        }
    }

    void decompose(int u, int h, const string& s,
                   vector<int>& base) {
        head[u] = h;
        pos[u] = timer;
        base[timer++] = charMask(s[u]);

        if (heavy[u] != -1) {
            decompose(heavy[u], h, s, base);
        }

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u])
                continue;

            decompose(v, v, s, base);
        }
    }

    void build(int node, int l, int r,
               const vector<int>& base) {
        if (l == r) {
            seg[node] = base[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, base);
        build(node * 2 + 1, mid + 1, r, base);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            seg[node] = value;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, value);
        else
            update(node * 2 + 1, mid + 1, r, idx, value);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr) return seg[node];

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr) ^
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    int pathMask(int u, int v) {
        int result = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            result ^= query(1, 0, n - 1,
                            pos[head[u]], pos[u]);

            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
            swap(u, v);

        result ^= query(1, 0, n - 1, pos[u], pos[v]);

        return result;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        timer = 0;

        adj.assign(n, {});
        parent.resize(n);
        depth.assign(n, 0);
        subtree.assign(n, 0);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1);

        vector<int> base(n);
        decompose(0, 0, s, base);

        seg.assign(4 * n, 0);
        build(1, 0, n - 1, base);

        vector<bool> answer;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                s[u] = c;
                update(1, 0, n - 1, pos[u], charMask(c));
            } else {
                int v;
                ss >> v;

                int mask = pathMask(u, v);
                answer.push_back(
                    (mask & (mask - 1)) == 0
                );
            }
        }

        return answer;
    }
};