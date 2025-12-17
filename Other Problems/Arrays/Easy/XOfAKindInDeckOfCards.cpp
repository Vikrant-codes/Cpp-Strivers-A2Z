/*
Leetcode - 914. X of a Kind in a Deck of Cards : Easy

You are given an integer array deck where deck[i] represents the number written on the ith card.
Partition the cards into one or more groups such that:
- Each group has exactly x cards where x > 1, and
- All the cards in one group have the same integer written on them.
Return true if such partition is possible, or false otherwise.

Examples :-

Input: deck = [1,2,3,4,4,3,2,1] __ Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].

Input: deck = [1,1,1,2,2,2,3,3] __ Output: false
Explanation: No possible partition.

Constraints :-
- 1 <= deck.length <= 10^4
- 0 <= deck[i] < 10^4
*/
#include <bits/stdc++.h>
using namespace std;

/*
Some EdgeCases / Cases to understand the problem better :-
Input : [1,1,2,2,2,2] __ Output : True __ Explanation : Grouping can be done as [1,1], [2,2], [2,2]
Input : [1,1,1,1,2,2,2,2,2,2] __ Output : True __ Explanation : Group can be done as [1,1], [1,1], [2,2], [2,2], [2,2]
Input : [1] __ Output : False __ Explanation : Only one group of size 1
*/

/*
🎯 Goal of the problem
You need to check if the deck can be partitioned into groups such that:
- All groups have equal size X
- X ≥ 2
- Each group contains cards with the same value
This translates to: If all card frequencies share a common divisor ≥ 2, grouping is possible.

So, we find the largest value 'x' of partition size such that equal elements can be partitioned into groups of size 'x'
If that x >= 2, we return true because partition is possible. 
*/
int getGCD(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;

    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}
bool hasGroupsSizeX(vector<int>& deck) {
    vector<int> freq(10000);
    for (int x : deck) freq[x]++;
    int gcd = 0;
    for (int f : freq) gcd = getGCD(gcd, f);
    return gcd != 1;        // or use :- return gcd > 1
}

int main() {
    vector<int> deck = {1,1,2,2,2,3,3,3,3,3,3};
    cout << hasGroupsSizeX(deck);

    return 0;
}