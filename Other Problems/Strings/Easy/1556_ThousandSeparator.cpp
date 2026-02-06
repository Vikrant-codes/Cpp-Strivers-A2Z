/*
Leetcode - 1556. Thousand Separator : Easy

Given an integer n, add a dot (".") as the thousands separator and return it in string format.

Examples :-

Input: n = 987
Output: "987"

Input: n = 1234
Output: "1.234"

Constraints :-
- 0 <= n <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Time Complexity Analysis:

- Time complexity: O(d)
where d = number of digits in n.

Breakdown:
1. Integer → string conversion (stringstream / to_string / manual conversion)
    → processes each digit once → O(d)
2. Loop to build answer string
    → traverses all digits once → O(d)
3. No nested loops or repeated rescanning.

So total time complexity remains: O(d)
Since, d = log10(n), we can also say time complexity is O(log10 n) in terms of the number value.

>> Space Complexity : O(d) ... to store the int n as a string, we used a string num of size O(d)
*/

// Using to_string() method to convert the integer 'n' to string
string thousandSeparator(int n) {
    string num = to_string(n);
    int len = num.length();
    
    string ans = "";
    for (int i = 0; i < len; i++) {
        ans += num[i];
        // if count of remaining digits is multiple of 3, then add a dot
        if ( (len-1-i) % 3 == 0 && i != len-1) 
            ans += '.';
    }
    return ans;
}

// Using stringstream to convert the integer 'n' to string
string thousandSeparator(int n) {
    stringstream ss;
    ss << n;
    string num = "";
    ss >> num;

    int len = num.length();

    string ans = "";
    for (int i = 0; i < len; i++) {
        ans += num[i];
        if ( (len-1-i) % 3 == 0 && i != len-1) 
            ans += '.';
    }
    return ans;
}

// Manually converting int n to string 
string thousandSeparator(int n) {
    if (n == 0)
        return "0";

    string num = "";
    int temp = n;
    while (temp) {
        int dig = temp % 10;
        num += (char) ('0' + dig);
        temp = temp / 10;
    }
    reverse(num.begin(), num.end());

    int len = num.length();

    string ans = "";
    for (int i = 0; i < len; i++) {
        ans += num[i];
        if ( (len-1-i) % 3 == 0 && i != len-1) 
            ans += '.';
    }
    return ans;
}

int main() {
    return 0;
}