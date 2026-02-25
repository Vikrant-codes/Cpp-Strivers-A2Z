/*
Leetcode - 1356. Sort Integers by The Number of 1 Bits : Easy

You are given an integer array arr. 
Sort the integers in the array in ascending order by the number of 1's in their binary representation and 
in case of two or more integers have the same number of 1's you have to sort them in ascending order.

Return the array after sorting it.

Examples :-

Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explantion: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]

Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
Output: [1,2,4,8,16,32,64,128,256,512,1024]
Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.
 
Constraints :-
- 1 <= arr.length <= 500
- 0 <= arr[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Custom Comparator Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
    /*
    We use a custom comparator to compare two integers on the basis of no. of 1 bits they have
    Time Complexity Analysis:-
    - compare function counts the 1 bits of two integers and compares them on the basis of that
    - The maximum values of integer according to given constraints is 10^4 which can be represented in around 13-14 bits.
    - So, the while loop inside compare runs for 13-14 iterations. Two while loops are used (one for both integers).
    - Thus, complexity of compare function = O(28) ~ O(1)
    - Sort takes O(n log n) and calls compare for each comparison. 
    So, total time complexity = O(n log n) * O(28) ~ O(n log n)
    */ 

    static bool compare(int a, int b) {
        int x = a, y = b;           // values are stored in temporary variables so not to change original values
        int cnt1 = 0, cnt2 = 0;     // cnt1 & cnt2 = count of set bits (1 bits) in x & y
        while (x) {
            cnt1 += x & 1;
            x >>= 1;
        }
        while (y) {
            cnt2 += y & 1;
            y >>= 1;
        }

        if (cnt1 == cnt2) 
            return a < b;
        return cnt1 < cnt2;
    }

    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), compare);

        return arr;
    }

    /*
    Why we used 'static' to define comparator function?
        If we didn't used the static keyword, the function 'bool compare(int a, int b)' 
        will remain 'non-static' and internally it becomes: 'bool compare(Solution* this, int a, int b)'
        But sort() expects: bool compare(int a, int b)
        So, using the compare function as non-static gives error. Thus, we need to define it as static
    */
};

int main() {
    return 0;
}