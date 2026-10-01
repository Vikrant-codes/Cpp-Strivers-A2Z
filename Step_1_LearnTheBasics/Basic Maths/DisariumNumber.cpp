// GFG - Disarium Number : Basic

/*
>> Disarium Number

| A Disarium number is a number where the sum of its digits raised to the power of their respective positions 
| (1-indexed position from the left) equals the number itself.

Examples of Disarium Numbers :-
• 89: 8¹ + 9² = 8 + 81 = 89
• 135: 1¹ + 3² + 5³ = 1 + 9 + 125 = 135
• 175: 1¹ + 7² + 5³ = 1 + 49 + 125 = 175
• 518: 5¹ + 1² + 8³ = 5 + 1 + 512 = 518
*/

/*
GFG - Disarium Number : Basic

Given a number n, find if it is Disarium or not.

A number is called a Disarium number if the sum of its digits raised to the power of their respective positions 
is equal to the number itself.

Examples :-

Input: 89 __ Output: true
Explanation: 8^1 + 9^2 = 8 + 81 = 89, which is equal to n. Therefore, 89 is a Disarium Number, so output is true.

Input: 81 __ Output: false
Explanation: 8^1 + 1^2 = 8 + 1 = 9, which is not equal to n. Therefore, 81 is not a Disarium Number, so output is false.

Constraints :-
• 0 <= n <= 10^8
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Storing Digits) : Time Complexity : O(d) __ Space Complexity : O(d)
/*
- Extract all the digits of the number and store them in a vector.
- Calculate the sum of digits raised to the power of their respective position.
- Check if this sum is equal to the original number n.

The digits are extracted in reversed order, and when inserted in the digits vector using push_back,
the digits vector also contains the digits in reversed order.

Now, to traverse the digits we need to traverse right to left in the digits vector while maintaining a position variable.
Initially position is 1. For each digit, we calculate digit ^ pos, and then increment pos for the position of next digit.

We can also reverse the digits vector to store the digits in original order.
After reversal, we can get the position of each digit which is at index i in digits vector, using pos = (i + 1).
Thus, we wont need to explicitly maintain a pos variable if we reverse the digits vector.

>> Time Complexity
Let, d = count of digits in n
- Extracting and storing digits in digits vector: O(d)
- Traversing the digits vector and building sum: O(d)
Total: O(d)

>> Space Complexity
An extra space is used to store the 'd' digits of the number. So, O(d)
*/ 

bool isDisarium1(int n) {
    vector<int> digits;
    
    int temp = n;
    
    // Store all digits of the number
    while (temp) {
        digits.push_back(temp % 10);
        
        temp /= 10;
    }
    
    // digits vector now contains the digits in reverse order (as digits are extracted in reverse order)

    // calculate sum of each digit raised to the power of their respective position
    int sum = 0;

    // traverse the digits vector from end while maintaining a pos variable (initial value = 1)
    int pos = 1;    // the left-indexed position of the current digit
    for (int i = digits.size()-1; i >= 0; i--) {
        // sum += pow(digits[i], pos);
        // pos++;
        
        sum += pow(digits[i], pos++);
    }
    
    return sum == n;
}

bool isDisarium2(int n) {
    vector<int> digits;
    int temp = n;
    
    // Store all digits of the number
    while (temp) {
        digits.push_back(temp % 10);
        
        temp /= 10;
    }
    
    // reverse the vector so digits can be traversed in their appearance order
    reverse(digits.begin(), digits.end());
    
    // calculate sum of each digit raised to the power of their respective position
    int sum = 0;
    for (int i = 0; i < digits.size(); i++) {
        sum += pow(digits[i], i+1);
    }
    
    return sum == n;
}

// Optimal Approach : Time Complexity : O(d) __ Space Complexity : O(1)
/*
We don't need to store the digits in a vector to get the required sum.
We can calculate the sum by adding digit raised to its respective position while extracting the digits.

We know digits are extracted in reverse order, so the first digit extracted will be at position = count of digits of n.
Let d = count of digits of n, dig = extracted digit, pos = position of current digit
So, the first extracted digit is at position d. So, we do sum += pow(dig, pos) = pow(dig, d).

When we extract the later digits, their position is less than d, so the value of pos must decrement.
- the second extracted digit is at position d-1
- the third extracted digit is at position d-2
...
- the last extracted digit is at position 1

So, we just need to find the count of digits of n, to get the initial value of `pos`. Then we can simply decrement it.
count of digits of n = log10(n) + 1.

>> Time Complexity
Let, d = count of digits of n
Extracting digits & building sum takes O(d). So, O(d)

>> Space Complexity 
No extra space used just few variables, so O(1).
*/
bool isDisarium(int n) {
    int sum = 0;
    int pos = log10(n) + 1;   // initial value = count of digits (position of last digit)
    int temp = n;             // temp variable so original number's value is not lost
    
    while (temp) {
        int dig = temp % 10;
        
        sum += pow(dig, pos--);
        // pos-- decrements the position for the later digits
        
        temp /= 10;
    }
    
    return sum == n;
}

int main() {
    return 0;
}