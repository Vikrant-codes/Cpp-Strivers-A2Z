/*
Majority Element <-Leetcode : Easy-> :- Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
int majorityBrute(vector<int> arr) {
    int n = arr.size();
    for(int i=0; i<n; i++){
        int cnt = 1;
        for(int j=i+1; j<n; j++){
            if(arr[j] == arr[i]) cnt++;
        }
        if (cnt > n/2) return arr[i];
    }
    return -1;
}

// Better Approach : Time Complexity : unorder_map -> O(n) {Best Case} , O(n^2) {Worst Case}, map -> O(n log n) __ Space Complexity : O(n)
int majorityHash(vector<int> arr){
    unordered_map<int, int> mpp;
    for(int x : arr) mpp[x]++;
    for(auto y : mpp)  if(y.second > arr.size()/2) return y.first;
    return -1;
}

// Optimal Approach : 'Moore's Voting Algorithm' -> Time Complexity : O(n) __ Space Complexity : O(1)
/*
We start by considering the first element as the answer and we iterate through the array and increase the count if the encountered element is 
same as answer variable, if it isn't then we decrement the count. If at a certain moment the count becomes zero this signifies that the array upto 
the current element have no majority element since if it had one then the count would've never reached 0. So when the count reaches zero we take the
next element as ans and do the same thing for the remaining array. 
EX - consider arr = {7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5} 
we start by conisdering ans = 7 and when we do the specified task we notice that the count becomes 0 at index 5 (array length 6) since at that index
the there are 3 7's and other elments are also 3 so there is no majority element upto index 5. So we now consider the next element (5) to be the ans
and start doing the same operations. This time the count reaches 0 after encountering just 2 elements (5 increases count to 1 and 7 decreases to 0) so 
we can say that upto this index there is no majority element also (upto index 7) now we again take 5 as ans and again see that after encountering 4 more
elements the count becomes 0 again (upto index 11) so we again take next element as ans i.e. 5 and this time since all remaining elements are 5 so count
becomes 4. Thus we get the majority element to be 5. 
But does the last ans element is always the majority ?? 
consider array:- {7,7,5,7,5,1,5,7,5,5,7,7,1,1,1,1} this time if we use the algo we see that upto index 11 there is no majority (count becomes 0) so 
we consider 1 to be ans and check for its count and the loop terminates having 1 as ans. But 1 only appears 5 times in the array of length 16 so it 
can't be the majority element. The only reason we got 1 as the ans was because upto index 11 there was no majority but 
in the subarray arr[11 : 16] 1 was the majority. since there was no majority element upto index 11 so if a majority elements exists in the array 
it should be determined by the last remaining portion. 
So if it's not guaranteed that array has a majority element we check the no of appearances of the ans element after the algo is finished to check 
whether the ans element appears more than n/2 or not (if it does it is the answer)
Steps ->
1. Apply Moore's algo
2. Verify whether the ans element is actually the majority element or not
*/
int MooreVotingAlgo(vector<int> arr){
    int el, cnt = 0;
    for (int x : arr) {
        if (cnt == 0) {
            cnt = 1;
            el = x;
        }
        else if (x == el) cnt++;
        else cnt--;         //  if x is not equal to ans element do cnt--
    }
    // If it is guaranteed that the array has a major element then it's not necessary to verify the answer, in that case simply return ele
    cnt = 0;
	for(int x : arr) if (x == el) cnt++;
    return cnt > arr.size()/2 ? el : -1;
}

int main() {
    vector<int> arr = {7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5};
    vector<int> arr2 = {7,7,5,7,5,1,5,7,5,5,7,7,1,1,1,1};
    int major = MooreVotingAlgo(arr);
    cout << "Majority Element : " << major;
    return 0;
}