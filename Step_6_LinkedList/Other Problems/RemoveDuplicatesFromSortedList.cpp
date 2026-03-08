/*
Leetcode - 83. Remove Duplicates from Sorted List : Easy

Given the head of a sorted linked list, delete all duplicates such that each element appears only once. 
Return the linked list sorted as well.

Examples :-

Input: head = [1,1,2] __ Output: [1,2]
Input: head = [1,1,2,3,3] __ Output: [1,2,3]

Constraints :-
• The number of nodes in the list is in the range [0, 300].
• -100 <= Node.val <= 100
• The list is guaranteed to be sorted in ascending order.
*/

// There is a similar problem for doubly linked list also

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

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Idea : 
Since the list is sorted, duplicates appear next to each other.
Thus, for any node, if its duplicates exists, then they must appear next to it only.
Now, we want to arrange the list such that each element appears only once.
To do so, we check if duplicates exists for a particular node and if they exists, 
we link this node's next to the next node after skipping the duplicates.

Ex- consider the linked list 1 -> 1 -> 1 -> 2 -> 2 -> 3
The result list must be : 1 -> 2 -> 3
We want to link the first occurrence of each element to the next unequal node
For 1: we will skip all the duplicate 1 nodes and link the '2' to the next of this 1.
While skipping duplicates, we also delete them to free up the memory
*/
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* curr = head;

    while (curr) {
        // if duplicates exist for current node
        if (curr->next != NULL && curr->val == curr->next->val) {
            // traverse till the first node is found whose value is not a duplicate of current node
            ListNode* nextNode = curr->next;
            while (nextNode && nextNode->val == curr->val) {
                ListNode* duplicate = nextNode;
                nextNode = nextNode->next;
                delete duplicate;
            }
            // Now, nextNode points to the first node after the duplicate values of current node
            curr->next = nextNode;                  // link curr's next to nextNode   
        }

        curr = curr->next;   // move curr ahead, it points to the next node after skipping duplicates
    }

    return head;
}

int main() {
    return 0;
}