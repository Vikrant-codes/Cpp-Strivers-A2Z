/*
>> Armstrong Numbers 

An Armstrong number (also known as a narcissistic or pluperfect number) is a number that equals the sum of its own digits, 
where each digit is raised to the power of the total number of digits

| A number is called an Armstrong number if the sum of its digits raised to the power of the number of digits 
| is equal to the number itself.

Examples :-

- 153 :- 
Count of digits (n) = 3, 
sum of digits raised to the power of n (=3) = 1^3 + 5^3 + 3^3 
                                            = 1 + 125 + 27 
                                            = 153

- 1634 :- 
Count of digits (n) = 4
sum of digits raised to the power of n (=4) = 1^4 + 6^4 + 3^4 + 4^4 
                                            = 1 + 1296 + 81 + 256 
                                            = 1634
*/

#include<iostream>
#include<cmath>         // includes functions like : log10 , pow(base, exp), abs()
using namespace std;

bool isArmstrong(int n) {
    // get count of digits
    int x = (int) (log10(n) + 1);

    // Calculate sum of digits raised to the power count of digits 'x'
    int sum = 0;
    int temp = n;           // use a temp variable to store the value of n and extract the digits
    while (temp) {
        int d = temp % 10;
        sum += pow(d, x);   // pow(base, exp) returns base raised to the power exp, add it to sum
        temp /= 10; 
    }

    // check if the sum is equal to the original number
    return sum == n;       
}

// GFG Variant 
/*
GFG - Armstrong Numbers : Easy

You are given a 3-digit number n, Find whether it is an Armstrong number or not.
An Armstrong number of three digits is a number such that the sum of the cubes of its digits is equal to the number itself. 
371 is an Armstrong number since 33 + 73 + 13 = 371. 

Examples :-

Input: n = 153 __ Output: true
Explanation: 153 is an Armstrong number since 13 + 53 + 33 = 153. 

Input: n = 372 __ Output: false
Explanation: 372 is not an Armstrong number since 33 + 73 + 23 = 378. 

Input: n = 100 __ Output: false
Explanation: 100 is not an Armstrong number since 13 + 03 + 03 = 1. 

Constraints:- 100 ≤ n <1000 
*/
bool armstrongNumber(int n) {
    int sum = 0;
    int temp = n;
    
    while (temp) {
        int d = temp % 10;
        sum += (d * d * d);
        temp /= 10;
    }
    
    return sum == n;
}

int main() {
    cout << "Armstrong Numbers upto 10000" << endl;
    for(int i=1; i<=10000; i++){
        if (isArmstrong(i)) 
            cout << i << "  ";
    }

    return 0;
}