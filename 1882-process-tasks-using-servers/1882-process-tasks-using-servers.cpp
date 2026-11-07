class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // free_servers: min-heap of {weight, index}
        using FreeServer = pair<int, int>;
        priority_queue<FreeServer, vector<FreeServer>, greater<FreeServer>> free_servers;

        for (int i = 0; i < n; ++i) {
            free_servers.push({servers[i], i});
        }

        // busy_servers: min-heap of {free_time, weight, index}
        using BusyServer = tuple<long long, int, int>;
        priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy_servers;

        vector<int> ans(m);
        long long current_time = 0;

        for (int j = 0; j < m; ++j) {
            // Task j is available at least at second j
            current_time = max(current_time, (long long)j);

            // If no free servers are available, jump time directly to when the next server frees up
            if (free_servers.empty() && !busy_servers.empty()) {
                current_time = max(current_time, get<0>(busy_servers.top()));
            }

            // Move all servers that are finished by current_time back to free_servers
            while (!busy_servers.empty() && get<0>(busy_servers.top()) <= current_time) {
                auto [free_time, weight, idx] = busy_servers.top();
                busy_servers.pop();
                free_servers.push({weight, idx});
            }

            // Assign task j to the best available free server
            auto [weight, idx] = free_servers.top();
            free_servers.pop();

            ans[j] = idx;
            busy_servers.push({current_time + tasks[j], weight, idx});
        }

        return ans;
    }
};
 
