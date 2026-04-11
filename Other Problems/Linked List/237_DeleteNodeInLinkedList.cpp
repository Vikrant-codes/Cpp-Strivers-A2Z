/*
Leetcode - 237. Delete Node in a Linked List : Medium

There is a singly-linked list head and we want to delete a node node in it.
You are given the node to be deleted node. You will not be given access to the first node of head.
All the values of the linked list are unique, and it is guaranteed that the given node node is not the 
last node in the linked list.

Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:
- The value of the given node should not exist in the linked list.
- The number of nodes in the linked list should decrease by one.
- All the values before node should be in the same order.
- All the values after node should be in the same order.

Custom testing:
- For the input, you should provide the entire linked list head and the node to be given node. 
  node should not be the last node of the list and should be an actual node in the list.
- We will build the linked list and pass the node to your function.
- The output will be the entire list after calling your function.

Examples :-

Input: head = [4,5,1,9], node = 5 __ Output: [4,1,9]
Explanation: You are given the second node with value 5, 
the linked list should become 4 -> 1 -> 9 after calling your function.

Input: head = [4,5,1,9], node = 1 __ Output: [4,5,9]
Explanation: You are given the third node with value 1, 
the linked list should become 4 -> 5 -> 9 after calling your function.

Constraints :-
• The number of the nodes in the given list is in the range [2, 1000].
• -1000 <= Node.val <= 1000
• The value of each node in the list is unique.
• The node to be deleted is in the list and is not a tail node.
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

// Optimal Approach : Time Complexity : O(1) __ Space Complexity : O(1)
/*
Key constraint
- We are NOT given the head of the linked list.
- We are only given the pointer to the node that must be deleted.

>> Why normal deletion doesn’t work
Normally, to delete a node:
    prev->next = node->next;
    delete node;
But here, we don’t have prev. So we can’t change the previous node’s pointer.

-> The idea used here
Instead of deleting the given node directly, we:
👉 Copy the next node’s data into the current node
👉 Then delete the next node

One-line intuition
👉 “We can’t delete this node, so we turn it into the next node and delete that instead.”
*/
void deleteNode(ListNode* node) {
    ListNode* nextNode = node->next;

    node->val = nextNode->val;
    node->next = nextNode->next;
    
    delete nextNode;
}


int main() {
    return 0;
}