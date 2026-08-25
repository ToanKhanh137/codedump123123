//https://leetcode.com/problems/check-divisibility-by-digit-sum-and-product/
class Solution {
public:
    int add(char a, char b) {
        return (a - '0') + (b - '0');
    }

    int multiply(char a, char b) {
        return (a - '0') * (b - '0');
    }

    bool checkDivisibility(int n) {
        string s = to_string(n);
        return (n % (accumulate(s.begin(), s.end(), 1, multiply) + accumulate(s.begin(), s.end(), 0, add)) == 0 );
    }
};
