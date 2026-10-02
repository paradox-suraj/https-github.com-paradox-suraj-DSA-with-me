class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        getParenthesis(0, 0, "", n, res);
        return res;
    }

    void getParenthesis(int open, int close, string s, int n, vector<string>& res) {
        if(s.length() == 2 * n) {
            res.push_back(s);
        }

        if(open < n) {
            getParenthesis(open + 1, close, s + "(", n, res);
        }

        if(close < open) {
            getParenthesis(open, close + 1, s + ")", n, res);
        }
    }
};