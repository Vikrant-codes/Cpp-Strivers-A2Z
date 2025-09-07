#include<iostream>
using namespace std;

// Reverse an array using recursion
void rvrseTwoPointer(int arr[], int l, int r){
    if(l >= r) return;
    swap(arr[l], arr[r]);
    rvrseTwoPointer(arr, l+1, r-1);
}

// Reverse using a single pointer
void rvrseOnePointer(int arr[], int p, int len) {
    if (p >= len/2) return;
    swap(arr[p], arr[len-p-1]);
    rvrseOnePointer(arr, p+1, len);
}

// Check if a string is palindrome or not using recursions
bool chkpalindrome(string s, int p, int len) {
    if(p >= len/2) return true;
    if(s[p] != s[len-p-1]) return false;
    return chkpalindrome(s, p+1, len);
}

int main() {
    int arr[] = {1,2,3,4,5};
    rvrseTwoPointer(arr, 0, 4);
    for(int x : arr) cout << x << " ";
    cout << endl;
    rvrseOnePointer(arr, 0, 5);
    for(int x : arr) cout << x << " ";
    cout << endl;
    string s;
    cout << "Enter s : ";
    cin >> s;
    cout << chkpalindrome(s, 0, 7);
    return 0;
}