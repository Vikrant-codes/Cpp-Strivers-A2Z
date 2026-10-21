#include<bits/stdc++.h>
using namespace std;

// Time Complexity : O(log₂ n) __ Space Complexity : O(log₂ n)

string convert2Binary(int n) {
    string res = "";

    while (n != 0) {
        if (n & 1) res += '1';  // similar to condition, if (n % 2 == 1)  
        else res += '0';

        n = n >> 1;             // similar to n = n / 2;
    }

    reverse(res.begin(), res.end());

    return res;
}

// Time Complexity : O(binary.size()) __ Space Complexity : O(1)

int convert2Decimal(string& binary) {
    int n = binary.size();

    int num = 0;
    int multiplier = 1;         // initial multiplier is 2^0, which is 1.

    for (int i = n - 1; i >= 0; i--) {
        if (binary[i] == '1')
            num = num + multiplier;
        
        multiplier *= 2;
    }

    return num;
}

int main() {
    return 0;
}