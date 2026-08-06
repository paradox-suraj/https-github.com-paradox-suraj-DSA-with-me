class Solution {
public:
    int smallestNumber(int n, int t) {
        for(int i=n; i < 101; i++){ //See the given Constraints.
            int temp = i;
            int sum = 1; // because product karna hai
            
            while(temp > 0){
                int k = temp % 10; //spiliting digits
                sum = sum * k;
                temp = temp/10;
            }
            if(sum % t == 0){
                return i;
            }
        }
        return 0;
    }
};