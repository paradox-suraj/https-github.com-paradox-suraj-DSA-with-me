class Solution {
public:
    struct Node {
        int len;
        int prefix;
        int suffix;
        int best;
        char chr;
        char chl;
    };
    vector<Node> tree;
    void update(int node, int l, int r, int index, char c) {

        if (l == r) {
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            tree[node].chr = c;
            tree[node].chl = c;
            tree[node].len = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (index <= mid) {
            update(2 * node, l, mid, index, c);
        } else {
            update(2 * node + 1, mid + 1, r, index, c);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    vector<int> query(const string& queryCharacters,
                      const vector<int>& queryIndices, int n) {
        vector<int> res;
        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            res.push_back(tree[1].best);
        }
        return res;
    }
    Node merge(Node left, Node right) {
        Node parent;
        parent.len = left.len + right.len;
        parent.chl = left.chl;
        parent.chr = right.chr;

        if (left.chr == right.chl && left.prefix == left.len) {
            parent.prefix = left.prefix + right.prefix;

        } else {
            parent.prefix = left.prefix;
        }
        if (left.chr == right.chl && right.suffix == right.len) {
            parent.suffix = left.suffix + right.suffix;
        } else {
            parent.suffix = right.suffix;
        }
        parent.best = max(left.best, right.best);

        if (left.chr == right.chl) {
            parent.best = max(parent.best, left.suffix + right.prefix);
        }
        return parent;
    }

    void divide(int node, int l, int r, const string& s) {
        if (l == r) {
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            tree[node].chl = s[l];
            tree[node].chr = s[r];
            tree[node].len = 1;

            return;
        }
        int mid = (l + r) / 2;
        divide(2 * node, l, mid, s);
        divide(2 * node + 1, mid + 1, r, s);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        divide(1, 0, n - 1, s);

        return query(queryCharacters, queryIndices, n);
    }
};