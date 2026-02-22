/*
Leetcode - 21. Merge Two Sorted Lists : Easy

You are given the heads of two sorted linked lists list1 and list2.
Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
Return the head of the merged linked list.

Examples :-
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]

Constraints :-
• The number of nodes in both lists is in the range [0, 50].
• -100 <= Node.val <= 100
• Both list1 and list2 are sorted in non-decreasing order.
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

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    ListNode* prev = NULL;
    ListNode* curr1 = list1;
    ListNode* curr2 = list2;

    ListNode* head = (list1->val <= list2->val) ? list1 : list2;

    while (curr1 && curr2) {
        // if curr1's value is greater than curr2's, insert that curr1 node before curr1 in list1
        if (curr1->val > curr2->val) {
            ListNode* temp = curr2->next;       // store the curr2's next, so it is not lost
            if (prev) 
                prev->next = curr2;             // link prev's next to curr2
            prev = curr2;   
            curr2->next = curr1;                // link curr2's next to curr1
            curr2 = temp;                       // move curr2 forward
        }

        else {
            // move the pointers forward
            prev = curr1;
            curr1 = curr1->next;
        }
    }
    // loop ends if either list1 or list2 is fully traversed (i.e. either curr1 == NULL or curr2 == NULL)

    // if curr1 == NULL, it means list 1 is fully traversed
    // in this case we need to link the last node of list 1 to the current node of list 2
    // this case happen when curr2 is not NULL as the list2 is not fully traversed
    if (curr2) 
        prev->next = curr2;

    return head;
}

int main() {
    return 0;
}