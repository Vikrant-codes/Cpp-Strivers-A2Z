/*
Leetcode - 19. Remove Nth Node From End of List : Medium

Given the head of a linked list, remove the nth node from the end of the list and return its head.

Examples :-

Input: head = [1,2,3,4,5], n = 2 __ Output: [1,2,3,5]
Input: head = [1], n = 1 __ Output: []
Input: head = [1,2], n = 1 __ Output: [1]

Constraints :-
- The number of nodes in the list is sz.
- 1 <= sz <= 30
- 0 <= Node.val <= 100
- 1 <= n <= sz

Follow up: Could you do this in one pass?
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
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Naive Approach (Two Pass Solution): Time Complexity: O(len) + O(len-n), where len = size of list __ Space Complexity: O(1)
/*
• We need to delete the nth node from the end. But to know which is the nth node from end, we firstly need to know the size.
• Traverse through the linked list and calculate the size. Let variable sz be the size of linked list.
• Now, we want to delete the nth node from end of linked list.
• To do so, we need to reach the previous node before it and change the links.
• The desired node which needs to be deleted is present at the (size - (n - 1)) index (1 based indexing) of linked list.
• So, the previous node is present at the (size - n) index of linked list.
• We use a counter variable (initialized with 1) and use that to reach the previous node.
• Delete the desired node by removing it from the chain and then deleting it.
• If n was equal to size itself, it means the nth node from end is the head node and we need to delete head in that case. 
*/
ListNode* removeNthFromEndNaive(ListNode* head, int n) {
    int sz = 0;
    ListNode* curr = head;
    while (curr) {
        sz++;
        curr = curr->next;
    }
    // if n is equal to size of the linked list itself, that means the nth node from end is the head node
    if (sz == n)
        return head->next;

    // iterate till the (n+1)th node from end ... the 1-based index of (n+1)th node from end is size - n.
    curr = head;
    int i = 1;
    while (curr) {
        if (i == sz - n) {
            // delete the next node and change the links accordingly
            ListNode* temp = curr->next;
            curr->next = temp->next;
            delete temp;
            break;
        }
        i++;
        curr = curr->next;
    }
    // we could've also used a for loop to iterate till the previous node and delete the links.. the code is below for that
    /*
    // iterate to the previous node which is just one before the one that needs to be deleted 
    curr = head;
    for (int i = 1; i < sz - n; i++)
        curr = curr->next;
    
    ListNode* temp = curr->next;
    curr->next = temp->next;
    delete temp;
    */

    return head;
}

// Optimal Approach (Two Pointers) : Time Complexity : O(len) __ Space Complexity : O(1)
/*
We want to delete the nth Node from end. To do so, we need to reach its previous node.
We know that the distance between the previous node to the nth Node from end and the last node will be n itself.
Example - 
    Assume list: 1 → 2 → 3 → 4 → 5 → 6, n = 3.
    The 3rd node from end is 4 and its previous node is 3. 
    Notice that the last node 6 and the previous node 3 are separated by a distance of 3.

This will remain the case for all cases but if n is equal to linked list size itself, 
then the node to be deleted is head itself and there is no previous node to it. So we need to handle this case separately.

For other cases, we can use this observation that the distance between previous node and last node is 'n'.
We can use this to reach the previous node.
Use two pointers slow and fast. Maintain a gap of n nodes between fast and slow.
• Move fast ahead by n steps. (so, to maintain the gap of n nodes b/w the two pointers)
• Then move both together. (slow initially points to head and fast points to n nodes ahead of slow)
• When fast reaches the last node, slow will be just before the node to delete (the previous node).

When loop ends: fast → last node, slow → node before the one to delete (previous node)
Delete the targeted node

# Edge case handling: deleting head
If we were supposed to delete head, then 'n' would be given equal to size of linked list. 
In that case, moving fast n steps would make it reach NULL. Thus,
    if (fast == NULL)
        return head->next;

>> Time Complexity Analysis:-
- O(n) to move fast pointer n steps ahead of slow at the start
- O(len - n) to reach the last of the linked list
Thus, total time complexity = O(n) + O(len - n) = O(len)
The fast pointer start from head and reaches the last node thus in total we move 'fast' through the entire linked list once.
*/
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    for (int i = 0; i < n; i++) 
        fast = fast->next;
    
    if (fast == NULL)
        return head->next;
    
    ListNode* slow = head;
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;

    return head;
}

int main() {
    return 0;
}