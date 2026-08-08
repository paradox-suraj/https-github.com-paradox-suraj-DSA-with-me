class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suffix[j] = position used for word2[j] when
        // word2[j...] is matched as far right as possible in word1.
        vector<int> suffix(m + 1, -1);

        // Empty suffix is always possible after the last index.
        suffix[m] = n;

        int i = n - 1;

        // Build suffix information from right to left.
        for (int j = m - 1; j >= 0; --j) {
            while (i >= 0 && word1[i] != word2[j]) {
                --i;
            }

            if (i >= 0) {
                suffix[j] = i;
                --i;
            }
        }

        vector<int> answer;

        bool usedMismatch = false;
        int j = 0;

        // Greedily choose the smallest possible indices.
        for (int i = 0; i < n && j < m; ++i) {

            // Normal exact match.
            if (word1[i] == word2[j]) {
                answer.push_back(i);
                ++j;
            }

            // Try using our one allowed mismatch.
            else if (!usedMismatch && suffix[j + 1] > i) {
                answer.push_back(i);
                ++j;
                usedMismatch = true;
            }
        }

        // Could not select enough characters.
        if (j != m) {
            return {};
        }

        return answer;
    }
};