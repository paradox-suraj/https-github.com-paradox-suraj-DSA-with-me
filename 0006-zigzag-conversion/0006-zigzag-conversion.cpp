class Solution {
public:
    string convert(string s, int row) {
        // If there's only 1 row, the zigzag pattern matches the original string
        if (row == 1)
            return s;

        // Calculate the full jump cycle step between vertical columns
        int count = 2;
        for (int j = 2; j < row; j++) {
            count += 2;
        }

        string s1 = "";
        
        // Traverse through each row one by one
        for (int i = 0; i < row; i++) {
            int j = i;
            
            while (j < s.size()) {
                // Append the character belonging to the main vertical column
                s1 += s[j];

                // Middle rows have an extra diagonal/zigzag character between columns
                if (i != 0 && i != row - 1) {
                    int zigzagIdx = j + count - (2 * i);
                    if (zigzagIdx < s.size()) {
                        s1 += s[zigzagIdx];
                    }
                }
                
                // Jump to the next cycle column
                j += count;
            }
        }
        return s1;
    }
};