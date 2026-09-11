/*
Leetcode - 1742. Maximum Number of Balls in a Box : Easy

You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit inclusive 
(i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to infinity.

Your job at this factory is to put each ball in the box with a number equal to the sum of digits of the ball's number. 
For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 
and the ball number 10 will be put in the box number 1 + 0 = 1.

Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.

Examples :-

Input: lowLimit = 1, highLimit = 10 __ Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
Box 1 has the most number of balls with 2 balls.

Input: lowLimit = 5, highLimit = 15 __ Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
Ball Count:  1 1 1 1 2 2 1 1 1 0  0  ...
Boxes 5 and 6 have the most number of balls with 2 balls in each.

Input: lowLimit = 19, highLimit = 28 __ Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 12 ...
Ball Count:  0 1 1 1 1 1 1 1 1 2  0  0  ...
Box 10 has the most number of balls with 2 balls.

Constraints :-
- 1 <= lowLimit <= highLimit <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition (brief & clear)

>> Why hashing (frequency array)?
Each ball is assigned to a box based on the sum of its digits. Multiple balls can map to the same box, 
so we need to count frequencies of how many balls go into each box → classic hashing / frequency counting use case.

>> Why only size 45?
Constraints: 1 ≤ ball ≤ 10^5
Maximum digit sum for 99999 = 9+9+9+9+9 = 45 ..... (digit sum will be maximum when all digits are 9)
Minimum digit sum = 1

So:
Possible box numbers are 1 to 45
Hence a fixed array of size 45 is enough (constant space)

>> Complexity Analysis

→ Time Complexity

Let: n = highLimit - lowLimit + 1
Each number has at most 6 digits (number can be 10^5 at max and 10^5 has 6 digits) 
Digit sum calculation: O(6) ≈ O(1)
Loop over all balls: O(n)
Final max scan over 45 boxes: O(45) ≈ O(1)

✅ Overall Time Complexity: O(n)

→ Space Complexity
Hash array of fixed size 45.
✅ Space Complexity: O(1)
*/

// helper function - returns the box no for a ball (i.e. the digit sum of the ball number)
int getBoxNo(int ball) {
    int ans = 0;
    while (ball != 0) {
        ans += ball % 10;
        ball /= 10;
    }
    return ans;
}

int countBalls(int lowLimit, int highLimit) {
    vector<int> hashBox(45);

    for (int ball = lowLimit; ball <= highLimit; ball++) {
        int box = getBoxNo(ball);
        hashBox[box-1]++;
    }
        
    int mx_balls = 0;

    for (int& ball_count : hashBox)
        if (ball_count > mx_balls)
            mx_balls = ball_count;
    
    return mx_balls;
}

// Same logic but here we are not using a helper function
int countBalls2(int lowLimit, int highLimit) {
    vector<int> hashBox(45);

    for (int a = lowLimit; a <= highLimit; a++) {
        int digSum = 0;
        int ball = a;
        while (ball != 0) {
            digSum += ball % 10;
            ball /= 10;
        }
        hashBox[digSum-1]++;            // 0-based indexing in array so box no in array is digSum - 1.
    }

    int mx_balls = 0;

    for (int& ball_count : hashBox)
        if (ball_count > mx_balls)
            mx_balls = ball_count;
    
    return mx_balls;
}

int main() {
    return 0;
}