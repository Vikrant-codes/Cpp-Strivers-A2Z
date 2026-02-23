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

// Naive Approach : Time Complexity : O(N) + O(N * log N) + O(N) __ Space Complexity : O(2*N), where N = size of list1 + list2
/*
Approach:-
- Use an array to store the data of both linked lists
- Sort this array to get the data in sorted order
- Generate a new linked list according to this sorted array and return its head.

Complexity Analysis:-
- Time Complexity : 
    Let, n = size of list1, m = size of list2 and N = n + m
    Adding data to array: O(N) :- both lists are traversed once to add the data to the array
    Sorting: O(N log N) :- to sort an array of size N it takes N log N
    Creating New Linked List: O(N) :- the whole array is traversed to create a new linked list
    | Total = O(N) + O(N * log N) + O(N)
- Space Complexity :
    O(N): An array of size N (= n + m) is used to store the data
    O(N): A new linked list of size N is created
*/
ListNode* mergeTwoListsNaive(ListNode* list1, ListNode* list2) {
    if (list1 == NULL && list2 == NULL)
        return NULL;

    vector<int> arr;

    // Push the list-1 elements in the array/vector
    ListNode* curr = list1;
    while (curr) {
        arr.push_back(curr->val);
        curr = curr->next;
    }
    // Push list-2 elements in the vector
    curr = list2;
    while (curr) {
        arr.push_back(curr->val);
        curr = curr->next;
    }
        
    // sort the array elements i.e. the data of linked list nodes
    sort(arr.begin(), arr.end());

    // generate a new linked list for the sorted data and return its head
    ListNode* head = new ListNode(arr[0]);
    curr = head;
    for (int i = 1; i < arr.size(); i++) {
        ListNode* temp = new ListNode(arr[i]);
        curr->next = temp;
        curr = temp;
    }
    return head;
}

// Better Approach: Time Complexity : O(N) + O(N) __ Space Complexity : O(2*N), where N = size of list1 + list2
/*
Approach :-
- We know that the given linked lists are sorted in themselves (list1 is sorted and list2 is also sorted).
- So, we can try to traverse the lists in some better way to get the data in sorted order itself.
- We can use two pointers (one at head of list-1 and another at list-2) and then use the two pointers to get the 
    data in sorted order itself.
- Let curr1 = current node pointer of list-1, and, curr2 = current node pointer of list-2
- Now, while traversing the two lists, we can compare the data of both lists and choose the smaller one 
    and move that pointer forward. Thus, 
    If curr1's data is smaller: put this data in the array, move curr1 forward
    Else if curr2's data is smaller: put this data in the array, move curr2 forward
- If, while traversing, either of the two linked list gets fully traversed, 
    we can push the other list's data to the array directly without comparing as the other list will have data in sorted order.
- Now, array contains data in sorted order itself, no need to sort this explicitly.
- Use this array data to create a new linked list and return its head
*/
ListNode* mergeTwoListsBetter(ListNode* list1, ListNode* list2) {
    if (list1 == NULL && list2 == NULL)
        return NULL;

    vector<int> arr;

    ListNode *curr1 = list1, *curr2 = list2;
    // curr1 = current node pointer of list-1, curr2 = current node pointer of list-2

    while (curr1 && curr2) {
        // if curr1's data is smaller than curr2's, then, add it to array.
        if (curr1->val <= curr2->val) {
            arr.push_back(curr1->val);
            curr1 = curr1->next;            // move curr1 pointer forward
        }
        // else add curr2's data to the array as it is smaller
        else {
            arr.push_back(curr2->val);
            curr2 = curr2->next;            // move curr2 pointer forward
        }
    }
    // loop ends when either curr1 or curr2 becomes NULL

    // if curr1 != NULL (list-1 not fully traversed): need to add remaining elements of list-1 to array
    while (curr1) {
        arr.push_back(curr1->val);
        curr1 = curr1->next;            // move curr1 pointer forward
    }

    // if curr2 != NULL (list-2 not fully traversed): need to add remaining elements of list-2 to array
    while (curr2) {
        arr.push_back(curr2->val);
        curr2 = curr2->next;            // move curr1 pointer forward
    }

    // now, array contains the data in sorted order itself as we pushed the smaller elements of both lists first

    // generate a new linked list for the sorted data of array and return its head
    ListNode* head = new ListNode(arr[0]);
    curr1 = head;
    for (int i = 1; i < arr.size(); i++) {
        ListNode* temp = new ListNode(arr[i]);
        curr1->next = temp;
        curr1 = temp;
    }
    return head;
}

// Time Complexity : O(N) + O(N) __ Space Complexity : O(N), where N = size of list1 + list2
/*
The space complexity can be optimised slightly by avoiding creation of a new final linked list and using the given lists.

- Collect sorted values into arr
- Physically connect the two lists by connecting tail of list1 to head of list2
- Rewrite values in one traversal, now that list1 & list2 are connected, they can be traversed one after another directly
- Return head

We need to handle cases when list1 is empty or list2 is empty or both
*/
ListNode* mergeTwoListsBetterPlus(ListNode* list1, ListNode* list2) {
    if (list1 == NULL && list2 == NULL)
        return NULL;

    vector<int> arr;

    ListNode *curr1 = list1, *curr2 = list2;
    // curr1 = current node pointer of list-1, curr2 = current node pointer of list-2

    while (curr1 && curr2) {
        // if curr1's data is smaller than curr2's, then, add it to array.
        if (curr1->val <= curr2->val) {
            arr.push_back(curr1->val);
            curr1 = curr1->next;            // move curr1 pointer forward
        }
        // else add curr2's data to the array as it is smaller
        else {
            arr.push_back(curr2->val);
            curr2 = curr2->next;            // move curr2 pointer forward
        }
    }
    // loop ends when either curr1 or curr2 becomes NULL

    // if curr1 != NULL (list-1 not fully traversed): need to add remaining elements of list-1 to array
    while (curr1) {
        arr.push_back(curr1->val);
        curr1 = curr1->next;            // move curr1 pointer forward
    }

    // if curr2 != NULL (list-2 not fully traversed): need to add remaining elements of list-2 to array
    while (curr2) {
        arr.push_back(curr2->val);
        curr2 = curr2->next;            // move curr1 pointer forward
    }

    // now, array contains the data in sorted order itself as we pushed the smaller elements of both lists first

    // link the tail of list1 and head of list2 so to merge the two linked lists
    ListNode* head = NULL;
    // if list1 is empty, then the head of the merged list will be head of list2
    if (list1 == NULL)    
        head = list2;
    // else list1 is not empty, then head = list1 and link the two lists to merge them
    else {
        ListNode* tail = list1;
        while (tail->next)
            tail = tail->next;          // reach the tail of list1
        tail->next = list2;             // connect tail of list1 to head of list2
        head = list1;                  // curr1 points to head of list1 as it is the new head
    }

    // now, traverse the final merged list and change its data according to the final sorted order 
    ListNode* curr = head;
    int i = 0;
    while (curr) {
        curr->val = arr[i];         // change the curr nodes' value according to the final sorted order
        curr = curr->next;          // move curr1 forward
        i++;                        // increment 'i' so i points at the next data element
    }

    return head;
}

// My Optimal Approach : O(N) __ Space Complexity : O(1), where N = size of list1 + list2
/*
Instead of using an array to get the data in sorted order and then re-writing the nodes of the two lists, 
we can simply play with pointers and connect the nodes of the two lists in sorted order themselves.

One-line intuition:
| Traverse list1 and list2, and whenever a node in list2 is smaller, insert it at the correct position inside list1.
So, we are inserting list2 nodes at their correct position in list1 and then returning the final head.

1. Both lists are already sorted.
2. Maintain three pointers:
    - curr1 → current node in list1
    - curr2 → current node in list2
    - prev → node before curr1 (to help insert)
3. Decide the final head at the start:
    - Whichever list has the smaller first value becomes the head.
4. Traverse both lists simultaneously.
5. At each step:
    - If curr1->val <= curr2->val
        → move forward in list1
        → update prev = curr1
    - If curr2->val < curr1->val
        → insert curr2 before curr1
        → fix links using prev
        → move curr2 forward
6. Continue until one list finishes.
7. If list2 still has nodes left:
    - Attach remaining nodes to prev->next.

✅ Time Complexity: O(n + m) = O(N)
- Each node of list1 is visited at most once.
- Each node of list2 is inserted/visited at most once.
- No nested re-traversal.
*/
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

// Striver's Optimal Approach: Time Complexity : O(N) __ Space Complexity : O(1)
/*
🔹 One-Line Intuition
| Build a new sorted list by always attaching the smaller current node from the two lists to a dummy chain.

1. Create a dummy node to act as a temporary starting point.
    → This avoids handling special cases for head.
2. Keep a pointer temp that builds the merged list.
3. Use two pointers:
    - t1 → traverses list1
    - t2 → traverses list2
4. Compare current values:
    - Attach the smaller node to temp->next.
    - Move that list’s pointer forward.
5. Move temp forward every time you attach a node.
6. When one list finishes:
    - Attach the remaining part of the other list directly.
    - No need to compare anymore (because remaining nodes are already sorted).
7. Return dummy->next
    → Real head is next of dummy.

🧠 Why Dummy Helps
- No need to track prev
- No need to decide head separately
- No special case for first insertion
- Cleaner pointer manipulation
*/
ListNode* mergeTwoListsStriver(ListNode* list1, ListNode* list2) {
    ListNode *t1 = list1, *t2 = list2;          // pointers to traverse the two lists
    ListNode *dummy = new ListNode(-1);         // a dummy node which acts as head of a dummy chain 
    ListNode *temp = dummy;                     // pointer to traverse the dummy chain

    // now traverse the two lists and connect the smaller ones to the dummy chain
    while (t1 && t2) {
        if (t1->val <= t2->val) {
            temp->next = t1;            // connect this node to the dummy chain
            t1 = t1->next;              // move t1 forward to traverse the rest of the nodes of list1
        }
        else {
            temp->next = t2;            // connect this node to the dummy chain
            t2 = t2->next;              // move t2 forward to traverse the rest of the nodes of list2
        }
        temp = temp->next;          // move dummy chain's pointer forward
    }
    // loop ends when either list1 (t1 == NULL) or list2 (t2 == NULL) is fully traversed

    // if t1 != NULL (nodes still left in t1), we need to attach these nodes to dummy chain
    if (t1) temp->next = t1;

    // Similarly, we need to check for t2 != NULL
    if (t2) temp->next = t2;

    return dummy->next;
}

int main() {
    return 0;
}