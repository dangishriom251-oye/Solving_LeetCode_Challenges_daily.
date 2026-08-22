class Solution {
public:
    bool checkDivisibility(int n) {
        int original = n;
        int sum = 0;
        int product = 1;

        while (n > 0) {
            int digit = n % 10;
            sum += digit;
            product *= digit;
            n = n / 10;
        }

        int sp = sum + product;

        return original % sp == 0;
    }
};
