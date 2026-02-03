/*
Leetcode - 66. Plus One : Easy

You are given a large integer represented as an integer array digits, 
where each digits[i] is the ith digit of the integer. 
The digits are ordered from most significant to least significant in left-to-right order. 
The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.

Examples :-

Input: digits = [1,2,3] __ Output: [1,2,4]
Explanation: The array represents the integer 123. Incrementing by one gives 123 + 1 = 124. 
Thus, the result should be [1,2,4].

Input: digits = [4,3,2,1] __ Output: [4,3,2,2]
Explanation: The array represents the integer 4321. Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].

Input: digits = [9] __ Output: [1,0]
Explanation: The array represents the integer 9. Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].

Constraints :-
• 1 <= digits.length <= 100
• 0 <= digits[i] <= 9
• digits does not contain any leading 0's.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Basic intuition:

Think of the digits as a normal number where you add 1 from the rightmost side.

• Start from the last digit (units place).
• If it’s less than 9, just add 1 and you’re done.
• If it’s 9, adding 1 makes it 0 and creates a carry, so you move left.
• Keep propagating the carry until:
    • you find a digit < 9 (stop), or
    • you run out of digits (all were 9s).
If all digits were 9 (like 9, 99, 999), the result should be 100…0, so you insert 1 at the front.

That’s it — just manual addition with carry, done digit by digit.
*/

vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();      // no. of digits in the number
    int i = n - 1;
    while (i >= 0) {
        if (digits[i] < 9) {
            digits[i]++;
            break;
        }
        else digits[i] = 0;
        i--;
    }
    // if i becomes -ve, means the no. only had 9's ex- 9, 99 etc. so insert 1 at the beginning
    if (i < 0) digits.insert(digits.begin(), 1);

    return digits;
}

vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    int j = n-1;
    while(j >=0 && digits[j] == 9){
        digits[j] = 0;
        j--;
    }
    if(j == -1){
        digits[0] = 1;
        digits.push_back(0);
    }
    else digits[j] += 1;
    return digits;
}

int main() {
    return 0;
}