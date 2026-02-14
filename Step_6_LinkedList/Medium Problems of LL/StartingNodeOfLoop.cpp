/*
Leetcode - 142. Linked List Cycle II

Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again 
by continuously following the next pointer. 
Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). 
It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.

Examples :-

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.

Constraints :-
• The number of the nodes in the list is in the range [0, 10^4].
• -10^5 <= Node.val <= 10^5
• pos is -1 or a valid index in the linked-list.

Follow up: Can you solve it using O(1) (i.e. constant) memory?
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Naive Approach: Time Complexity : O(n) __ Space Complexity : O(n)
/*
We used the hashset approach to detect the existence of loop in the linked list.
this same approach can also be used to find the starting point/node of the loop.

>> Intuition behind this approach
The idea is based on remembering nodes we have already visited.
When traversing a normal linked list:
    • every node is visited only once
    • eventually we reach NULL.
But in a linked list with a cycle:
    • after some point, traversal starts repeating the same nodes again.
    • the first repeated node is exactly the starting node of the cycle.

>> How this logic works step by step
1. Start from head.
2. Maintain a set/map that stores addresses of visited nodes.
3. For every node:
    • If the node is not in the set, insert it and move forward.
    • If the node already exists in the set, it means:
        we have come back to a node seen before → so a cycle exists → this node is the entry point of the loop.

>> Why the first repeated node is the cycle start
- Before entering the cycle, nodes are visited only once.
- Once inside the cycle, traversal keeps moving in the loop.
The first time you revisit any node must be the point where the cycle connects back — the cycle’s starting node.
*/
ListNode *detectCycle(ListNode *head) {
    ListNode* curr = head;
    unordered_set<ListNode*> s;
    while (curr) {
        if (s.count(curr))
            return curr;
        s.insert(curr);
        curr = curr->next;
    }
    return NULL;
}

// Optimal Approach (Using Two Pointers (Slow & fast) - Tortoise-Hare approach): Time Complexity: O(n) __ Space Complexity: O(1)
/*
Intuition of the approach
We already know that when slow and fast pointers meet, a cycle exists.
Now the question is: why does resetting one pointer to head give the start of the loop?

Think about what happens after collision:
1. The fast pointer has been moving faster, so inside the cycle it has already made extra rounds.
2. Because of these extra rounds, when the collision happens, the fast pointer is positioned in such a way that:
    the distance from collision point → cycle start equals the distance from head → cycle start, i.e.
    distance from collision point → cycle start = distance from head → cycle start.
So when we:
- move one pointer from head, and
- move the other from the collision point,
both at the same speed,
they are essentially covering equal remaining distances to reach the cycle start.
Since both move one step at a time, they reach that point together — and that point is exactly the first node of the loop.
*/
// Mathematical Proof (Why this works ?)
/*
Step 1 — Situation before collision
Let
    • l = distance from head to start of loop.
When slow reaches the start of the loop:
    • slow has travelled l
    • fast has travelled 2l (because it moves twice as fast)
So fast has travelled l more distance than slow.
Since both are now inside the loop, this extra distance means:
    | fast is ahead of slow inside the loop by a distance equal to l.
Let this distance between fast and slow inside the loop be called 'd'.
So at this moment:
    | distance between fast and slow inside loop = d

Step 2 — Why they collide after d steps
Inside the loop:
    • slow moves 1 step
    • fast moves 2 steps
So in every step, fast reduces the gap by 1 node.
If the gap is d, fast needs exactly d steps to catch slow (so that the distance b/w them becomes 0).
During these d steps:
    • slow moves d steps forward (from its initial position which was start of loop)
    • fast moves 2d steps forward

Step 3 — Position of slow at collision
Slow started these d steps from the start of the loop.
After moving d steps, slow is now 'd' distance ahead of the loop start.
Since the loop length is fixed, the remaining distance from this collision point back to the loop start is:
rem = (loop length − d)

Step 4 — Loop Length & Remaining Distance from collision point back to loop start
Now, the loop length can be calculated by considering the initial scenario,
When slow was at the start node of loop
- fast was 'l' distance ahead of slow
- the distance between fast and slow inside the loop was 'd'
So, loop length must be the sum of these two, i.e. loop length = l - d.

So, the remaining distance from this collision point back to the loop start is = rem = (loop length − d) = (l + d - d) = l.

Step 5 — Why resetting slow works
Now:
- place slow at head → it needs l steps to reach loop start
- fast stays at collision → it also needs l steps to reach loop start
Both move one step at a time.
So after exactly l moves, both reach the same node — the start of the loop.

>> Intuition in one line
The extra distance fast gains before slow enters the loop becomes 
exactly the distance from the meeting point back to the loop start, 
which is why starting one pointer from head and moving both equally makes them meet at the loop entry.
*/
ListNode *detectCycle(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        // if slow and fast collides -> loop exists
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

int main() {
    return 0;
}