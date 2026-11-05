/*
Leetcode - 1423. Maximum Points You Can Obtain from Cards : Medium

There are several cards arranged in a row, and each card has an associated number of points. 
The points are given in the integer array cardPoints.
In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
Your score is the sum of the points of the cards you have taken.
Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Examples :-

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. 
However, choosing the rightmost card first will maximize your total score. 
The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards. 

Constraints :-
• 1 <= cardPoints.length <= 10^5
• 1 <= cardPoints[i] <= 10^4
• 1 <= k <= cardPoints.length
*/

#include <bits/stdc++.h>
using namespace std;

// My Solution: Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Key Observation — Think About What NOT to Pick

At first, the problem might seem a little tricky because we can pick cards 
from either the beginning or the end of the array. 
Trying to directly maximize the sum by considering different combinations of cards picked from both ends 
can make the problem unnecessarily complicated.

Instead, we can approach it using a complementary approach: 
Rather than figuring out which k cards to pick, let's figure out which cards we should NOT pick.

- We are allowed to pick exactly k cards from either end of the array.
- This means the cards we don't pick will always form one contiguous subarray somewhere in the middle.
- Since we pick k cards out of n cards, the number of cards left behind will be exactly n-k.

Now comes the important observation:
Since we want to maximize the sum of the selected cards, 
we should leave behind the contiguous subarray having the minimum possible sum.

Therefore, instead of finding the maximum sum of k cards from the two ends, 
we can find the minimum sum subarray (window) of size n-k and subtract it from the total sum of the array.

This gives us: Maximum Score = Total Sum - Minimum Window Sum

Once we make this observation, the problem becomes a straightforward fixed-size sliding window problem, 
where we maintain the minimum window sum instead of the maximum.

>> Optimal Approach — Fixed-Size Sliding Window

First, calculate the total sum of the array. 
Then, our task is to find the minimum sum of any contiguous subarray of size n-k, 
representing the cards we choose not to pick.

We can maintain a fixed-sized window of n-k elements and calculate its sum. 
As we slide the window across the array, we efficiently update its sum 
by adding the newly entering element (cardPoints[r]) and 
subtracting the element leaving the window (cardPoints[l]).

For every window of the required size, update the minimum window sum (min_win_sum). 
After considering all possible windows, subtract this minimum sum from the total array sum to obtain the maximum score.

>> Complexity Analysis

- Time Complexity: O(2n)
  - Calculating the total sum takes O(n).
  - Sliding the window across the array also takes O(n), as both pointers traverse the array at most once.

- Space Complexity: O(1) — We only use a constant number of variables.
*/
int maxScore1(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int len = n - k;

    int total_sum = 0;
    for (int x : cardPoints) 
        total_sum += x;
    
    if (k == n) return total_sum;

    int sum = 0, min_win_sum = INT_MAX;
    int l = 0, r = 0;

    while (r < n) {
        sum += cardPoints[r];

        if (r - l + 1 == len) {
            min_win_sum = min(min_win_sum, sum);
            sum -= cardPoints[l];
            l++;
        }

        r++;
    }

    return total_sum - min_win_sum;
}

// other implementation
int maxScore2(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();

    int total_sum = 0;
    
    for (int x : cardPoints)
        total_sum += x;
    
    int sum = 0;
    int len = n - k;

    for (int i = 0; i < len; i++)
        sum += cardPoints[i];

    int min_win_sum = sum;

    for (int i = len; i < n; i++) {
        sum += cardPoints[i] - cardPoints[i - len];
        min_win_sum = min(min_win_sum, sum);
    }

    return total_sum - min_win_sum;
}

// Striver's solution: Time Complexity : O(2k) __ Space Complexity : O(1)
/*
>> Key Observation

Since we can pick cards only from either end, we have a few possible combinations:
- Pick all k cards from the left.
- Pick k-1 cards from the left and 1 from the right.
- Pick k-2 cards from the left and 2 from the right.
- Continue this way until we pick all k cards from the right.
The important observation is that we don't need to try every possible combination independently.

We can start by selecting all k cards from the left. Then, gradually shift our selection from left to right:
- Remove one card from the left selection.
- Add one card from the right selection.
- Calculate the new sum and update the maximum.
This way, we systematically consider all possible combinations of picking k cards from the two ends.

>> Approach — Two Pointers / Greedy Selection

Initially, calculate the sum of the first k elements, assuming we pick all k cards from the left. 
Store this as our initial maximum sum (maxSum).

Now, we gradually replace the cards selected from the left with cards from the right. 
We use i to traverse the initially selected left portion in reverse order and 
rightInd to traverse the array from the right end.

In every iteration:
1. Remove cardPoints[i] from leftSum, since we are no longer selecting that card from the left.
2. Add cardPoints[rightInd] to rightSum, since we are now selecting that card from the right.
3. Calculate the combined sum (leftSum + rightSum) and update maxSum if we have found a better selection.

By repeating this process k times, 
we consider every possible distribution of the k selected cards between the left and right ends, 
from selecting all k cards on the left to selecting all k cards on the right.

>> Complexity Analysis
- Time Complexity: O(2k) — Calculating the initial left sum takes O(k), and the subsequent loop takes O(k). 
  Overall, O(2k), which is bounded by O(n).
- Space Complexity: O(1) — Only a constant number of variables are used.
*/
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int leftSum = 0, rightSum = 0;

    for (int i = 0; i < k; i++) 
        leftSum += cardPoints[i];
    
    int maxSum = leftSum;
    int rightInd = n - 1;

    for (int i = k - 1; i >= 0; i--) {
        leftSum -= cardPoints[i];
        rightSum += cardPoints[rightInd];
        rightInd--;

        maxSum = max(maxSum, leftSum + rightSum);
    }

    return maxSum;
}

int main() {
    return 0;
}