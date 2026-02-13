/*
Leetcode - 141. Linked List Cycle : Easy

Given head, the head of a linked list, determine if the linked list has a cycle in it.
There is a cycle in a linked list if there is some node in the list that can be reached again by 
continuously following the next pointer. 
Internally, pos is used to denote the index of the node that tail's next pointer is connected to. 
Note that pos is not passed as a parameter.
Return true if there is a cycle in the linked list. Otherwise, return false.

Examples :-

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

Input: head = [1], pos = -1
Output: false
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
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Using Hashset : Time Complexity : O(n) __ Space Complexity : O(n)
/*
Intuition:
While traversing the linked list, every node should normally be visited only once.
• We use a set to store the nodes we have already visited.
• As we move forward, we check whether the current node already exists in the set.
• If it does, it means we reached the same node again → the list looped back → a cycle exists.
• If we reach NULL, no node was repeated, so there is no cycle.
In short: a cycle means revisiting the same node again, and the set helps detect repeated visits.
*/
bool hasCycleNaive(ListNode *head) {
    set<ListNode*> s;
    ListNode* curr = head;
    while (curr) {
        if (s.count(curr))
            return true;
        s.insert(curr);
        curr = curr->next;
    }  
    return false;
}

bool hasCycleStriversNaive(ListNode *head) {
    unordered_map<ListNode*, int> mpp;
    ListNode* temp = head;
    while (temp) {
        if (mpp.find(temp) != mpp.end())
            return true;
        mpp[temp] = 1;
        temp = temp->next;
    }
    return false;
}

// Optimal Approach (Floyd’s Cycle Detection (Tortoise and Hare) approach) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
This is called the Floyd’s Cycle Detection (Tortoise and Hare) approach. The intuition comes from relative speed.

>> Core Idea
• Two pointers start from the head:
    • slow moves 1 step at a time
    • fast moves 2 steps at a time
• If there is no cycle, fast will reach NULL first.
• If there is a cycle, both pointers eventually enter the loop, and the faster one must catch the slower one.

>> Intuition (Why they must meet)
Think of the cycle as a circular track. Once both pointers enter the loop:
- slow moves 1 step per iteration.
- fast moves 2 steps per iteration.
So in every iteration, fast gains 1 extra step over slow. 

This means:
- The distance between them inside the loop keeps decreasing by 1 (modulo loop length).
- Since the loop has finite length, this distance cannot decrease forever.
- Eventually, the distance becomes 0 → both pointers land on the same node.
This is similar to a faster runner eventually lapping a slower runner on a circular track.

## Why meeting is guaranteed mathematically
Assume: Loop length = L
When both pointers are inside the loop, their positions differ by some distance d.
After each step: new distance = (d - 1) mod L
Since there are only L possible distances, after at most L steps the distance becomes 0, meaning they meet.

>> Summary
• No loop → fast pointer reaches end.
• Loop exists → fast pointer keeps gaining on slow pointer.
• Finite loop length guarantees collision.
*/
bool hasCycle(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
        
    return false;
}

int main() {
    return 0;
}