class Solution {
    struct Info {
        vector<int> ways;
        int whole;

        Info(int k) : ways(k, 0), whole(1) {}
    };

    struct SegmentTree {
        int size;
        int mod;
        vector<Info> tree;

        SegmentTree(vector<int>& nums, int k) {
            mod = k;
            size = 1;

            while (size < nums.size()) {
                size <<= 1;
            }

            tree.reserve(size * 2);

            for (int i = 0; i < size * 2; i++) {
                tree.emplace_back(k);
            }

            for (int i = 0; i < nums.size(); i++) {
                int rem = nums[i] % k;

                tree[size + i].ways[rem] = 1;
                tree[size + i].whole = rem;
            }

            for (int i = size - 1; i > 0; i--) {
                tree[i] = combine(
                    tree[i << 1],
                    tree[i << 1 | 1]
                );
            }
        }

        Info combine(const Info& left, const Info& right) {
            Info merged(mod);

            for (int r = 0; r < mod; r++) {
                merged.ways[r] = left.ways[r];
            }

            for (int r = 0; r < mod; r++) {
                if (right.ways[r] == 0) {
                    continue;
                }

                int newRem = (left.whole * r) % mod;
                merged.ways[newRem] += right.ways[r];
            }

            merged.whole = (left.whole * right.whole) % mod;

            return merged;
        }

        void update(int index, int value) {
            int pos = size + index;
            int rem = value % mod;

            fill(tree[pos].ways.begin(),
                 tree[pos].ways.end(), 0);

            tree[pos].ways[rem] = 1;
            tree[pos].whole = rem;

            pos >>= 1;

            while (pos > 0) {
                tree[pos] = combine(
                    tree[pos << 1],
                    tree[pos << 1 | 1]
                );

                pos >>= 1;
            }
        }

        Info query(int left, int right) {
            Info leftPart(mod);
            Info rightPart(mod);

            left += size;
            right += size;

            while (left < right) {
                if (left & 1) {
                    leftPart = combine(leftPart, tree[left]);
                    left++;
                }

                if (right & 1) {
                    right--;
                    rightPart = combine(tree[right], rightPart);
                }

                left >>= 1;
                right >>= 1;
            }

            return combine(leftPart, rightPart);
        }
    };

public:
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        SegmentTree tree(nums, k);
        vector<int> answer;

        for (auto& q : queries) {
            tree.update(q[0], q[1]);

            Info result = tree.query(q[2], nums.size());
            answer.push_back(result.ways[q[3]]);
        }

        return answer;
    }
};