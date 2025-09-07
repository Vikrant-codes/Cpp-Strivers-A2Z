/*
You are given an array of ‘N’ integers. You need to find the length of the longest sequence which contains the consecutive elements.
The subsequence need not to be necessarily contiguous. 
EX-> {1, 9, 3, 10, 4, 20, 2} in this array the longest consecutive subsequence is {1,2,3,4} which is of length 4 and these elements are not stored in contiguous locations.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^3)__ Space Complexity : O(1)
// Approach -> For every element arr[i], treat it as the start of a sequence and check if x + 1, x + 2, ... exist in the array using linearSearch.
/*
Complexity Analysis 
Let’s assume the worst case — where the array has consecutive numbers.

Example:- arr = {1, 2, 3, ..., n}
Now go through the outer loop:
For i = 0, x = 1, you check: Is 2 in the array? ✅ Is 3 in the array? ✅ ... Is n in the array? ✅ → That’s n−1 linearSearch calls
For i = 1, x = 2: Is 3 in the array? ✅ ...Is n in the array? ✅ → That’s n−2 linearSearch calls
...
For i = n-2, you check only one value
For i = n-1, no linearSearch at all

Total number of linearSearch calls: (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)

Each of those calls takes O(n) time, So total cost = O(n²) calls × O(n) time per call = O(n³) total time
*/
bool linearSearch(vector<int> arr, int x){
    for(int i=0; i<arr.size(); i++) {
        if (arr[i] == x) return true;
    }
    return false;
}

int longestSubseqBrute(vector<int> arr){
    int longest = 1;
    int n = arr.size();
    for(int i=0; i<n; i++){
        int x = arr[i];         // consider this element to be the start of a sequence
        int count = 1;          // initial count for this consecutive sequence
        while(linearSearch(arr, x+1)) {
            x = x+1;            // increment x to check for the next consecutive element
            count++;            // increase the length of the current sequence
        }
        longest = max(longest, count);
    }
    return longest;
}

// Better Approach (Using Sorting) : Time Complexity : O(n log n)__ Space Complexity : O(1)
/*
Sort the array then start iterating through it. Maintain a lastSmaller element to check for the consecutive last smaller element. Initially last smaller is INT_MIN.
While iterating if the encountered element is 1 greater than lastSmaller this means it is a part of the current consecutive subsequence so we increase the current count and
also we give lastSmaller value as arr[i]. But in case array have duplicates then it might have duplicates and in such cases we don't need to increase the count or update the 
lastSmaller. But if lastSmaller is neither equal to arr[i] and nor arr[i] == lastSmaller + 1, this means the current element is not a part of the consecutive sequence and 
thus is a part of another sequence so we re-assign count as 1 and lastSmaller as arr[i]. 
*/
int longestSubseqBetter(vector<int> arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    int lastSmaller = INT_MIN;
    int cnt = 0, longest = 1;
    for(int i=0; i<n; i++) {
        if(arr[i] == lastSmaller + 1) {
            cnt++;
            lastSmaller = arr[i];
        }
        else if(lastSmaller != arr[i]) {
            cnt = 1;
            lastSmaller = arr[i];
        }
        longest = max(longest, cnt);
    }
    return longest;
}

// Optimal Approach (Using unordered_set) : Time Complexity : O(N) + O(N+N) = O(3N) __ Space Complexity : O(N)
/*
Complexity Analysis :- O(N) for adding elements to the set and now we iterate through the set which is like O(N) but if we encounter a starting element we check for its 
consecutive sequence until it exists in the set which is O(N) in total since in total the length of the consecutive sequence can be N at max and this N iteration will only 
happen once. Even if array has multiple consecutive sequences of size n1, n2 etc even then the while loop will run only for n1, n2 ... times that too for the starting element 
only and so this would also only add at most N iterations to the for loop. So complexity of this for loop and while loop will be O(N + N) = O(2N)
*/
/*
Add the array elements to the set (will take only distinct elements). Now iterate through the set elements and check for the starting points of consecutive subsequences. We can 
check whether the current element is a starting point of a sequence by checking whether element-1 exists in set or not. Since if element-1 exists then element is not the starting.
Once we find that a certain element is starting point we try to find its consecutive subsequence by repeatedly checking for the existence of next consecutive elements in the set. 
This is kind of similar to brute force approach. During this repeated checking we also do count++ and update the longest_count if current_count is more. 
Ex -> arr = [102, 101, 101, 4, 3, 2, 100, 3, 103, 105, 2, 1, 1, 104, 1, 2]
set = [102, 101, 4, 3, 2, 100, 103, 105, 1, 104]
iterating through the set :- 
-> x = 102 :- does 101 exists ? yes, the condition won't enter if so do nothing
-> x = 101 :- does 100 exists ? yes, do nothing
-> x = 4 :- does 3 exists ? yes, do nothing
-> x = 3 :- does 2 exists ? yes, do nothing
-> x = 2 :- does 1 exists ? yes, do nothing
-> x = 100 :- does 99 exists ? no, so this 100 is possibly the staring point of some consecutive sequence. we then initialize count by 1 and repeatedly check for existence of 
x+1 in the set and if it exists incremenet count and also do x++ to check for next consecutive element. Now for x = 100 we do count = 1 and check for 101, it exists we update 
count to 2 and check for 102, again it exists update count to 3 we .... check for 105, it exists count becomes 6 now check for 106 it doesn't exists in the set so while loop ends
with count = 6.. update the longest if count is greater than longest. 
-> x = 103 :- does 102 exists ? yes, do nothing
-> x = 105 :- does 104 exists ? yes, do nothing
-> x = 1 :- does 0 exists ? no, so we repeat the same process to find the length of consecutive sequence of 1 which turns out to be 4 but since longest = 6 we don't update it
-> x = 104 :- does 103 exists ? yes, do nothing
iteration ends and we return longest which is 6
*/
int longestSubseq(vector<int> arr) {
    int n = arr.size();
    if(n == 0) return 0;        // if arr = [] then return 0
    int longest = 1;
    unordered_set<int> st;
    for(int x : arr) st.insert(x);
    for(int x : st) {
        // If element - 1 doesn't exist that means the element is a starting point and so we find the length of that consecutive sequence whose starting is element
        if (st.find(x-1) == st.end()) {
            int cnt = 1;
            while(st.find(++x) != st.end()) cnt++;
            // this above while loop is same as while(st.find(x+1) != st.end()) { cnt++; x = x+1; }
            longest = max(longest, cnt);
        }
        // If element-1 exists in set that means the element is not the starting point so do nothing and hence no code required for this condition        
    }
    return longest;
}

int main() {
    vector<int> arr = {102, 101, 101, 4, 3, 2, 100, 3, 103, 105, 2, 1, 1, 104, 1, 2};
    int ans = longestSubseq(arr);
    cout << "Longest Consecutive Subsequence Length: " << ans << endl;
    return 0;
}