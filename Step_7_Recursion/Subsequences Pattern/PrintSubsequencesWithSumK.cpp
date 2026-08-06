// Print subsequeneces whose sum is k

#include<bits/stdc++.h>
using namespace std; 

void print(const vector<int>& list) {
    cout << "[ ";
    
    for (int x : list) 
        cout << x << " ";
    
    cout << "]" << endl;
}

// <- Print all subsequences whose sum is k ->

void printAllSubseqK(vector<int>& arr, int k, int ind, vector<int>& ds, int sum) {
    if (ind == arr.size()) {
        if (sum == k) 
            print(ds);
        
        return;
    }

    ds.push_back(arr[ind]);
    sum += arr[ind];
    printAllSubseqK(arr, k, ind+1, ds, sum);

    ds.pop_back();
    sum -= arr[ind];
    printAllSubseqK(arr, k, ind+1, ds, sum);
}

// Optimization: Early exit condition (Only if array contains positives)
/*
If array contains non-negative integers only, then we can add a early return condition when sum > k.
becuase, since array has only positives, once sum exceeds k, it will only increase or remain same, 
so no good will come by trying to expand the current subsequence, so we must consider other subsequences. 
*/

// <- Print any subsequence whose sum is k ->

// using a boolean flag variable
/*
void printSubseqK(vector<int>& arr, int k, int ind, vector<int>& ds, int sum, bool& found) {
    if (found == true) return;

    if (ind == arr.size()) {
        if (sum == k) {
            print(ds);
            found = true;
        }
        
        return;
    }

    ds.push_back(arr[ind]);
    sum += arr[ind];
    printSubseqK(arr, k, ind+1, ds, sum, found);

    ds.pop_back();
    sum -= arr[ind];
    printSubseqK(arr, k, ind+1, ds, sum, found);
}
*/

// using a non-void recursive method which returns a boolean value (true/false) depending on subsequence found or not
bool printSubseqK(vector<int>& arr, int k, int ind, vector<int>& ds, int sum) {
    if (ind == arr.size()) {
        if (sum == k) {
            print(ds);
            return true;
        }
        return false;
    }

    ds.push_back(arr[ind]);
    sum += arr[ind];
    
    if (printSubseqK(arr, k, ind+1, ds, sum)) 
        return true;

    ds.pop_back();
    sum -= arr[ind];
    
    if (printSubseqK(arr, k, ind+1, ds, sum)) 
        return true;

    return false;
}


// <- Count all subsequences whose sum is k ->

// we don't need to maintain a list of subsequence elements because the elements won't be needed, 
// only maintaining the current sum of subsequence elements is enough which can be done by sum int variable.
int countSubseqK(vector<int>& arr, int k, int ind, int sum) {
    if (ind == arr.size()) {
        if (sum == k) {
            return 1;
        }
        return 0;
    }

    sum += arr[ind];

    int left = countSubseqK(arr, k, ind + 1, sum);

    sum -= arr[ind];

    int right = countSubseqK(arr, k, ind + 1, sum);

    return left + right;
}

// Time & Space Complexity
/*
>> Time Complexity 

For all these methods, 
Each array element has 2 possibilities, chosen and not chosen.
For n elements, the total possibilities become 2 * 2 * 2 * .... * 2 upto n times
So, total time : O(2 ^ n)

This O(2^n) is just for getting the subsequences, if we try to print the subsequence as well, 
another O(n) time is used to print each subsequence, thus making it total O(n * 2^n)

Space Complexity : O(n)

At any step, the maximum recursive depth of call stack can be n only. So, O(n)
*/

int main() {
    vector<int> arr = {1, 2, 3, 4, -1, -1, 2};
    int k = 3;
    vector<int> ds = {};

    // print all subsequences with sum k
    cout << "-- Printing all subsequences with sum " << k << " --\n";
    printAllSubseqK(arr, k, 0, ds, 0);

    // print any 1 subsequence with sum k (whichever is found first)
    cout << "\n\n-- Printing any 1 subsequence with sum " << k << " --\n";

    ds = {};

    // using a boolean flag variable
    // bool found = false;
    // printSubseqK(arr, k, 0, ds, 0, found);

    // using non-void recursive method which returns a boolean value (true/false)
    
    printSubseqK(arr, k, 0, ds, 0);

    // count all subsequences with sum k
    ds = {};
    cout << "\n\nCount of subsequences with sum " << k << ": " << countSubseqK(arr, k, 0, 0) << endl;

    return 0;
}