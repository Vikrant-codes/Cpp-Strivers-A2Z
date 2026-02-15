/*
Leetcode - 234. Palindrome Linked List : Easy

Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

Examples :-
Input: head = [1,2,2,1] __ Output: true
Input: head = [1,2] __ Output: false

Constraints :-
- The number of nodes in the list is in the range [1, 10^5].
- 0 <= Node.val <= 9

Follow up: Could you do it in O(n) time and O(1) space?
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

// Naive Approach (Storing data of all nodes of linked list) (Using Stack): Time Complexity : O(2*n) __ Space Complexity : O(n)
/*
• Traverse the linked list from start to end, and push each node's value into a stack.
• Once done, start again from the head of the linked list.
• For each node, pop an element from the stack and compare it with the current node’s value.
• If any value doesn’t match, return false — it’s not a palindrome.
• If all values match till the end, return true — the list is a palindrome.
*/
bool isPalindromeNaive(ListNode* head) {
    stack<int> st;
    ListNode* curr = head;
    while (curr) {
        st.push(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr) {
        if (curr->val != st.top())
            return false;
        st.pop();
        curr = curr->next;
    }
    return true;
}

// Optimal Approach : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
The idea of this approach is simple:
| A linked list is a palindrome if the first half and the second half (reversed) become identical when compared node by node.
So the steps are:
- Find the middle of the list.
- Reverse the second half.
- Compare first half with reversed second half.
- Restore the list.
The correctness comes from how we split the list and why the correct middle is chosen.

### Reversing the Second Half 
>> For Odd-length linked list
- It has only 1 middle node
- The second half starts after this middle node
- Ex: Consider the linked list : 1 → 2 → 3 → 2 → 1
- The middle of this linked list is [3]. So, the second half which starts after this middle Node is 2 → 1.
- We reverse this second half. It becomes 1 → 2. (3 is still pointing to 2 because the 3's next pointer remains unchanged).
- Now, we traverse both halves simultaneously and check if Node matches. 
- One pointer is at head (1), while the other is at the head of the reversed second half (1)

>> For Even-length linked list (✅ Why we return the first middle in even-length lists)
- In an even-length list there are two middle nodes.
    Example:
        1 → [2] → [2] → 1
             ↑     ↑
            mid1  mid2
- Now, if we consider mid2 as the middle node, then the second half would only have 1.
- But, that's not the case, since, mid2 itself is part of the second half then mid2 must be reversed as part of second half.
- The second half is 2 → 1, which needs to be reversed and this second half starts after the mid1.

--> So, we return the first Middle Node so that we get the correct second half for both even & odd length linked list

### Algorithm :-
• Return true if the list is empty or has only one node, since such lists are palindromes by default.
• Use Tortoise & Hare approach to get the middle node of the linked list(return the first middle node in case of even length).
• Reverse the second half of the linked list starting from the node after the middle (middle->next), preparing it for comparison.
• Set two pointers: one at the head of the list and the other at the head of the reversed second half, to compare both halves.
• Compare both halves node by node; if any mismatch occurs, return false, otherwise continue till the end of either list.
• Reverse the second half again to restore the original list structure, and return true if all nodes matched successfully.
*/

// Helper function to get the Middle Node of the linked list (first middle in case of even length)
ListNode* getMiddleNode(ListNode* head) {
    ListNode* slow = head, *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Helper function to reverse the linked list starting from the start node
ListNode* reverseLL(ListNode* start) {
    ListNode* curr = start, *prev = NULL;
    while (curr) {
        ListNode* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;        // new start node of second half after reversal
}

bool isPalindrome(ListNode* head) {
    // Check if the linked list is empty or has only one node
    if (head == NULL || head->next == NULL)
        return true;               // Already a palindrome by definition, so return true

    ListNode* middle = getMiddleNode(head);        // get the middle Node
    ListNode* revHead = reverseLL(middle->next);   // reverse the second half (starts from middle->next)

    ListNode *p1 = head, *p2 = revHead;     // Pointers to first half (p1) & the reversed second half (p2)

    // Compare data values of nodes from both halves
    while (p2) {
        if (p1->val != p2->val) {
            // If values do not match, the list is not a palindrome
            reverseLL(revHead);    // Reverse the second half back to its original state
            return false;
        }
        p1 = p1->next;             // move p1 forward
        p2 = p2->next;             // move p2 forward
    }

    reverseLL(revHead);            // Reverse the second half back to its original state
    return true;            
}


int main() {
    return 0;
}