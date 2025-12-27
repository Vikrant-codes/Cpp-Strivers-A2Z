/*
Leetcode - 3668. Restore Finishing Order : Easy

You are given an integer array order of length n and an integer array friends.
order contains every int from 1 to n exactly once, representing the IDs of the participants of a race in their finishing order.
friends contains the IDs of your friends in the race sorted in strictly increasing order. 
Each ID in friends is guaranteed to appear in the order array.

Return an array containing your friends' IDs in their finishing order.

Examples :-

Input: order = [3,1,2,5,4], friends = [1,3,4] __ Output: [3,1,4]
Explanation:
The finishing order is [3, 1, 2, 5, 4]. Therefore, the finishing order of your friends is [3, 1, 4].

Input: order = [1,4,5,3,2], friends = [2,5] __ Output: [5,2]
Explanation:
The finishing order is [1, 4, 5, 3, 2]. Therefore, the finishing order of your friends is [5, 2].

Constraints :-
- 1 <= n == order.length <= 100
- order contains every integer from 1 to n exactly once
- 1 <= friends.length <= min(8, n)
- 1 <= friends[i] <= n
- friends is strictly increasing
*/

#include <bits/stdc++.h>
using namespace std;

// HashMap Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🧠 Intuition
We are given:
- order: the finishing order of all participants.
- friends: a subset representing your friends.
We need to restore the finishing order only of your friends, preserving the relative order they appeared in the main order list.

So, the task is essentially : Filter out elements from order that are present in friends, keeping their original sequence.

⚙️ Algorithm :-
1. Store friends for quick lookup
2. Iterate through order:
    - For every participant, check if they’re your friend.
    - If yes → push them into the result vector ans.
    - This naturally preserves their order of appearance.
3. Return the result.

⏱️ Complexity Analysis
| Step      | Operation               | Time         | Space                        |
| --------- | ----------------------- | ------------ | ---------------------------- |
| Build map | Store all friends       | O(m)         |   O(m)                       |
| Filter    | Iterate through `order` | O(n)         |   O(m)                       |
| **Total** |                         | O(n + m)     |   O(m)                       |
where, n = size of order, m = size of friends, k = 
*/
vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
    unordered_map<int, bool> isFriend;
    vector<int> ans;

    for (int x : friends)
        isFriend[x] = true;
    
    for (int p : order)
        if (isFriend.count(p)) 
            ans.push_back(p);
    
    return ans;
}

int main() {
    return 0;
}