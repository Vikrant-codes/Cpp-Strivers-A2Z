/*
Leetcode - 2095. Delete the Middle Node of a Linked List : Medium

You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.

The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, 
where ⌊x⌋ denotes the largest integer less than or equal to x.

For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.

Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]
Explanation:
Since n = 7, node 3 with value 7 is the middle node. We return the new list after removing this node.

Input: head = [1,2,3,4]
Output: [1,2,4]
Explanation:
For n = 4, node 2 with value 3 is the middle node.

Input: head = [2,1]
Output: [2]
Explanation:
For n = 2, node 1 with value 1 is the middle node. Node 0 with value 2 is the only node remaining after removing node 1.
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
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Naive Approach: Time Complexity : O(n) + O(n / 2) __ Space Complexity : O(1)
/*
- Traverse the linked list and finds its length. Let n = length of the linked list = no. of nodes in linked list
- Find the index of the middle node, which is : mid = ⌊n / 2⌋.
- Now, we need to reach the node which is just before the middle node, 
    so we can links this node to the next of middle node and delete middle.
- Use a for loop (or a counter) to reach the previoud node of middle node (⌊n / 2⌋ - 1)th node.
- Delete the middle node using this previous node.
*/
ListNode* deleteMiddleNaive(ListNode* head) {
    // if there is only one node (head node), then we need to remove the head and return NULL
    if (head->next == NULL) 
        return NULL;

    int len = 0;
    ListNode* curr = head;
    while (curr) {
        len++;
        curr = curr->next;
    }
    int ind = len/2;
    curr = head;
    for (int i = 0; i < ind-1; i++) 
        curr = curr->next;

    // delete the curr->next node
    ListNode* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
        
    return head;
}

// Optimal Approach (3 Pointers) : Time Complexity : O(n / 2) __ Space Complexity : O(1)
/*
- We need to delete the second middle node, which is present at the index ⌊n / 2⌋.
- We can use the Tortoise-Hare Two Pointers approach to reach this second middle node, 
    but we need the previous node to this second middle node in order to delete this middle node.
- We can thus use a 3rd pointer which points to the previous node to slow, 
    so that when loop ends, slow points to the second middle node and prev points to its previous node.
- Initially, prev points to NULL and when slow moves one step further, prev firstly reaches slow then slow moves ahead
    so that prev is always just one node before to slow.
- Use this prev node to de-link the middle node (slow) from the linked list and then delete it.
- Special Case: If there is only one node (which is head), the middle node is head itself so return NULL.
- Return head of the modified list.
*/
ListNode* deleteMiddle(ListNode* head) {
    // if there is only one node (head node), then we need to remove the head and return NULL
    if (head->next == NULL) 
        return NULL;

    ListNode *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
        
    // Now, slow points to the middle node which needs to be deleted and prev is the previous node
    prev->next = slow->next;
    delete slow;

    return head;
}

// Optimal Approach (2 Pointers Tortoise-Hare Method) : Time Complexity : O(n / 2) __ Space Complexity : O(1)
/*
- We want to reach the previous node to the second middle node in order to delete it.
- In Tortoise-Hare finding middle node problem, we initialize both slow & fast with head and then 
    fast moves 2 step while slow moves 1, and when loop ends slow points to the second middle node.
- But, we want slow to point 1 node before.
- This can be done if we keep slow fixed for just one iteration. 
    In this way fast will reach NULL/last node 1 step before slow could reach the second middle node
    thus, slow will point to the previous node.
- So, we initialize fast to head->next->next before starting the iteration to give fast a headstart.
- In this way, when loop ends, slow points to the previous node.
- Delete the middle node by skipping it from the linked list.
- Special Case: If there is only one node (which is head), the middle node is head itself so return NULL.
- Return head of the modified list.
*/ 
ListNode* deleteMiddleStriver(ListNode* head) {
    // if there is only one node (head node), then we need to remove the head and return NULL
    if (head->next == NULL) 
        return NULL;

    // Initialize slow pointer to head
    ListNode* slow = head;
    // Initialize fast pointer two steps ahead
    ListNode* fast = head->next->next;

    // Traverse until fast reaches end
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
        
    // Now, slow points to one node before the second middle node. Thus, slow->next is the middle node.
    ListNode* temp = slow->next;            // Pointer to middle node
    slow->next = slow->next->next;          // Bypass the middle node
    delete temp;                            // Delete middle node

    return head;
}

int main () {
    return 0;
}