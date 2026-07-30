#include <iostream>
#include <vector>
using namespace std;

// Reverse an Array

// Reverse Array Using Recursion : Time Complexity : O(n/2) __ Space Complexity : O(n/2) -- recursive stack space

// This recursive function implements this logic by taking the two pointers as parameters
void reverseArr(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    swap(arr[l], arr[r]);
    
    reverseArr(arr, l+1, r-1);
}

// Using a single pointer variable
void reverseArrOneVar(vector<int>& arr, int l) {
    if (l >= arr.size()/2)
        return;
    
    swap(arr[l], arr[arr.size() - 1 - l]);

    reverseArrOneVar(arr, l+1);
}

// Check if string is Palindrome

// Palindrome Check Using Recursion : Time Complexity : O(n/2) __ Space Complexity : O(n/2) -- recursive stack space

bool checkPalindrome(string s, int l, int r) {
    // Base Condition
    if (l >= r)
        return true;

    // Palindrome Check
    if (s[l] != s[r]) 
        return false;

    return checkPalindrome(s, l+1, r-1);
}

// We can also implement this palindorme check using a single pointer variable which will be passed as parameter
bool checkPalindromeOneVar(string s, int l) {
    // Base Condition
    if (l >= s.size()/2)
        return true;

    // Palindrome Check
    if (s[l] != s[s.size() - 1 - l]) 
        return false;

    return checkPalindromeOneVar(s, l+1);
}

int main() {
    return 0;
}