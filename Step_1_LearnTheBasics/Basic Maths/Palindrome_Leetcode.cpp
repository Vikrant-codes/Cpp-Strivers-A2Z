/*
Leetcode -- Palindrome Number -- Difficulty : Easy
Given an integer x, return true if x is a palindrome, and false otherwise.

Input: x = 121         Output: true

Input: x = -121        Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Input: x = 10          Output: false
*/

#include<iostream>
using namespace std;

bool isPalindrome(int x) {
    if(x<0) return false;
    long long rev = 0;
    int temp = x;
    while (temp!=0) {
        int d = temp%10;
        rev = rev*10 + d;
        temp = temp/10;
    }
    return rev==x;
}

int main() {
    int n;
    cout << "Enter the number : ";
    cin >> n;
    cout << isPalindrome(n);

    return 0;
}