class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0); // Score accumulator for the global scope

        for (char c : s) {
            if (c == '(') {
                st.push(0); // Start a new nested scope
            } else {
                int innerScore = st.top();
                st.pop();

                // If innerScore is 0, we matched "()", worth 1.
                // Otherwise, we matched "(A)", worth 2 * innerScore.
                int currentScore = (innerScore == 0) ? 1 : 2 * innerScore;

                // Add to the enclosing scope
                st.top() += currentScore;
            }
        }

        return st.top();
    }
};