/*
TUF - 801. Check if a Number is Prime or Not 

Given an integer num, return true if it is prime otherwise false.
A prime number is a number that is divisible only by 1 and itself.

Examples :-

Input : num = 5 __ Output : true
Explanation : The factors of 5 are 1 and 5 only.
So it satisfies the prime number condition.

Input : num = 15 __ Output : false
Explanation : The factors of 15 are 1, 3, 5, 15 only.
As the number has factors other than 1 and itself, So it is not a prime number.

Constraints :-
• 1 <= num <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

bool fun(int num, int i) {
    if (i * i > num)
        return true;

    if (num % i == 0) return false;
    
    return fun(num, i + 1);
}

bool checkPrime(int num){
    if (num < 2) 
        return false;

    return fun(num, 2);
}

int main() {
    return 0;
}