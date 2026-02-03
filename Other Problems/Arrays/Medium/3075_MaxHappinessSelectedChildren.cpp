/*
Leetcode - 3075. Maximize Happiness of Selected Children : Medium

You are given an array happiness of length n, and a positive integer k.

There are n children standing in a queue, where the ith child has happiness value happiness[i]. 
You want to select k children from these n children in k turns.

In each turn, when you select a child, 
the happiness value of all the children that have not been selected till now decreases by 1. 
Note that the happiness value cannot become negative and gets decremented only if it is positive.

Return the maximum sum of the happiness values of the selected children you can achieve by selecting k children.

Examples :-

Input: happiness = [1,2,3], k = 2 __ Output: 4
Explanation: We can pick 2 children in the following way:
- Pick the child with the happiness value == 3. The happiness value of the remaining children becomes [0,1].
- Pick the child with the happiness value == 1. The happiness value of the remaining child becomes [0]. Note that the happiness value cannot become less than 0.
The sum of the happiness values of the selected children is 3 + 1 = 4.

Input: happiness = [1,1,1,1], k = 2 __ Output: 1
Explanation: We can pick 2 children in the following way:
- Pick any child with the happiness value == 1. The happiness value of the remaining children becomes [0,0,0].
- Pick the child with the happiness value == 0. The happiness value of the remaining child becomes [0,0].
The sum of the happiness values of the selected children is 1 + 0 = 1.

Input: happiness = [2,3,4,5], k = 1 __ Output: 5
Explanation: We can pick 1 child in the following way:
- Pick the child with the happiness value == 5. The happiness value of the remaining children becomes [1,2,3].
The sum of the happiness values of the selected children is 5.

Constraints :-
- 1 <= n == happiness.length <= 2 * 10^5
- 1 <= happiness[i] <= 10^8
- 1 <= k <= n
*/

#include <bits/stdc++.h>
using namespace std;

// Sorting + Greedy Approach : Time Complexity : O(n * log n) __ Space Complexity : O(1)
/*
"
| Since all the unselected numbers are decreasing at the same rate, we should greedily select k largest values.
| The ith largest number (i = 1, 2, 3,…k) should decrease by (i - 1) when it is picked.
| Add 0 if the decreased value is negative.
"

We need to select k children in such a way the the total sum of selected children's happiness is the maximum possible.
Also, when we select a child the happiness of the remaining unselected children decrements by 1 ('not becomes negative').

To maximize the total happiness the best approach will be to select the most happy children first. 
While selecting children we also need to consider the decremented value till now.

Since, the array is not sorted thus finding the maximum each time would be tiresome. 
Thus, we firstly sort the array, so that we can select the most happy children by traversing the array from end after sorting.

We need to select total 'k' children, so we select the last 'k' children from the sorted array.
Also, the value of the ith child from end i.e. the ith maximum child will be decremented by i-1 times when it gets selected.
Ex- [1,2,3,4,5], k = 3.. Initialize sum = 0
Child 1 :- Most happy = 5, sum = 5, array becomes = [0,1,2,3,|5|]  since the unselected kids happiness gets decremented
Child 2 :- Now, when we select the 2nd most happy child i.e. 2nd last array value, its value would be decremented by 1. 
Child 3 :- Select the 3rd most happy child i.e. 3rd last array value and its value would have been decremented by 2.
Thus, the ith maximum child value is decremented by (i-1) times by the time it is selected.

If the decremented value becomes negative, we will consider it as 0.
*/
long long maximumHappinessSum(vector<int>& happiness, int k) {
    sort(happiness.begin(), happiness.end());
    int n = happiness.size();
    long long sum = 0;
    for (int i = n-1; i >= n - k; i--) {
        int decVal = happiness[i] - (n - 1 - i);
        if (decVal < 0) decVal = 0;
        sum += decVal;
    }
    return sum;
}

/*
If while selecting the kids, assume the ith selected child happiness gets decremented to negative (becomes 0), 
and assume that k-i kids still remain to be selected,
We know for sure that the ith child original happiness value is more than the unselected kids and also since 
its value has been decremented to become negative then all the other kids value would also become negative.
So, instead of selecting those children, we simply break out of the loop because 
their selection will no longer increase the maximum happiness sum. 

This is small optimization step due to early break condition.
*/
long long maximumHappinessSum(vector<int>& happiness, int k) {
    sort(happiness.begin(), happiness.end());
    int n = happiness.size();
    long long sum = 0;
    for (int i = n-1; i >= n - k; i--) {
        int decVal = happiness[i] - (n - 1 - i);
        if (decVal < 0) break;
        sum += decVal;
    }
    return sum;
}

int main() {
    return 0;
}