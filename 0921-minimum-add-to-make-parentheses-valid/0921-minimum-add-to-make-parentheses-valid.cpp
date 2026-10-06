class Solution {
public:
    int minAddToMakeValid(string s) {
        while (true) {
            size_t pos = s.find("()");
            if (pos == string::npos) {
                break;
            }
            s.erase(pos, 2);
        }
        return s.length();
    }
};