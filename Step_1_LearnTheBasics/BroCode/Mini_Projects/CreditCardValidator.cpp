/*
Problem: Credit Card Number Validation (Luhn Check)

Credit card numbers are not random numbers.
Every valid credit card number is constructed in such a way that it satisfies a checksum rule known as the Luhn algorithm.

This design helps systems quickly detect typing and transmission errors (such as a wrong digit or swapped digits) 
without contacting the bank.

Your task is to verify whether a given number could be a valid credit card number 
by checking if it satisfies the Luhn validation rule.

Important:
Passing the Luhn check does not mean the credit card actually exists or is usable.
It only means the number is well-formed according to the rules used when credit card numbers are issued.

Luhn Algorithm Description
1. Given a number consisting of digits:
2. Start from the rightmost digit (the check digit) and move left.
3. Double every second digit (i.e., digits in even positions when counted from the right, starting at 1).
4. If doubling a digit results in a number greater than 9, subtract 9 from it.
5. Add all digits (both modified and unmodified) to obtain a total sum.
6. If the total sum is divisible by 10, the number is considered Luhn-valid

| If a credit card number exists, it must satisfy the Luhn check.
| But satisfying the Luhn check does not mean the card exists.

Examples :-
Credit Card No. : 4539148803436467 -> VALID
Credit Card No. : 4539148803436468 -> INVALID
*/

#include <iostream>
using namespace std;

// sum of even place digits (firstly double those digits (if double > 9, double = double - 9), then add it)
int sumEvenPlaceDigits(string cardNo) {
    int sum = 0;
    for (int i = cardNo.size()-2; i >= 0; i-=2) {
        int dig = cardNo[i] - '0';
        int twice = dig * 2;
        if (twice > 9) 
            twice -= 9;
        sum += twice;
    }

    return sum;
}

// sum of odd place digits
int sumOddPlaceDigits(string cardNo) {
    int sum = 0;
    for (int i = cardNo.size()-1; i >= 0; i-=2) {
        int dig = cardNo[i] - '0';
        sum += dig;
    }

    return sum;
}

bool isValidCreditCardNo(string cardNo) {
    int result = sumEvenPlaceDigits(cardNo) + sumOddPlaceDigits(cardNo);
    
    return result % 10 == 0;
}

int main() {
    string cardNumber;
    cout << "Enter the credit card number : ";
    cin >> cardNumber;

    if (isValidCreditCardNo(cardNumber))
        cout << "VALID";
    else 
        cout << "INVALID";

    return 0;
}