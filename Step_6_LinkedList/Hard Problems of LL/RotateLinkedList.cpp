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

// Naive Approach : Time Complexity : O(n) + O(n * k) __ Space Complexity : O(1)
/*
Approach :-
🔹 Basic Idea
We want to rotate the linked list to the right by k positions → meaning: last k nodes move to the front.
Instead of doing it in one go, we: Rotate the list one step at a time (k times).

>> Observation :-
Suppose n = length of linked-list, then if we rotate it n times, we get the same list back (as nodes moves 1 full cycle).
So, if k > n, we can remove these full cycle shifts and only do the remaining shifts. 
Ex- assume n = 5 and k = 8, then rotating list 8 times is equivalent to rotating it 3 times.
So, we can do 'k = k % n' as this will reduce our work a lot.
Ex- assume k = 10000003 and n = 5, then instead of rotating the list 10000003 times, we can rotate it 3 times (10000003 % 5 = 3).

>> helper function -- rotateListOnce() --> shifts the linked list right by 1 (last node is moved to 1st position)
• Traverse to the last node (tail) and keep track of the second last node (prev)
• Break the link: prev->next = NULL → now prev becomes new tail
• Move last node to front: tail->next = head
• Return tail as new head

>> main function -- rotateRightNaive()
• Edge Case handling : If list is empty or has only 1 node, then rotating it k times doesn't matter becuase list remains same.
    So, for this condition return head
• Find length of the linked list (len)
• Reduce unnecessary work: k = k % len
• If k becomes 0, we don't need to do any rotation -> return head.
• Else, run a loop k times and use helper function to rotate the list once k times.
• Return new head.

*/
// helper function -- rotates the linked-list to the right 1 time (only moves the last node to the head) 
ListNode* rotateListOnce(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* tail = head;

    while (tail->next) {
        prev = tail;
        tail = tail->next;
    }
    
    prev->next = NULL;      // detach tail node ... make prev next NULL as prev becomes the new tail
    tail->next = head;      // add tail node to the start of linked list
    
    return tail;            // tail becomes the new Head of the linked list
}

ListNode* rotateRightNaive(ListNode* head, int k) {
    // if list has 0 or 1 node, then 'k' doesn't matter -> return head
    if (head == NULL || head->next == NULL) 
        return head;

    int len = 1;
    ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
        len++;
    }

    k = k % len;
    if (k == 0) return head;

    // rotate linked list to the right k times
    for (int i = 0; i < k; i++) {
        head = rotateListOnce(head);
    }
    return head;
}


// Optimal Approach : Time Complexity : O(n) + O(n - k) __ Space Complexity : O(1)
/*
>> Observation:-
Assume, list = 1 → 2 → 3 → 4 → 5 → 6 → 7 and k = 4
The resultant list must be: 4 → 5 → 6 → 7 → 1 → 2 → 3

In this example, we see that the nodes last 4 nodes i.e. (4 → 5 → 6 → 7) comes to front.
7's next point to the previous head of the list (1) and 3's next point to NULL.
3 becomes the new tail of the list and 4 becomes the new head.

so we need to divide the list into two parts (1 → 2 → 3 and 4 → 5 → 6 → 7), make 3's next point to NULL to separate them.
Link tail's next to head (7 → 1) and then return 4 as the newHead.
this newHead 4 is at the kth position from end (or, (size-k+1)th position from start)
the newTail (3) is at the (k+1)th position from end (or, (size - k)th position from start)

So, we just need to track these nodes and change the links and no need to rotate the list manually k-times.

As seen in naive approach, we can do k = k % len so that k remains less than n and our works simplifies.

>> Approach:-
• Edge Case handling : if (head == NULL || k == 0) return head
    - head = NULL means list is empty so no need to rotate it or do anything    
    - k = 0 means we don't need to perform any rotation, so simply return head
• Find the length of the linked list and also the tail node
    - initialize len/size = 1, tail = head
    - Move tail pointer ahead until (tail->next != NULL), increment size when moving tail ahead
• k = k % size
• if (k == 0) return head
    - after modifying k (doing k = k % 10), k might become 0, for that case return head
• Find the (size - k)th node from start as this will be the newTail.
• newHead will be the next node of this newTail.. (since newTail is (k+1)th node from end and newHead is kth node from end).
• So, newHead = newTail->next
• detach newHead and newTail -> make newTail's next point to NULL.
• join the previous tail's next to previous head. (to link the two portions, to move the last k nodes to the front)
• return newHead

🔹 Key Insight
| Rotation is just changing the breaking point of a circular list, not moving nodes repeatedly.
When we do tail->next = head, we are making the list circular and then we break the list at a particular node 
to get the rotated list.
*/

ListNode* rotateRight1(ListNode* head, int k) {
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

// Implementation 2 :- Using a helper function 

ListNode* getNthNode(ListNode* head, int n) {
    ListNode* temp = head;
    while (n != 1) {
        temp = temp->next;
        n--;
    }
    return temp;
}

ListNode* rotateRight2(ListNode* head, int k) {
    if (head == NULL || k == 0) return head;

    int size = 1;           // size of linked-list
    ListNode* tail = head;  // tail-node of linked list
    while (tail->next) {
        tail = tail->next;
        size++;
    }
    
    k = k % size;
    if (k == 0) return head;
    
    // the newTail node will be at (size - k) position in the linked list (considering 1-based indexing)
    ListNode* newTail = getNthNode(head, size - k);

    // the newHead would be the kth node from end of linked-list.... this will be the next node of newTail
    ListNode* newHead = newTail->next;
    newTail->next = NULL;       // detach this newHead from newTail
    tail->next = head;          // link 'head' to tail
    
    return newHead;
}

// Other Implementation 
ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL) return head;

    int len = 1;
    ListNode* tail = head;
    while (tail->next) {
        len++;
        tail = tail->next;
    }

    k = k % len;
    if (k == 0) return head;
    
    int x = len - k;
    ListNode* curr = head;
    while (x != 1) {
        curr = curr->next;
        x--;
    }

    ListNode* newHead = curr->next;
    tail->next = head;
    curr->next = NULL;
    
    return newHead;
}

int main() {
    return 0;
}