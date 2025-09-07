/*
GFG <-- Frequencies in a Limited Array --> Difficulty: Easy

You are given an array arr[] containing positive integers. 
The elements in the array arr[] range from 1 to n (where n is the size of the array), and some numbers may be repeated or absent.
Your task is to count the frequency of all numbers in the range 1 to n and return an array of size n such that result[i] represents 
the frequency of the number i (1-based indexing).
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> frequencyCount(vector<int>& arr) {
    // code here
    int n = arr.size();
    vector<int> res(n, 0);
    for(int i=0; i<n; i++) res[arr[i]-1]++;
    
    return res;
}

int main() {
    vector<int> arr;
    int n;
    cout << "Enter Array Size : ";
    cin >> n;
    cout << "Enter the elements ( 1 to " << n << " ) : ";
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        arr.push_back(x);
    }

    vector<int> res = frequencyCount(arr);
    for(int i=0; i<n; i++) cout << res[i] << " ";

    return 0;
}