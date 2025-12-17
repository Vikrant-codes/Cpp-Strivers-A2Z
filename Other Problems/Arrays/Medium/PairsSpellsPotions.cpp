/*
Leetcode - 2300. Successful Pairs of Spells and Potions : Medium

You are given two positive integer arrays spells and potions, of length n and m respectively, 
where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.
You are also given an integer success. 
A spell and potion pair is considered successful if the product of their strengths is at least success.
Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair 
with the ith spell.

Examples :-

Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7 __ Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Input: spells = [3,1,2], potions = [8,5,8], success = 16 __ Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful. 
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful. 
 
Constraints :-
n == spells.length __ m == potions.length
1 <= n, m <= 10^5
1 <= spells[i], potions[i] <= 10^5
1 <= success <= 10^10
*/

#include <bits/stdc++.h>
using namespace std;

/*
There are 2 major optimal approaches to this problem :- 
1. Binary Search
2. Two Pointer Approach 

Binary Search is better in terms of overall complexity but Two Pointer is faster for large arrays
This is becuase after sorting the two arrays in two pointers searching takes only O(n + m) time 
rather than O(n log m ) of binary search.
*/

// Binary Search Approach : Time Complexity : O(m log m + n log m) __ Space Complexity : O(1)
/*
Intuition

For a spell x, whether a potion p is succesful if x * p >= success. So for that spell x all the potions with strength >= p 
will also be succesful. 
So if we sort potions, we can find the first potion that satisfies the inequality and then all potions after it are successful.
Instead of calculating product of potion & spell everytime during binary search, we can pre-compute need = success/spell_strength
and find the first potion whose strength is >= need. 

Algorithm / reasoning

1. Sort potions ascending. (Needed so binary search works.)
2. For each spell value x:
-- Compute need = (success + x - 1) / x as a long long (this is ceil(success/x) without floating point).
-- Binary-search potions for the first index pos where potions[pos] >= need.
-- The number of successful potions for this spell is m - pos (where m = potions.size()).
-- If pos == m (no such potion) → add 0.
3. Return the list of counts in the same order as spells.

Correctness

1. If we were using multiplication while binary search, then instead of checking x * potions[mid] >= success, 
we would have to use 1LL * x * potions[mid] >= success to handle integer overflow cases. 

2. While calculating need = ceil(success / x). 
If we used int need = ceil(success / x); — this line doesn’t work correctly for two reasons:
- Integer division truncates — since both success and x are integers, success / x will floor the result 
  before ceil() even applies.
- Also, ceil() works on floating-point values, so it’s better avoided when success can be large (long long).
So, instead of using this we used long long need = (success + x - 1) / x;   // equivalent to ceil(success / x)

Que > Why for integer maths :- (a + b - 1) / b is equivalent to ceil (a / b), like we used to calculate ceil (success/x) ?
and also why didn't we used ceil (1.0 * success / x) to prevent truncation of success/x value before ceil could apply?

Ans > Yes, int need = ceil(1.0 * success / x); will work correctly
(because 1.0 * success forces floating-point division before applying ceil()).
But in competitive programming, we usually avoid floating-point math when integer math can achieve the same — 
to prevent precision issues and improve speed.
🧩 Why (success + x - 1) / x ≡ ceil(success / x) (integer math)
⚙️ Normal integer division : If you do success / x (integer division), it always truncates (floors) toward zero.
ex - 10 / 3 = 3 (not 3.333 as decimal portion is trunacted in integer maths)
⚙️ Trick: Add (x - 1) before dividing : If you add (x - 1) before dividing, you ensure the remainder “rounds up” 
whenever there is any. Thus, ceil(a / b) = (a + b - 1) / b
Ex - ceil (10 / 3) = (10 + 3 - 1) / 3 = 12 / 3 = 4

🧠 Intuitive reasoning : Why adding x - 1 to success mimicks the ceil functioning. 
When success divides evenly by x, (success + x - 1) just adds less than x, so division result doesn’t increase.
But if there’s a remainder (meaning success isn’t a multiple of x), that extra (x - 1) “pushes” it into the next integer, 
mimicking a ceil.


Complexity :- 
Sorting potions: O(m log m).
For each of the n spells, one binary search on potions: O(n log m).
Total: O(m log m + n log m) time.
Extra space: O(1) (ignoring the output array).
*/
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
    sort(potions.begin(), potions.end());
    int m = potions.size();
    vector<int> pairs;
    for (int x : spells) {
        // apply binary search in potions array to find the min succesfull pair element

        int low = 0, high = m - 1;
        long long need = (success + x - 1) / x;   // same as ceil(success/x) .. eplained above 

        while (low <= high) {
            int mid = low + (high - low) / 2;
            // if (1LL * x * potions[mid] >= success) high = mid - 1;

            if (potions[mid] >= need) high = mid - 1;
            else low = mid + 1;
        }

        pairs.push_back(m - low);
    }
    return pairs;
}

// Two Pointer Approach : Time Complexity : O(m logm + n log m) + O(n + m) __ Space Complexity : O(n)
/*
🧠 Intuition
The key observation is:
For a given spell strength s, all potions p such that s * p >= success will also hold true for any potion stronger than p 
(since potions are sorted).
So, if potions are sorted in increasing order, once we find the first potion that makes the product ≥ success,
all potions to its right will also be successful pairs.
To use this efficiently for all spells, we sort spells as well.
Then we use two pointers:
One (i) moves from the largest spell (right end of spells).
The other (j) moves from the weakest potion (left end of potions).
We check for product of spells[i] and potions[j] and move the two pointers accordingly while keeping count of successful pairs.

⚠️ Problem faced while implementing :- 
If we sort the array spells then the order of the elements will get lost and then we wouldn't know where to place the 
count of pairs for corresponding spell_strengths as sorting will change their previous order.
To solve this problem we firstly use another array to store the spells elements in the original order before sorting spells.
Now while doing two pointer traversal we use a map to store the count of successful pairs for a particular spell x. 
Now we traverse the original order spell elements stored in a third array and add their corresponding successful pair count 
to the answer vector by checking mpp[element]. 
I had initially stored spells element to ans vector and then later on changed these elements to the corresponding pair count 
extracted from map.

⚙️ Algorithm
1. Sort both arrays (spells and potions) ascendingly.
2. Keep two pointers:
-- i = n-1 → largest spell
-- j = 0 → smallest potion
3. For each spell from largest to smallest:
-- While spell[i] * potions[j] < success, move j right (need stronger potion).
-- Once the condition holds, every potion from j to m-1 forms a valid pair. → So mpp[spell[i]] = m - j.
-- Decrement i to check the next smaller spell.
4. If j goes out of bounds (j == m), → remaining smaller spells can’t make any valid pair, so set their count to 0.
5. Finally, reconstruct results for the original spell order using the map.

⏱️ Time Complexity
- Sorting spells and potions: O(n log n + m log m)
- Two-pointer traversal: O(n + m)
- Map reconstruction: O(n)
✅ Total: O(n log n + m log m) + O(n + m)
(Same asymptotic complexity as binary search, but only one pass after sorting.)

🧩 Space Complexity
- unordered_map<int,int>: up to O(n) extra space.
- ans is a copy of spells: O(n)
✅ Total: O(n).

✅ Summary of reasoning
- Sorting ensures a monotonic relationship between spell strength and potion success.
- The two-pointer method exploits this monotonicity to efficiently count all valid potion pairs for each spell in one pass.
- The map restores original order since sorting spells changed the positions.
*/
vector<int> successfulPairs2Pointers(vector<int>& spells, vector<int>& potions, long long success) {
    vector<int> ans = spells;
    sort(spells.begin(), spells.end());
    sort(potions.begin(), potions.end());
    unordered_map<int, int> mpp; // stores pair count for element x

    int n = spells.size(), m = potions.size();
    int i = n - 1, j = 0;
    
    while (i >= 0 && j < m) {
        if (1LL * spells[i] * potions[j] >= success) {
            mpp[spells[i]] = m - j;
            i--;
        }
        else j++;
    }
    // if j went out of bound (j == m) but (i >= 0), remaining smaller spells can’t make any valid pair, so set their count to 0.
    while (i >= 0) {
        mpp[spells[i]] = 0;     
        i--;
    }
    // change ans vector elements to the corresponding successful pair count
    for (int &x : ans) {
        x = mpp[x];         // mpp[x] give the successful pair count for the element x
    }
    return ans;
}  

int main() {

}