/*
Leetcode - 203. Remove Linked List Elements : Easy

Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, 
and return the new head. 

Examples :-

Input: head = [1,2,6,3,4,5,6], val = 6
Output: [1,2,3,4,5]

Input: head = [], val = 1
Output: []

Input: head = [7,7,7,7], val = 7
Output: []

Constraints :-
- The number of nodes in the list is in the range [0, 10^4].
- 1 <= Node.val <= 50
- 0 <= val <= 50
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

ListNode* removeElements(ListNode* head, int val) {
    if (head == NULL) return head;

    ListNode* dummy = new ListNode(-1);
    ListNode* temp = dummy;
    ListNode* curr = head;
    
    while (curr) {
        if (curr->val != val) {
            temp->next = curr;
            temp = temp->next;
        }
    
        else temp->next = NULL;
    
        curr = curr->next;
    }
    
    return dummy->next;
}

int main() {
    return 0;
}