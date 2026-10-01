class Solution {
public:
    bool isValid(string& s) {
        int j = 0;

        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                s[j++] = c;
            } else {
                if (j == 0)
                    return false;

                char open = s[--j];

                if ((c == ')' && open != '(') ||
                    (c == '}' && open != '{') ||
                    (c == ']' && open != '['))
                    return false;
            }
        }

        return j == 0;
    }
};