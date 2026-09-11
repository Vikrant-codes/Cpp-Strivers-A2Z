/*
Leetcode - 292. Nim Game : Easy

You are playing the following Nim Game with your friend:
- Initially, there is a heap of stones on the table.
- You and your friend will alternate taking turns, and you go first.
- On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
- The one who removes the last stone is the winner.

Given n, the number of stones in the heap, 
return true if you can win the game assuming both you and your friend play optimally, otherwise return false.

Examples :-

Input: n = 4 __ Output: false
Explanation: These are the possible outcomes:
1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
In all outcomes, your friend wins.

Input: n = 1 __ Output: true

Input: n = 2  __ Output: true

Constraints :- 
1 <= n <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(1) __ Space Complexity : O(1)
/*
Key Idea (Intuition)
In this game:
- Each player can remove 1, 2, or 3 stones
- We start first
- Whoever removes the last stone wins
- Both players play optimally
Instead of trying all possibilities, look for a pattern in small values of n.

Try Small Cases
| n (stones) | What happens                                       | Can we win?    |
| ---------- | -------------------------------------------------- | -------------- |
| 1          | Take 1 → win                                       | ✅ True       |
| 2          | Take 2 → win                                       | ✅ True       |
| 3          | Take 3 → win                                       | ✅ True       |
| 4          | Any move leaves 1,2,3 for opponent → opponent wins | ❌ False      |
| 5          | Take 1 → leave 4 (losing state for opponent)       | ✅ True       |
| 6          | Take 2 → leave 4                                   | ✅ True       |
| 7          | Take 3 → leave 4                                   | ✅ True       |
| 8          | Any move leaves 5,6,7 (all winning for opponent)   | ❌ False      |

Pattern appears:
1 → W
2 → W
3 → W
4 → L
5 → W
6 → W
7 → W
8 → L
Every multiple of 4 is a losing position.

>> Why multiples of 4 are losing
If n = 4: No matter what starting move we make, opponent wins, example cases-
- Take 1 → opponent sees 3 → opponent wins
- Take 2 → opponent sees 2 → opponent wins
- Take 3 → opponent sees 1 → opponent wins
So we cannot force a win.

>> Winning Strategy
If n is not a multiple of 4, remove stones so that the opponent always sees a multiple of 4.
i.e. if (n % 4 != 0) only then we can win, 
and our move must be removing (n % 4) so that the count of stones becomes multiple of 4 for the opponent and he loses.
Example (n = 6): 6 → take 2 (6 % 4 == 2) → leave 4.
Now, no matter what move opponent makes, he will lose.

Thus, if n % 4 == 0 → we lose
Otherwise → we win
*/
bool canWinNim(int n) {
    return n % 4 != 0;
}

int main() {
    return 0;
}