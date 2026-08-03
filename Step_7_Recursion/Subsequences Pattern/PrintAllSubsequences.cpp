// Printing all subsequeneces of an array
/*
A subsequence is a sequence derived from a string or an array by deleting zero or more elements 
without changing the relative order of the remaining elements. 
Crucially, the elements do not need to be consecutive or contiguous in the original structure.

Consider the string/array: "ABCDE"
-> Valid Subsequences: "ACE", "BD", "ABD", "ABCDE" (the sequence itself), and "" (the empty sequence).
-> Invalid Subsequences: "CEA" (order is broken), "BX" ('X' is not in the original sequence).

>> Properties of Subsequence:
- A sequence is a subsequence of itself.
- The empty sequence is a subsequence of every sequence.
- The relative order of characters is unchanged.
- The number of possible subsequences of a sequence of length n is 2^n.
- A subsequence of a subsequence is also a subsequence of the original sequence. (X_X)

>> Mathematical Formula: 
A sequence of length n contains exactly 2^n total subsequences (including the sequence itself and the empty sequence).
Ex-> For arr = {1, 2, 3}, the total subsequences are 8, which are {}, {1}, {2}, {3}, {1,2}, {1,3}, {1,2,3}.
*/

#include<bits/stdc++.h>
using namespace std;



// helper method -> prints the passed subsequence
void print(vector<int>& list) {
    cout << "[ ";

    for (int x : list)
        cout << x << " ";
    
    cout << "]" << endl;
}

// print all subsequences
void fun(int arr[], int n, int ind, vector<int>& ds) {
    if (ind >= n) {
        print(ds);
        return;
    }

    // take / pick the current element (will be added to subsequence) ,push it into the data structure list
    ds.push_back(arr[ind]);         
    fun(arr, n, ind + 1, ds);

    // not take/pick the current element (will not be added to subsequence), so remove it from the data structure list
    ds.pop_back();                  
    fun(arr, n, ind + 1, ds);
}

int main() {
    int arr[] = {1, 2, 3};

    vector<int> ds = {};

    fun(arr, 3, 0, ds);
}