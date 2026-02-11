/*
Leetcode - 876. Middle of the Linked List : Easy

Given the head of a singly linked list, return the middle node of the linked list.
If there are two middle nodes, return the second middle node.

Examples :-

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

Constraints :-
- The number of nodes in the list is in the range [1, 100].
- 1 <= Node.val <= 100
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
The Naive/Brute Force Approach to find the Middle Node of the linked list is -
- Calculate size of the linked list (traverse the entire linked list and find the size)
- Calculate mid node number (in case of two middle nodes, we need to return the second middle node)
    Thus, if size = 5, we need to return the 3rd node, 
    but,  if size = 6, there are 2 middle nodes (3rd & 4th) and we have to return the 4th one.
    The general formula to calculate mid for this scenario would be mid = size / 2 + 1. 
    Ex- For size = 5, mid = size / 2 + 1 ==> mid = (5 / 2) + 1 ==> mid = 2.5 + 1 ==> mid = 3.5 ==> mid = 3 (integer part only)
    For size = 6, mid = size / 2 + 1 ==> mid = (6 / 2) + 1 ==> mid = 3 + 1 ==> mid = 4.
- Traverse the linked list again starting from head and return the mid node.    
*/
// Time Complexity : O(n + n/2) __ Space Complexity : O(1)
ListNode* middleNodeNaive(ListNode* head) {
    if (head->next == nullptr) 
        return head;
    // it is not actually necessary to check for single node as the algorithm would work for single node as well
    // Calculate Size
    int size = 0;
    ListNode* curr = head;
    while (curr) {
       size++;
       curr = curr->next; 
    }
    // Calculate Mid
    int mid = size / 2 + 1;
    // Get the mid Node
    int k = 1;
    curr = head;
    while (k < mid) {
        curr = curr->next;
        k++;
    }
    return curr;
}

ListNode* middleNodeNaiveStriver(ListNode* head) {
    int cnt = 0;
    ListNode* temp = head;
    while (temp) {
        cnt++;
        temp = temp->next;
    }
    int mid = (cnt / 2) + 1;
    temp = head;
    while (temp) {
        mid--;
        if (mid == 0) break;
        temp = temp->next;
    }
    return temp;
}

// Optimal Approach (TortoiseHare Method) (Slow & Fast Pointers) : Time Complexity : O(n / 2) __ Space Complexity : O(1)
/*
The idea is based on moving at different speeds.

>> Basic intuition
Imagine two people starting from the same point on a track:
- Slow (tortoise) walks 1 step at a time.
- Fast (hare) runs 2 steps at a time.
By the time the fast pointer reaches the end of the list, the slow pointer has covered half the distance.
So the slow pointer naturally ends up at the middle.

>> Why this works
Let the list length be n.
Each loop:
- slow moves 1 node
- fast moves 2 nodes
When fast reaches the end:
- fast has moved roughly n nodes
- slow has moved roughly n/2 nodes
So slow is at the middle.

>> Key intuition in one line
| Fast reaches the end twice as quickly, so slow must be halfway when that happens.
*/
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // move 1 step
        fast = fast->next->next;    // move 2 steps
    }
    return slow;
}

int main() {
    return 0;
}