class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int match = 0;
        vector<int> temp = cnt;

        while (match < n && temp[target[match] - 'a'] > 0) {
            temp[target[match] - 'a']--;
            match++;
        }

        int start = min(n - 1, match);

        vector<int> avail = cnt;
        for (int i = 0; i < start; i++)
            avail[target[i] - 'a']--;

        for (int i = start; i >= 0; i--) {
            for (int c = target[i] - 'a' + 1; c < 26; c++) {
                if (avail[c] > 0) {
                    avail[c]--;

                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    for (int j = 0; j < 26; j++)
                        ans.append(avail[j], char('a' + j));

                    return ans;
                }
            }

            if (i > 0)
                avail[target[i - 1] - 'a']++;
        }

        return "";
    }
};