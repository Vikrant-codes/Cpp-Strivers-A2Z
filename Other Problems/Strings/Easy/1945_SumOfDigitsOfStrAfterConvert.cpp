/*

*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach 1 :- Time Complexity : O(n+k) __ Space Complexity : O(2*n)
/*
- Build the converted string where each character is replaced by its equivalent position in alphabet.
- Traverse in this converted string to find the 1st transformed digit sum.
- This sum will be small so it can be stored in an integer
- Now, we just need to get the digit sum repeatedly for the remaining k-1 times.
- Run a loop for remaining k-1 times and update sum repeatedly.
- Return sum after loop exits

An early break condition can be used when running the k-1 iteration, 
if sum becomes single digit number then running the loop for next iterations will be unncessary.

This early exits is not that important since k is in range [1, 10], 
so at max this early exit will save just about 9 iterations.

>> Complexity Analysis :-

Time Complexity: O(n + k)
- Building the transformed string and summing its digits takes O(n), 
where n is the length of s (the transformed string has at most 2n digits, which is still O(n)).
- Each of the remaining k - 1 transformations processes a very small integer 
(at most 1000 after the first transformation), so each takes O(1). Thus, this part contributes O(k).
Overall: O(n + k).

Space Complexity: O(n)
The transform string stores up to 2n characters, so the extra space used is O(n).
*/
int getDigitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int getLucky1(string s, int k) {
    string transform = "";

    for (char ch : s)
        transform += to_string(ch - 'a');
    
    int sum = 0;
    for (char d : transform) {
        sum += (d - '0');
    }

    int i = k-1;
    while (i--) {
        sum = getDigitSum(sum);

        if (sum < 10) 
            return sum;
    }
    
    return sum;
}

// Naive Approach 2 :- Time Complexity : O(n+k) __ Space Complexity : O(2*n)
/*
Instead of storing the sum as an integer and then using digit extraction logic to get the sum of digits,
we can simply stored the sum inside a string and can simply traverse the string to get the digit sum.

- Build the converted string
- For k iterations:
    - find the sum of digits in the converted string (traverse the string to get the sum)
    - change the converted string as it must now store this new sum as its content
    - if at any moment sum becomes less than 10, then any further iterations are useless. So we can do early exit.
- Converted string contains the resultant sum, so return the int value of that string as the answer.

>> Complexity Analysis

Time Complexity: O(n + k)
- Building the initial converted string takes O(n), where n is the length of s.
- During the first transformation, the string has at most 2n digits, so processing it takes O(n).
- After the first transformation, the value is at most 1000, so the string length becomes at most 4 digits. 
    Each of the remaining k - 1 transformations therefore takes O(1).
- Overall, the complexity is O(n + k), which is effectively O(n) since k ≤ 10.

Space Complexity: O(n)
The transform string stores the converted representation of s, 
requiring at most 2n characters, so the auxiliary space is O(n).
*/

int getLucky2(string s, int k) {
    string transform = "";

    for (char ch : s)
        transform += to_string(ch - 'a' + 1);
    
    while (k--) {
        int sum = 0;
        
        for (char d : transform) {
            sum += (d - '0');
        }

        if (sum < 10)
            return sum;
        
        transform = to_string(sum);
    }
    
    return stoi(transform);
}

// Optimal Approach :- Time Complexity : O(n+k) __ Space Complexity : O(1)
/*
The key observation is that we don't need to actually construct the huge number after converting the string.
For each character:
- Find its alphabet position (1 to 26).
- Instead of appending it to a string, directly add the sum of its digits.
    1 → 1
    12 → 1 + 2 = 3
    26 → 2 + 6 = 8
This gives us exactly the same result as the first transform.

For example:
"leetcode"
    l -> 12 -> 1+2 = 3
    e -> 5  -> 5
    e -> 5  -> 5
    t -> 20 -> 2+0 = 2
    c -> 3  -> 3
    o -> 15 -> 1+5 = 6
    d -> 4  -> 4
    e -> 5  -> 5
Total = 3+5+5+2+3+6+4+5 = 33

This is exactly what we'd get after
    12552031545
    ↓
    1+2+5+5+2+0+3+1+5+4+5 = 33
So we've already completed the first transformation without ever creating the converted number.
Then perform the remaining k-1 digit-sum operations.

>> Time Complexity
First pass over the string: O(n)
Each subsequent transformation operates on a very small number.

Why is it small?
Maximum string length = 100.
Largest digit sum contributed by one character is for s = 19, whose digit sum is 1 + 9 = 10
So after the first transformation: maximum sum = 100 × 10 = 1000
Each later transformation processes at most a 4-digit number (1000), which is constant time.
Therefore,
Time: O(n)
Space: O(1)
This is the optimal solution in both time and space.
*/

int getLucky(string s, int k) {
    int sum = 0;
    for (char ch : s) {
        int val = ch - 'a' + 1;
        // val will be in range [1, 26]
        // if val is single digit number, directly add to sum
        if (val < 10)
            sum += val;
        
        // else val is double digit number (range [10, 26]), we can get its digits by doing val/10 and val%10
        else 
            sum += val / 10 + val % 10;
    }

    // now sum already contains the sum of digits after one transformation
    // for the remaining k - 1 transformations, sum digits repeatedly
    k--;            // decrement value by 1 because sum already holds 1 transformation sum
    
    while (k--) {
        sum = getDigitSum(sum);
    }
    
    return sum;
}

int main() {

    return 0;
}