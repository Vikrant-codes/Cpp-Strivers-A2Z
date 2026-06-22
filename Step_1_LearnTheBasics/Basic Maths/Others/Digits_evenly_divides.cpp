/*
GeeksforGeeks -- Count Digits

Given a positive integer n, count the number of digits in n that divide n evenly (i.e., without leaving a remainder). 
Return the total number of such digits.

A digit d of n divides n evenly if the remainder when n is divided by d is 0 (n % d == 0).
Digits of n should be checked individually. If a digit is 0, it should be ignored because division by 0 is undefined.

Examples :
Input: n = 12                      Output: 2
Explanation: 1, 2 when both divide 12 leaves remainder 0.
*/

#include <iostream>
#include <vector>

using namespace std;

int evenlyDivides(int n) {
    int ct = 0;
    int temp = n;
    while (temp>0) {
        int d = temp%10;
        if(d!=0 && n%d == 0) ct++;
        temp = temp/10;
    }
    return ct;
}
int main() {
    int n;
    cout << "Enter no : ";
    cin >> n;
    int count = evenlyDivides(n);
    cout << "Count of Evenly dividing digits : " << count;

    return 0;
}