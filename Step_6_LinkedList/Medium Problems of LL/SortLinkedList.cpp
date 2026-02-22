/*
Leetcode - 148. Sort List : Medium

Given the head of a linked list, return the list after sorting it in ascending order.

Examples :-
Input: head = [4,2,1,3] __ Output: [1,2,3,4]
Input: head = [-1,5,3,4,0] __ Output: [-1,0,3,4,5]
Input: head = [] __ Output: []

Constraints :-
• The number of nodes in the list is in the range [0, 5 * 10^4].
• -10^5 <= Node.val <= 10^5
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

// Naive Approach : Time Complexity : O(n) + O(n log n) + O(n) __ Space Complexity : O(n)
/*
Naive Approach - We want to sort the linked list in ascending order. We can achieve so by sorting its data.
- Use an array to store the data of linked list nodes
- Sort the array
- Traverse the linked list and replace its data according to the sorted array data.
*/
ListNode* sortListNaive(ListNode* head) {
    vector<int> data;

    ListNode* curr = head;
    while (curr) {
        data.push_back(curr->val);
        curr = curr->next;
    }

    sort(data.begin(), data.end());
        
    curr = head;
    for (int x : data) {
        curr->val = x;
        curr = curr->next;
    }
    return head;
}


// Merge Sort Approach

// merging 2 sorted linked list
ListNode* merge(ListNode* list1, ListNode* list2) {
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

ListNode* mergeSort(ListNode* head) {
    if (head == NULL || head->next == NULL)
        return;
    
    // find mid
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // now slow points at middle element
    ListNode* head2 = slow->next;           // 2nd half's head
    slow->next = NULL;                      // detach first half tail from second half, by pointing its tail to NULL

    mergeSort(head);
    mergeSort(head2);      // second half
    head = merge(head, head2);

    return head;
}

ListNode* sortList(ListNode* head) {
    return mergeSort(head);
}

int main() {
    return 0;
}