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
int numberOfSteps1(int num) {
    int steps = 0;
    while (num != 0) {
        if (num % 2 == 0) num = num / 2;
        else num = num - 1;
        steps++;
    }
    return steps;
}

// Better Approach : Time Complexity : O(log n) __ Space Complexity : O(1)
/*
>> Intuition :
If the no is even then we divide by 2, if odd we subtract 1. 
This subtraction of 1 will then make the no. even and then again we will have to divide by 2 in the next step.
So, in a way we need to divide by 2 but if the no is odd our works increments by 1 step 
since we need to subtract 1 from the no. before dividing it.

Now, if we think about binary, even no. ends with Least Significant Bit (LSB) 0, while odds have LSB 1.
So, if we traverse the binary representation of the no. then 
    for each 1 bit we will have to work 2 steps, and,  
    for 0 we just need 1 step.
This division by 2 can be easily done by right shifting the binary representation by 1 bit.

Binary insight
1️⃣ If the last bit is 0 (no. is even) : ...0
    Number is even
    Operation: divide by 2 (In binary → right shift)
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
But, since MSB 1 will be odd, our logic would do 'steps += 2' even for this MSB 1 bit.
Due to this, the total steps woulbe be 1 more than required due to counting 2 steps even when num becomes 1 (MSB 1),
thus, we do steps - 1 before returnin it. 

| Each 0 costs one divide, each 1 costs a subtract + divide — except the last 1.

Time Complexity : O(log n) since we are dividing number 'n' by two till it becomes zero.
*/

int numberOfSteps2(int num) {
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

int numberOfSteps3(int num) {
    if (num == 0) return 0;
    
    int steps = 0;
    while (num > 0) {
        if (num % 2 == 1)
            steps += 2; // odd → subtract 1 + divide by 2
        else 
            steps += 1; // even → divide by 2
        
        num /= 2;      // divide by 2
    }
    return steps - 1;
}

// Optimal Approach :- Time Complexity : O(1) __ Space Complexity : O(1)
/*
Think in terms of what operations actually happen in binary, not decimal.
The rules are:
- If even → divide by 2 → right shift
- If odd → subtract 1 → makes it even

Key observation
In binary:
- Dividing by 2 = removing the last bit (right shift)
- Subtracting 1 from an odd number = turning the last 1 into 0

Now imagine processing the number bit by bit (from right to left)
Take an example: 14 = 1110
We process from rightmost bit:
• If bit is 0 → just one operation (divide by 2)
• If bit is 1 → two operations:
    • subtract 1 → make it 0
    • divide by 2 → remove it

So contribution of each bit:
• 0 → 1 step
• 1 → 2 steps

BUT there's a catch 👇
For the most significant 1 (leftmost bit): We do NOT need the final divide
Because once we reach 1, we just subtract → 0 (done)
So:
- Every 1 contributes 2 steps
- Except the last (leftmost) 1, which contributes only 1 step

Putting it together
Let:
- total bits = bitsSize
- number of 1s = cnt1bits
Then:
- Each bit → at least 1 step → contributes 'bitsSize'
- Each 1 → needs one extra step (subtract operation) → contributes 'cnt1bits'
- But we overcounted 1 extra step (for the last MSB). So: answer = bitsSize + cnt1bits - 1
| answer = bitsSize + cnt1bits - 1
*/
// Using built-in methods -- These methods are effectively O(1)
int numberOfSteps(int num) {
    if (num == 0) return 0;
    
    return __builtin_popcount(num) + (32 - __builtin_clz(num)) - 1;
    // __builtin_popcount(num) -> returns no. of set bits in binary representation of num
    // __builtin_clz(num) -> returns no. of leading zeros in binary represntation of num
    // (32 - __builtin_clz(num)) -> This will give us the count of bits required to represent the number num
}

// Without Using built-in methods ... if we try to implement the built-in methods, it would take O(log n) complexity
int numberOfSteps_2(int num) {
    if (num == 0) return 0;
    
    int cnt1bits = 0;       // no. of set bits
    int bitsSize = 0;       // no. of total bits required to represent the number

    while (num) {
        if (num & 1) cnt1bits++;
        bitsSize++;
        num >>= 1;
    }

    return bitsSize + cnt1bits - 1;
}

int main() {
    return 0;
}