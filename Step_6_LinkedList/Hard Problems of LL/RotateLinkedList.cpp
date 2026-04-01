/*
Leetcode - 61. Rotate List : Medium

Given the head of a linked list, rotate the list to the right by k places.

Examples :-

Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Input: head = [0,1,2], k = 4
Output: [2,0,1]

Constraints :-
• The number of nodes in the list is in the range [0, 500].
• -100 <= Node.val <= 100
• 0 <= k <= 2 * 10^9
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

ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL || k == 0) return head;
    
    int size = 1;
    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        size++;
    }

    k = k % size;
    if (k == 0) return head;
    
    ListNode* newTail = head; // place newTail at the (size - k)th node as this will become newTail
    for (int i = 0; i < size - k - 1; i++)
        newTail = newTail->next;
    
    ListNode* newHead = newTail->next;
    newTail->next = NULL;
    tail->next = head;
    
    return newHead;
}

int main() {
    return 0;
}