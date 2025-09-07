// Given two sorted arrays (can have duplicates) ... Find the Union of the arrays in sorted order containing only unique values

#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Brute Force Approach --> Time Complexity : O(n log x + m log x) + O(n + m) __ Space Complexity : O(n + m)
/*
We can use a set or map to store the only distinct array element in sorted order
We traverse both the arrays and add their elements to the set/map (it only takes unique elements and adds in sorted order)
where n and m are the sizes of the two arrays and x is the number of unique elements in the union of the two arrays
*/
vector<int> unionBrute(vector<int> a, vector<int> b){
    set<int> s;
    vector<int> un;
    for(int i=0; i<a.size(); i++) s.insert(a[i]);         // add array1 elements
    for(int j=0; j<b.size(); j++) s.insert(b[j]);         // add array2 elements
    for(int x : s) un.push_back(x);                             // copy the elements of set to resulatant union vector
    return un;
}

// Optimal Approach : 2 pointer approach --> Time Complexity : O(n + m) __ Space Complexity : ---O(m+n)--- O(1)
// Here we consider space complexity to be O(1) and not O(m+n) because the output vector is not considered in space complexity
/*
Take 2 pointers i & j initially both 0 .. Compare the elements a[i] & b[j] and add the smaller one to the union vector and increment the
respective pointer (if a[i] is added then do i++) else do j++. If both are equal then add any one of them and increment both pointers.
while adding also check if the last added element (last element of union vector) is same as the current element (a[i] or b[j]) to avoid
duplicates in the union vector. If any of the array is exhausted then add the remaining elements of the other array to the union vector.
*/

vector<int> unionOptimal(vector<int> a, vector<int> b){
    vector<int> Union;
    int n = a.size(), m = b.size();
    int i=0, j=0;
    while(i<n && j<m){
        // If a[i] is smaller than b[j] then add a[i] to the union vector and increment i
        if(a[i] <= b[j]){
            // we need to make sure that union array won't have any duplicates so before adding any number to it we check the last value of the union
            // for this we use un.back() which gives the last element of the union vector
            // In case Union is empty un.back() will cause unexpected behavior so we check for condition when Union is empty i.e. when un.size() == 0
            if(Union.size() == 0 || Union.back() != a[i]) Union.push_back(a[i]);
            if(a[i] == b[j]) j++; // If both are equal then increment j as well
            i++;
        }
        // If b[j] is smaller than a[i] then add b[j] to the union vector and increment j
        else{
            if(Union.size() == 0 || Union.back() != b[j]) Union.push_back(b[j]);
            j++;
        }
    }
    // Loop terminates when either of the array is exhausted
    for(i; i<n; i++) if(Union.back() != a[i]) Union.push_back(a[i]); // add remaining elements of a to the union vector
    // we can also use while(j<m) but this is more readable
    for(j; j<m; j++) if(b[j] != Union.back()) Union.push_back(b[j]);
    return Union;
}

int main() {
    vector<int> a = {1, 1, 2, 3, 3, 5, 8, 8};
    vector<int> b = {2, 2, 4, 6, 7, 8};
    vector<int> Union = unionOptimal(a, b);             // There is a keyword named 'union' so we cannot use it as a variable name
    for(int x : Union) cout << x << " ";

    return 0;
}