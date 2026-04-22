/*
Leetcode - 2078. Two Furthest Houses With Different Colors : Easy

There are n houses evenly lined up on the street, and each house is beautifully painted. 
You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.
Return the maximum distance between two houses with different colors.
The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.

Examples :-

Input: colors = [1,1,1,6,1,1,1] __ Output: 3
Explanation: In the above image, color 1 is blue, and color 6 is red.
The furthest two houses with different colors are house 0 and house 3.
House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
Note that houses 3 and 6 can also produce the optimal answer.

Input: colors = [1,8,3,8,3] __ Output: 4
Explanation: In the above image, color 1 is blue, color 8 is yellow, and color 3 is green.
The furthest two houses with different colors are house 0 and house 4.
House 0 has color 1, and house 4 has color 3. The distance between them is abs(0 - 4) = 4.

Input: colors = [0,1] __ Output: 1
Explanation: The furthest two houses with different colors are house 0 and house 1.
House 0 has color 0, and house 1 has color 1. The distance between them is abs(0 - 1) = 1.

Constraints :-
- n == colors.length
- 2 <= n <= 100
- 0 <= colors[i] <= 100
- Test data are generated such that at least two houses have different colors.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
Approach :-
We want the maximum distance between two houses with different colours.
The naive approach is to try out every pairs of houses,
if the houses are of different colours, find the distance between them.
Use a variable to keep track of this maximum distance.

Idea:
- Try every possible pair (i, j) where i < j.
- If colors are different → compute distance j - i.
- Keep track of the maximum distance.
*/
int maxDistanceNaive(vector<int>& colors) {
    int n = colors.size();
    int ans = -1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (colors[i] != colors[j]) 
                ans = max(ans, j - i);
        }
    }
    
    return ans;
}

// Optimal Approach (Greedy 2 pointers approach) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
We need to find the maximum difference between two different coloured houses.
For that we need two different coloured houses which are located at the farthest possible index positions.
For that we would prefer the two houses to be as far as possible from each other.
So, we would try to pick those different coloured house pairs which are present nearer to different ends
(one house near to right end and another near to left end).

The best case for us would be when the houses at the two array ends are different coloured, in this case, 
we can simply choose these two houses at positions 0 & n - 1 and the maximum difference would be (n - 1) - 0 = n - 1.

But, if these two houses are coloured the same, then we need to find a different house whose difference is maximum possible.

If array has only one such different coloured house like ex- arr = [1, 1, 2, 1, 1] or [1, 2, 1, 1, 1]
then, this house coloured '2' is definitely one of the pair houses but we have multiple house positions we can pair it with.
We want the other house to be as far as possible, so it would be natural to pick the extreme end houses.. 
for array -> [1, 1, 2, 1, 1] both the left & right houses are equally distant, 
so we can choose any of the index positions '0' or '4' to pair up with 2 (index = 2), and max_diff = |2 -0| = |2-4| = 2

But, for array -> [1, 2, 1, 1, 1], this time the right end is farther to this '2' coloured house.
So, to get the maximum difference, we must choose the right end (n-1 = 4) house, max_diff = |1-4| = 3

If array had multiple coloured houses (in the above cases, there were only two distinct colours {1 & 2})
then also, the best choice would be to find find the different coloured house pair such that both the houses are 
present nearer to opposite ends (one near left end & other near right end).
Since, we need the house which is nearer to the end, 
we can traverse from end to middle in search of the different coloured house.
The answer pair would always have either the left end house or right end house.
For array = [1, 2, 1, 1, 1], we choose the right end house to form a pair and get the max difference = 3
In this case, '2' which is the different coloured house is nearer to the left end, so we chose the right end house to form a 
pair with it and thus maximize the position difference

For array = [1, 1, 1, 2, 1], we must choose the left end house to form a pair and get the max difference = 3.
In this case, '2' is near to right end and hence we choose left end house to form a pair with it.

If array was something like [1, 1, 3, 1, 1, 2, 1], now if we cosndier the first different coloured house from left end
it is 3 (at index 2), this 3 can form pair with right end, giving us the position difference of 4 units.
From right end, the first different coloured house is 2 (at index 5), this 2 forms pair with left house giving us the 
position difference of 5 units.
We see that we get the maximum possible difference when we choose 2 which is comparatively more nearer to the right end 
than 3 being nearer to left end.
So, we need to find the first different coloured house from both ends, considering both ends simultaneously. 
In this way, we can actually find the house which is nearest to either left end or right end and 
pair it up with the farther end and maximize the difference.

To do so, we use two pointers i & j which starts from indices 1 & 'n-1' and move inwards and the moment any of the two 
pointers reach a different coloured house, this is the house which gives us the best pair, we return the position 
difference of this house along with the pairing array end house (right house or left house).

Suppose arr = [a, b, c, d, e, f, g, h], where a,b,c... are some integer values and may be eqaul
then, we first check if a != i, if yes, we immediately get the max. difference houses and return n-1.
Else, we place two pointers i & j at positions 0 & n - 2.. (i points to b and j points to h)
We check both houses at i & j and chek if it is different coloured, if yes, we consider that house for pair 
and return its position differnece from the farther end house.
If both i & j houses are same coloured, then we move ahead, both i & j moves towards center 
i -> .... <- j
The next time, i moves to 'c' house and j to 'f' house
if both c & f are same coloured as a, then again i & j moves ahead
if c is different coloured than a, we get our first nearest to the end different coloured house, 
    we pair it up with the right end and the diff = right house - i = n - 1 - i
if f is different coloured than a, then, f is the first nearest to the end different coloured house,
    we pair it up with the left end, diff = j - left house = j - 0 = j
Loop stops when i and j crosses, i.e. when i becomes > j

Key Idea --
- The greedy approach suggests the either of the left house or right house always forms the optimal maximum distance pair.
- The second pair house of the optimal pair is the one which is nearer to the end.
- We need to consider both left end and right end while finding the nearest to the end house.
- We can use two pointers to find this nearest to the end house from both ends.
- When we find the nearest to the end house, we can pair it up with the farther end and return the position diff of the pair.
*/

int maxDistance(vector<int>& colors) {
    int n = colors.size();
    if (colors[0] != colors[n-1]) return n-1;

    int i = 1, j = n-2;
    while (i <= j) {
        if (colors[i] != colors[0]) return (n-1-i);
        if (colors[j] != colors[0]) return (j);
        i++;
        j--;
    }
    return -1;         
     // this will never run as the constraints provides that there is always at least two different colours are present
}

int main() {
    return 0;
}