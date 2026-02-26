/*
Leetcode - 1404. Number of Steps to Reduce a Number in Binary Representation to One : Medium

Given the binary representation of an integer as a string s, 
return the number of steps to reduce it to 1 under the following rules:
- If the current number is even, you have to divide it by 2.
- If the current number is odd, you have to add 1 to it.
It is guaranteed that you can always reach one for all test cases.

Examples :-

Input: s = "1101"
Output: 6
Explanation: "1101" corressponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14. 
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.  
Step 5) 4 is even, divide by 2 and obtain 2. 
Step 6) 2 is even, divide by 2 and obtain 1.  

Input: s = "10"
Output: 1
Explanation: "10" corresponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.  

Input: s = "1"
Output: 0

Constraints :-
- 1 <= s.length <= 500
- s consists of characters '0' or '1'
- s[0] == '1'
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexiy : O(n^2) __ Space Complexity : O(1)
int numSteps1(string s) {
    int n = s.size();
    int steps = 0;

    for (int i = n-1; i > 0; i--) {
        if (s[i] == '0') steps++;
        else {
            steps += 2;
            for (int j = i; j >= 0; j--) {
                if (s[j] == '1')
                    s[j] = '0';
                else {
                    s[j] = '1';
                    break;
                }
            }
            // if while adding 1 to the binary representation, the one gets carried till the MSB bit
            // then MSB would become 0 and a new '1' digit must be added theoretically.
            // the number would then have all zeros except this newly added '1' bit
            // so all the remaining steps would be simply dividing by 2
            // so instead of chaning the string to add 1 at start, we simply update steps and break
            if (s[0] == '0') {
                steps += (i - 0);
                break;
            }
        }
    }

    return steps;
}

// Optimal Approach (Greedy) : Time Complexity : O(N) __ Space Complexity : O(1)
/*
🔹 Core Idea
Rules:
- If number is even → divide by 2 → 1 step
- If number is odd → add 1, then divide by 2 → 2 steps
Since the number is large (given as string), we simulate from right to left and maintain a carry.

🔹 Why Traverse From Right?
Binary operations affect the least significant bit (LSB):
- 0 → even
- 1 → odd
Adding 1 to a binary number may generate a carry that propagates left.

🔹 What Carry Represents
carry = '1' means: We previously added 1 and that carry is still affecting higher bits.

🔹 Understanding the 4 Cases
We are effectively evaluating:
| current_bit + carry

✅ Case 1: 0 + 0 :- Result = 0 (even)
→ divide by 2
→ steps += 1

✅ Case 2: 1 + 0 :- Result = 1 (odd)
→ add 1 (makes it 0 with carry)
→ divide by 2
→ steps += 2
→ carry = 1

✅ Case 3: 0 + 1 :- Result = 1 (odd) (Same as Case 2)
→ steps += 2
→ carry = 1

✅ Case 4: 1 + 1 :- Result = 0 (carry 1 forward)
This is: 1 + 1 = 10
So:
- current bit becomes 0 (even)
- divide by 2 → steps += 1
- carry remains 1

🔹 Why Loop Stops at i > 0
We stop at MSB because: We never divide when number becomes 1.
The most significant bit is handled separately using final carry check.

🔹 Final Carry Handling
If carry is still '1' after loop:
Example: 11
Process:
    11
    +1
    100
So an extra step is needed → steps++

🔹 Clean Observation (Important)
Notice something:
(Except for MSB)
- Every 0 costs 1 step
- Every 1 costs 2 steps
- Except when there is a carry interacting
*/
int numSteps(string s) {
    int n = s.size();
    char carry = '0';
    int steps = 0;

    // we traverse the number from right end bit by bit
    // if current bit is '0', it means even case, divide by 2 case, so steps should increment by 1
    // if current bit is '1', it means odd case, we have to firstly add 1 to it to make it even 
    // and then divide it by 2, so for '1' bit the no. of steps required is 2.

    // when adding '1' we need to propagate a carry bit also and this carry bit might change current bit also
    
    // Various Cases :- 
    
    // Case - 1: Current bit = '0' and Carry bit = '0'
    // even condition, so steps increment by 1, carry bit remains '0'
    
    // Case - 2: Current bit = '1' and Carry bit = '0'
    // odd condition, so steps should increment by 2 and carry bit should become '1' to propagate the carry
    
    // Case - 3: Current bit = '0' and Carry bit = '1'
    // the current bit becomes '1' due to addition of the propagated carry bit
    // steps thus increments by 2 as the current bit has become '1' 
    // a new carry must be propagated forward for this '1' current bit, thus carry remains '1'
    
    // Case - 4: Current bit = '1' and Carry bit = '1'
    // the current bit should become '0' due to addition of the carry bit. 
    // so, steps should increment by 1, but at the same time carry bit of '1' must be propagated forward
    // so, carry bit should remain '1'
    
    for (int i = n - 1; i > 0; i--) {
        // Case - 1
        if (s[i] == '0' && carry == '0') steps++;

        // Case - 2
        else if ( s[i] == '1' && carry == '0' ) {
            steps += 2;
            carry = '1';
        }
        
        // Case - 3
        else if ( s[i] == '0' && carry == '1' ) {
            steps += 2;
            carry = '1';
        }
        
        // Case - 4
        else {
            steps++;
            carry = '1';
        }
    }

    // if at the end, carry bit is '1', it means this carry must be added to the MSB-1 bit
    // thus making the MSB bit '0' and need to add a new MSB of '1' 
    // like '11' becomes '100' due to addition of carry bit
    // in this case, the no. of steps inrease by 1 due to addition of carry bit (if it is '1')
    if (carry == '1') steps++;

    return steps;
}

int main() {
    return 0;
}