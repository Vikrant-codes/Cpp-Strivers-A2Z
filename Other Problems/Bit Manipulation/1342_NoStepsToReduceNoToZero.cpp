/*
Leetcode - 1342. Number of Steps to Reduce a Number to Zero : Easy

Given an integer num, return the number of steps to reduce it to zero.
In one step, if the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.

Examples :-

Input: num = 14 __ Output: 6
Explanation: 
Step 1) 14 is even; divide by 2 and obtain 7. 
Step 2) 7 is odd; subtract 1 and obtain 6.
Step 3) 6 is even; divide by 2 and obtain 3. 
Step 4) 3 is odd; subtract 1 and obtain 2. 
Step 5) 2 is even; divide by 2 and obtain 1. 
Step 6) 1 is odd; subtract 1 and obtain 0.

Input: num = 8 __ Output: 4
Explanation: 
Step 1) 8 is even; divide by 2 and obtain 4. 
Step 2) 4 is even; divide by 2 and obtain 2. 
Step 3) 2 is even; divide by 2 and obtain 1. 
Step 4) 1 is odd; subtract 1 and obtain 0.

Input: num = 123 __ Output: 12

Constraints :- 0 <= num <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
/*
Simulate the process by running a loop till the number becomes 0.
In each iteration if the no. is even we divide it by 2 else decrement the no. 
Increment the no. of steps in each iteration.
Return the steps after the loop ends.

⏱ Time Complexity
-- Worst case (e.g., all bits are 1):
• Each 1 → subtract 1
• Then divide by 2
-- Total operations proportional to: 
• number of bits
• plus number of 1s

Total Complexity : O(log n)

💾 Space Complexity : Only constant variables : O(1)
*/
int numberOfStepsSimulation(int num) {
    int steps = 0;
    while (num != 0) {
        if (num % 2 == 0) num = num / 2;
        else num = num - 1;
        steps++;
    }
    return steps;
}

// Bit Manipulation Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
/*
Intuition 
If the no is even then we divide by 2, if odd we subtract 1. 
This subtraction of 1 will then make the no. even and then again we will have to divide by 2 in the next step.
So, in a way we need to divide by 2 but if the no is odd our works increments 1 step due to firstly dividing by 1 then dividing.

Now, if we think about binary, even no. ends with Least Significant Bit (LSB) 0, while odds have LSB 1.
So, if we traverse the binary representation of the no. then 
    for each 1 bit we will have to work 2 steps, and,  
    for 0 we just need 1 step.
This division by 2 can be easily done by right shifting the binary representation.

Binary insight
1️⃣ If the last bit is 0 (no. is even) : ...0
    Number is even
    Operation: divide by 2
    In binary → right shift
    Cost = 1 step
2️⃣ If the last bit is 1 (odd, except MSB)
    Operation sequence :-
        1) subtract 1 → makes it even 
        2) divide by 2 (right shift)
    Binary effect : ...1 → (subtract 1) ...0 → (divide by 2) right shift
    Cost = 2 steps

Now, for the MSB, we don't need to work 2 steps as our main goal is to make the no. zero and for that, 
if we subtract 1 from MSB, the no. will become 0 and we won't have to right shift / divide by 2 for the MSB.
Thus, The most significant 1 does not need : subtract 1 and divide by 2 (it only needs subtract 1)
Thus, we subtract 1 from the total steps calculated this way due to the MSB case 

| Each 0 costs one divide, each 1 costs a subtract + divide — except the last 1.

Algorithm (binary method) :-
1. Convert number to binary
2. Traverse each bit:
    • If bit = 0 → steps += 1
    • If bit = 1 → steps += 2
3. Return steps - 1

⏱ Time Complexity
• Each loop iteration removes one binary digit (num >>= 1)
• Number of iterations = number of bits in num = ⌊log₂(num)⌋ + 1
| Total time complexity : O(log n)

💾 Space Complexity : Uses only a few integer variables : O(1)
*/
/*
>> How to “traverse binary” without converting ?
Two facts
| num & 1 → tells you if the last bit is 1 or 0
    because 1's binary representation is (00..1) and for any binary no. xxxxxx, 
    this num & 1 will depend only on the last bit of num 
    (because & needs both bits 1 and '1' has only the last bit set to 1, so num & 1 depends on last bit of 1)
| num >> 1 → removes the last bit (divide by 2)
    Right shifting 1 bit is the same as dividing the no. by 2.

So, in the code, while traversing, we check the last bit by num & 1.
    If num & 1 is true (means last bit of num is 1, num is odd), so steps increment by 2.
    Else (last bit of num is 0, num is even), so steps increment by 1.

Dry run Example → num = 14, binary = 1110
Iteration :- 
1) 14 & 1 = 1110 & 0001 → 0 (num & 1 is false, last bit is 0, num is even) → +1 (add 1 to steps), right shift → 7 (num becomes 7)
2) 7 & 1 = 111 & 001 → 1 (num & 1 is true, last bit 1 is 1, num is odd) → +2 (add 2 to steps), right shift → 3
3) 3 & 1 = 11 & 01 → 1 (last bit 1) → +2 (add 2 to steps), right shift → 1
4) 1 & 1 = 1 & 1 → 1 (last bit 1) → +2 (add 2 to steps), right shift → 0
steps = 7. 
return steps - 1 = 7 - 1 = 6. (since we consider only 1 step for MSB thus subtract 1 from total steps)
*/

int numberOfSteps(int num) {
    if (num == 0) return 0;
    
    int steps = 0;
    while (num > 0) {
        if (num & 1)
            steps += 2; // odd → subtract 1 + divide by 2
        else 
            steps += 1; // even → divide by 2
        
        num >>= 1;      // move to next bit by shifting bits to right
    }
    return steps - 1;
}

int main() {
    return 0;
}