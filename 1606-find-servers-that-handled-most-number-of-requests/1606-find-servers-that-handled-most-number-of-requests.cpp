class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > heap;

        vector<int> server(k, 0);
        set<int> free;

        for (int i = 0; i < k; i++) {
            free.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {
            long long arr = arrival[i];
            int l = load[i];

            while (!heap.empty() && heap.top().first <= arr) {
                int s_idx = heap.top().second;
                heap.pop();
                free.insert(s_idx);
            }

            if (free.empty()) {
                continue;
            }

            auto it = free.lower_bound(i % k);
            if (it == free.end()) {
                it = free.begin();
            }

            int s = *it;
            free.erase(it);

            heap.push({arr + l, s});
            server[s]++;
        }

        int max_ = *max_element(server.begin(), server.end());

        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server[i] == max_) {
                res.push_back(i);
            }
        }
        return res;
    }
};