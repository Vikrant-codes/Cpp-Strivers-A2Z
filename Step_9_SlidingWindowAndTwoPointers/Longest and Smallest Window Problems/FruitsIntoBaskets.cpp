/*
Leetcode - 904. Fruit Into Baskets : Medium

You are visiting a farm that has a single row of fruit trees arranged from left to right. 
The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

• You only have two baskets, and each basket can only hold a single type of fruit. 
  There is no limit on the amount of fruit each basket can hold.
• Starting from any tree of your choice, you must pick exactly one fruit from every tree 
  (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
• Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array fruits, return the maximum number of fruits you can pick.

Examples :-

Input: fruits = [1,2,1] __ Output: 3
Explanation: We can pick from all 3 trees.

Input: fruits = [0,1,2,2] __ Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Input: fruits = [1,2,3,2,2] __ Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].

Constraints :-
• 1 <= fruits.length <= 10^5
• 0 <= fruits[i] < fruits.length
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Simplified problem statement

We are given an array where each element represents a type of fruit.
We have two baskets, and each basket can hold only one type of fruit. 
We can collect as many fruits as we want, but we can have at most two distinct types of fruit.
We need to find the maximum number of fruits we can collect from a contiguous range of trees.
Essentially, the problem is asking:
Find the length of the longest subarray containing at most two distinct elements.
*/

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Brute Force — Generate all subarrays

- Consider every possible starting index i.
- Extend the subarray by moving j towards the right.
- Maintain a set to keep track of the distinct fruit types.
- If the number of distinct types is at most 2, update maxLen.
- If the number of distinct types exceeds 2, break immediately.

Why break?
Once a subarray contains more than two distinct types, 
extending it further cannot reduce the number of distinct types. 
So no longer subarray starting at the same i can be valid.

>> Complexity
- Time: O(n²) average
- Auxiliary Space: O(1), since the set can contain at most 3 distinct elements before we break.
*/
int totalFruitBrute(vector<int>& fruits) {
    int n = fruits.size();
    int maxLen = 0;
    
    for (int i = 0; i < n; i++) {
        unordered_set<int> st;

        for (int j = i; j < n; j++) {
            st.insert(fruits[j]);

            if (st.size() > 2)
                break;
            
            maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// Sliding Window: Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Intuition

Instead of generating every subarray independently, we maintain a sliding window [l, r].
1. Expand the window by moving r to the right.
2. Add fruits[r] to the frequency map.
3. If the map contains more than 2 distinct fruit types, the window becomes invalid.
4. Shrink the window from the left until the map contains at most 2 distinct types.
5. Update maxLen using the current valid window length.

One important detail: when shrinking, if the frequency of fruits[l] becomes zero, remove it from the map. 
Otherwise, mp.size() won't correctly represent the number of distinct fruit types.

>> Complexity
- Time: O(2n) average. Both pointers traverse the array at most once.
- Auxiliary Space: O(1), since the map holds at most 3 distinct elements.
*/
int totalFruit(vector<int>& fruits) {
    int n = fruits.size();

    int l = 0, r = 0;
    int maxLen = 0;

    unordered_map<int, int> mp;

    while(r < n) {
        mp[fruits[r]]++;

        while(mp.size() > 2) {
            mp[fruits[l]]--;

            if(mp[fruits[l]] == 0)
                mp.erase(fruits[l]);

            l++;
        }

        maxLen = max(maxLen, r-l+1);
        r++;
    }

    return maxLen;
}

// Optimized Sliding Window: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

This is the same optimization we used in `Leetcode - 1004. Max Consecutive Ones III`

In the naive approach, whenever the window becomes invalid, we shrink it until it becomes valid again.
But do we really need to do that?
We are only interested in finding the longest valid subarray.
Suppose we have already found a valid subarray of length maxLen.

Now, when we expand the window by moving r:
- If the window contains at most 2 distinct elements, it is valid. Update maxLen.
- If it contains more than 2 distinct elements, it becomes invalid.
- Instead of shrinking it completely, just move l one position forward.

Why is moving l once sufficient?
When the window becomes invalid, its length is maxLen + 1. Moving l once brings its length back to maxLen.
We don't need to find a valid window of a smaller length because we have already found a valid subarray of length maxLen.
If the window becomes valid again as we continue expanding, we can potentially find a longer valid subarray.

>> Complexity
- Time: O(n) average.
- Auxiliary Space: O(1), since the map stores at most 3 distinct elements.
*/
int totalFruit(vector<int>& fruits) {
    int n = fruits.size();
    
    int l = 0, r = 0;
    int maxLen = 0;

    unordered_map<int, int> mp;

    while(r < n) {
        mp[fruits[r]]++;

        if(mp.size() > 2) {
            mp[fruits[l]]--;

            if(mp[fruits[l]] == 0)
                mp.erase(fruits[l]);

            l++;
        }

        if(mp.size() <= 2) {
            maxLen = max(maxLen, r-l+1);
        }

        r++;
    }

    return maxLen;
}

int main() {
    return 0;
}