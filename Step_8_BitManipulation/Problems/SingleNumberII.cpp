/*
Leetcode - 137. Single Number II : Medium

Given an integer array nums where every element appears three times except for one, 
which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples :-

Input: nums = [2,2,3,2] __ Output: 3
Input: nums = [0,1,0,1,0,1,99] __ Output: 99

Constraints :-
• 1 <= nums.length <= 3 * 10^4
• -2^31 <= nums[i] <= 2^31 - 1
• Each element in nums appears exactly three times except for one element which appears once.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n) __ Space Complexity : O( (n-1)/3 + 1 )
/*
We can use a hash map to store each element and its frequency. 
First, traverse the array and increment the frequency of each element. 
Then, traverse the map and return the element whose frequency is 1, 
since every other element appears exactly three times.

This approach is straightforward, but it doesn't satisfy the problem's constant extra space requirement, 
because the hash map takes extra space to store the distinct elements.
Since nums has all elements appearing thrice except for one element, total no. of distinct elements are (n - 1) / 3 + 1.

>> Complexity Analysis:
- Time: O(n) average — One traversal to count frequencies and another to find the single element.
- Space: O( (n-1)/3 + 1 ) — The hash map stores the elements and their frequencies.
*/
int singleNumberHashMap(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int& x: nums)
        freq[x]++;
    
    for (auto& it : freq) 
        if (it.second == 1)
            return it.first;

    return -1;
}

// Better Approach (Sorting + Optimized Lookup): Time Complexity : O(n log n) + O(n / 3) __ Space Complexity : O(1)
/*
>> Intuition

We can first sort the array so that equal elements appear next to each other. 
Since every element appears exactly three times except for one, 
the repeated elements will form groups of three consecutive equal values, 
while the single element will appear alone.

After sorting, we could use a simple O(n) loop to manually find the single element by checking its neighbors. 
For example, we can check whether nums[i] differs from both nums[i - 1] and nums[i + 1] 
(taking care of the array boundaries). If it does, that element occurs only once.

However, we can make this lookup simpler by taking advantage of the groups of three.

How the lookup in this code works:

|    for (int i = 1; i < n; i += 3) {
|        if (nums[i] != nums[i - 1]) {
|            return nums[i - 1];
|        }
|    }
|    return nums[n - 1];

After sorting, every group of three equal elements occupies three consecutive positions. 

If the single element is not disrupting the pattern, the array looks like this:
Index:    0  1  2   3  4  5   6  7  8
Array:   [2, 2, 2,  5, 5, 5,  9, 9, 9]

So, we can check the elements at indices 1, 4, 7, ... against the elements immediately before them (0, 3, 6, ...). 
These are the second elements of each group of three.

- If nums[i] == nums[i - 1]: The current group is following the expected pattern, 
    so we move to the next group by increasing i by 3.
- If nums[i] != nums[i - 1]: The pattern has been disrupted by the single element. 
    The element at i - 1 is the single number, so we return it.

For example:
Index:    0  1  2   3  4  5   6
Array:   [2, 2, 2,  5, 7, 7,  7]

At i = 1, nums[1] == nums[0], so we continue.
At i = 4, nums[4] != nums[3] because 7 != 5. This means the group of 5s was interrupted, so we return nums[3], which is 5.

Why do we return nums[n - 1] at the end?
If the loop finishes without finding a mismatch, 
all the groups of three before the final element follow the expected pattern. 
Therefore, the single element must be at the end of the sorted array.

For example:
Index:    0  1  2   3  4  5   6
Array:   [2, 2, 2,  5, 5, 5,  9]
The loop checks i = 1 and i = 4, finding no mismatch. The remaining element 9 is the single number, so we return nums[n - 1].

>> Complexity Analysis:
- Time: O(n log n) + O(n / 3) — Sorting takes O(n log n), and the lookup takes O(n / 3) in the worst case.
- Space: O(1) auxiliary space if the sorting implementation uses in-place sorting, 
  though the sort may use O(log n) stack space.
*/
int singleNumberSorting(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());
    
    for (int i = 1; i < n; i += 3) {
        if (nums[i] != nums[i - 1]) {
            return nums[i - 1];
        }
    }
    
    return nums[n - 1];
}

// Approach-3 (Bit Manipulation): Time Complexity : O(32 x n) __ Space Complexity : O(1)
/*
>> Intuition

Every number except one appears exactly three times. 
If we count how many numbers have a particular bit set, 
the contribution from numbers appearing three times will be a multiple of 3.

The unique number appears only once, so its set bits will leave a remainder of 1 when the count is divided by 3. 
We can use this to reconstruct the unique number, one bit at a time.

>> How the code works:

1. Iterate through all 32 bit positions. Since an int is typically 32 bits in C++, bitIndex goes from 0 to 31.

2. Count the set bits at the current position.
|   if (x & (1 << bitIndex))
|       cnt++;
1 << bitIndex creates a number with only the current bit set. The bitwise AND checks whether x also has that bit set. 
If it does, increment cnt.

3. Check the count modulo 3.
|   if (cnt % 3 != 0)
|       ans = ans | (1 << bitIndex);

All numbers that appear three times contribute a multiple of 3 to the count. Therefore:
- If cnt % 3 == 0, the unique number has a 0 at this position.
- If cnt % 3 != 0, the unique number has a 1 at this position.

We set that bit in ans using bitwise OR.

4. After processing all 32 positions, ans contains the unique number.

Example: nums = [2, 2, 6, 2]

-----------------------------------------------
|Num             |     Binary Representation  |
|  2             |         0   1   0          |
|  2             |         0   1   0          |
|  6             |         1   1   0          | 
|  2             |         0   1   0          |
|---------------------------------------------|
|Count of bits   |         1   4   0          |
|---------------------------------------------|
|Count % 3       |         1   1   0          |
|---------------------------------------------|
|Single No. bits |         1   1   0          |
-----------------------------------------------
The reconstructed result is 110, which is 6.

>> Complexity analysis:
- Time: O(32 x n) = O(n), because we examine all 32 bits for every element.
- Space: O(1), because we use only a few integer variables.

-> Is this actually faster than sorting?
The sorting approach has time complexity O(n log n), 
while this bit-counting approach has time complexity O(32 x n), which simplifies to O(n) because 32 is a constant.

However, for this problem, the sorting approach can be faster in practice.
The maximum array length is 3 x 10^4 = 30,000. 
For sorting, the logarithmic factor is approximately: log (30,000) = 14.87

Compare the rough operation counts:
- Sorting: n log n = 14.87 x n
- Bit manipulation: 32 x n

Since 14.87 n < 32 n, sorting may perform fewer operations in this simplified comparison.
*/
int singleNumberBitMan(vector<int>& nums) {
    int ans = 0, cnt, mask;

    // Iterate through every bit (from 0 to 31)
    for (int bitIndex = 0; bitIndex < 32; bitIndex++) {
        cnt = 0;
        mask = (1 << bitIndex);     // Get the mask for the bitIndex-th bit position

        // Iterate over the array and count the number of set bits at position bitIndex
        for (int x : nums) {
            // Increment the cnt if bitIndex-th bit is set in current element
            if (x & mask) {
                cnt++;              
            }
        }
    
        // If sum is not a multiple of 3, it's part of the unique element
        if (cnt % 3 != 0) 
            ans = ans | mask;
    }

    return ans;
}

// Optimal Approach - 1 (Bit Manipulation + FSM): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal Approach - 1: Bit Manipulation + Finite State Machine

The problem says every number appears three times except one number, which appears once. 
We want to find that unique number in O(n) time and O(1) extra space.
Instead of processing each of the 32 bit positions separately, 
we track the remainder modulo 3 for every bit position simultaneously. 
The key idea is to use two bitmasks, one and two, to represent the states of a Finite State Machine (FSM).

1. Understand the three states
For any bit position, consider how many times that bit has appeared as 1. We only care about the count modulo 3.

-----------------------------------------------
| State	    | Remainder	 | one bit	| two bit |
-----------------------------------------------
| State 0	| 0	         | 0	    | 0       |
| State 1	| 1	         | 0	    | 1       |
| State 2	| 2	         | 1	    | 0       |
-----------------------------------------------
When the incoming bit is 1, the state moves through the cycle: 0 → 1 → 2 → 0
When the incoming bit is 0, the state stays unchanged.

Notice that in this implementation, two represents state 1, while one represents state 2. 
These names are just labels for the bitmasks.

2. Build the truth table
Let x represent the incoming bit from nums[i]. 
Since x can be either 0 or 1, each of our three states has two possible inputs, giving six cases.

-------------------------------------------------------------------
| Current state	| one  | two | x | Next state | New one | New two |
-------------------------------------------------------------------
| 0	            | 0	   | 0   | 0 | 0	      | 0       | 0       |
| 1	            | 0	   | 1   | 0 | 1	      | 0       | 1       |
| 2	            | 1	   | 0   | 0 | 2	      | 1	    | 0       |
| 0	            | 0	   | 0   | 1 | 1	      | 0	    | 1       |
| 1	            | 0	   | 1   | 1 | 2	      | 1	    | 0       |
| 2	            | 1	   | 0   | 1 | 0          | 0	    | 0       |
-------------------------------------------------------------------

3. How do we convert the truth table into a bitwise expression?
Before deriving the formulas, let's understand the operators involved.
- & (AND): returns 1 only when both input bits are 1.
- | (OR): returns 1 when at least one input bit is 1.
- ~ (NOT): flips every bit, changing 0 to 1 and 1 to 0.
The key rule for deriving a formula is:
| To represent a particular truth-table row, use AND (&) between all its input conditions. 
| Then use OR (|) to combine all rows that produce an output of 1.

For example, suppose a row has:
one	| two	| x	| Desired output
0	| 1	    | 1	| 1

We want an expression that becomes 1 for exactly these input values.
- one must be 0, so we use ~one.
- two must be 1, so we use two directly.
- x must be 1, so we use x directly.
Therefore, the expression for this row is: ~one & two & x

Why do we use ~one when one = 0? Because NOT flips the bit: if one = 0, then ~one has a 1 at that bit position. 
That allows the AND expression to evaluate to 1 when all the row's conditions are satisfied.

4. Derive the formula for new one
Look at the New one column in the truth table. It contains 1 in only two rows:
-------------------------------------------------------------------
| Current state	| one  | two | x | Next state | New one | New two |
-------------------------------------------------------------------
| 2	            | 1	   | 0   | 0 | 2	      | 1	    | 0       |
| 1	            | 0	   | 1   | 1 | 2	      | 1	    | 0       |
-------------------------------------------------------------------

First row: 0, 1, 1
- one = 0 → ~one
- two = 1 → two
- x = 1 → x
Expression: ~one & two & x

Second row: 1, 0, 0
- one = 1 → one
- two = 0 → ~two
- x = 0 → ~x
Expression: one & ~two & ~x

Either row should make new one equal to 1, so we combine the expressions with OR: 
> newOne = (one & ~two & ~x) | (~one & two & x)

5. Derive the formula for new two
Now look at the New two column. It also contains 1 in only two rows:
-------------------------------------------------------------------
| Current state	| one  | two | x | Next state | New one | New two |
-------------------------------------------------------------------
| 1	            | 0	   | 1   | 0 | 1	      | 0       | 1       |
| 0	            | 0	   | 0   | 1 | 1	      | 0	    | 1       |
-------------------------------------------------------------------

First row: 0, 0, 1
- one = 0 → ~one
- two = 0 → ~two
- x = 1 → x
Expression: ~one & ~two & x

Second row: 0, 1, 0
- one = 0 → ~one
- two = 1 → two
- x = 0 → ~x
Expression: ~one & two & ~x

Combining both cases with OR:
> newTwo = (~one & ~two & x) | (~one & two & ~x)

>> Why do we need cpy?
There is a subtle but important issue: the first assignment has already modified one. 
But the formula for new two requires the old value of one, as shown in the truth table.
So we save the old value first: int cpy = one;

Then use cpy instead of one in the second formula: two = (~cpy & two & ~nums[i]) | (~cpy & ~two & nums[i]);

6. Returning
We return two because the unique number appears once, so each of its set bits finishes in state 1. 
In this encoding, state 1 is represented by one = 0 and two = 1.

>> Complexity analysis
- Time: O(n) — We traverse the array once, performing a constant number of bitwise operations per element.
- Space: O(1) — We use only a few integer variables.
*/
int singleNumber1(vector<int>& nums) {
    int n = nums.size();
    int one = 0, two = 0;

    for (int i = 0; i < n; i++) {
        int cpy = one;
    
        one = (one & ~two & ~nums[i]) | (~one & two & nums[i]);
        two = (~cpy & two & ~nums[i]) | (~cpy & ~two & nums[i]);
    }

    return two;
}

// Optimal Approach - 2 (Optimized FSM Using XOR): Time Complexity : O(n) __ Space Complexity : O(1)
/*
This is another way to implement the same three-state machine. 
Instead of deriving long Boolean expressions from the truth table, 
this version uses XOR to toggle bits and AND with NOT to enforce valid states.

The goal remains the same: bits belonging to numbers that appear three times should return to state 0, 
while the bits belonging to the unique number should remain set in ones.

1. Understand the two bitmasks
This version uses a slightly different state encoding from the previous implementation.
--------------------------------------------------------
| State	| Meaning	            | ones bit	| twos bit |
--------------------------------------------------------
| 0	    | Count divisible by 3	| 0	        | 0        |
| 1	    | Remainder is 1	    | 1	        | 0        |
| 2	    | Remainder is 2	    | 0	        | 1        |
--------------------------------------------------------
When an incoming bit is 1, the state transitions are: 0 → 1 → 2 → 0
When the incoming bit is 0, the state remains unchanged.

Notice the difference from the previous version: here, ones represents state 1, and twos represents state 2. 

2. Understand the first formula: ones = (ones ^ nums[i]) & ~twos;

This has two operations.
- ones ^ nums[i]: XOR toggles a bit when the incoming bit is 1. 
                  If the incoming bit is 0, the bit remains unchanged.

- & ~twos: clears any bit that is already set in twos, 
           ensuring that a bit cannot simultaneously belong to state 1 and state 2.

--------------------------------------------------------------
| Old ones | Incoming bit x	| ones ^ x | Old twos | New ones |
--------------------------------------------------------------
| 0	       | 0	            | 0	       | 0	      | 0        |
| 0	       | 1	            | 1	       | 0	      | 1        |
| 1	       | 0	            | 1	       | 0	      | 1        |
| 1	       | 1	            | 0	       | 0	      | 0        |
| 0	       | 1	            | 1	       | 1	      | 0        |
--------------------------------------------------------------
The last row is particularly important: if twos is already 1, the bit must not remain set in ones. 
The & ~twos operation clears it.

3. Understand the second formula: twos = (twos ^ nums[i]) & ~ones;

The same principle applies:
- twos ^ nums[i] toggles bits in twos whenever the incoming bit is 1.
- & ~ones clears bits that are already set in ones, keeping the two states mutually exclusive.

For example, suppose a bit is currently in state 1:
- ones = 1
- twos = 0
When another 1 arrives, the state must move to state 2.

The first statement calculates: ones = (1 ^ 1) & ~0 = 0
Then the second statement calculates: twos = (0 ^ 1) & ~0 = 1
So the state changes from (ones, twos) = (1, 0) to (0, 1), exactly as required.

4. Trace the state transitions

For a single bit position, the behavior is:
--------------------------------------------
| Current state	| Incoming bit | New state |
--------------------------------------------
| 0 (0,0)	    | 0	           | 0 (0,0)   |
| 0 (0,0)	    | 1	           | 1 (1,0)   |
| 1 (1,0)	    | 0	           | 1 (1,0)   |
| 1 (1,0)	    | 1	           | 2 (0,1)   |
| 2 (0,1)	    | 0	           | 2 (0,1)   |
| 2 (0,1)	    | 1	           | 0 (0,0)   |
--------------------------------------------
This is the same modulo-3 FSM, just expressed using XOR and AND operations.
The key difference from the previous solution is that 
we don't manually write an AND expression for each truth-table row. 
Instead, XOR handles the toggling, and the masks ~twos and ~ones prevent invalid states.

Notice that the second statement uses the updated ones. 
That is intentional for this particular pair of formulas; unlike the previous implementation, 
it does not need a copy of the old ones.

>> Complexity analysis
- Time: O(n) — one traversal, with a constant number of bitwise operations per element.
- Space: O(1) — only two bitmasks are maintained.

| >> Core intuition 
| ones tracks bits seen once modulo 3, and twos tracks bits seen twice modulo 3. 
| XOR updates the bit states, while the NOT masks prevent a bit from being represented in both states at once. 
| After all numbers are processed, the bits of the unique number remain in ones.
*/
int singleNumber2(vector<int>& nums) {
    int n = nums.size();
    int ones = 0, twos = 0;

    for (int i = 0; i < n; i++) {
        ones = (ones ^ nums[i]) & ~twos;
        twos = (twos ^ nums[i]) & ~ones;
    }

    return ones;
}

// Optimal Approach - 3: Time Complexity : O(n) __ Space Complexity : O(1)
/*
1. Initialize two integers ones and twos to track bits seen once and twice.
2. Iterate over each number in the array.
3. Update twos with bits that are set in both ones and the current number (twos |= ones & num).
4. Update ones using XOR with the current number (ones ^= num) to toggle bits based on odd occurrences.
5. Compute a mask by negating the common bits in ones and twos (mask = ~(ones & twos)).
6. Apply the mask to both ones and twos to remove bits that have appeared three times.
7. After the loop, ones holds the bits of the number that appeared exactly once.
*/
int singleNumber3(vector<int>& arr) {
    int ones = 0, twos = 0, mask;

    for (int num : arr) {
        
        // Update 'twos' with bits that are set in both 'ones' and 
        // current number. These are bits that have appeared twice so far.
        twos |= ones & num;
        
        // XOR current number with 'ones' to add bits appearing
        // odd number of times.If a bit has appeared once, it is set
        // if it's the second time, it gets unset.
        ones ^= num;

        // (ones & twos) gives bits that are set in both, meaning they 
        // have now appeared 3 times. ~(ones & twos) inverts it to create 
        // a mask where those bits are 0 (to be cleared), and others are 1.
        // Applying this mask on 'ones' and 'twos' removes the 
        // bits that have appeared three times.
        mask = ~(ones & twos);

        // Apply mask to keep only valid bits that haven't appeared 3 times.
        ones &= mask;
        twos &= mask;
    }

    return ones;  
}

int main() {
    return 0;
}