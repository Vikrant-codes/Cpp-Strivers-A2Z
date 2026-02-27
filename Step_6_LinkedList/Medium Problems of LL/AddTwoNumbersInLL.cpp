/*
Leetcode - 2. Add Two Numbers : Medium

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Examples :-

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Input: l1 = [0], l2 = [0]
Output: [0]

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

Constraints :-
- The number of nodes in each linked list is in the range [1, 100].
- 0 <= Node.val <= 9
- It is guaranteed that the list represents a number that does not have leading zeros.
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

// Optimal Approach : Time Complexity : O( max(m, n) ) __ Space Complexity : O(1)
/*
Core Idea
Each linked list represents a number digit by digit (reverse order). (LSB is the head and MSB is the tail node)
So we simulate manual addition the same way we do on paper:
- Add corresponding digits
- Keep track of carry
- Store the result digit
- Move forward for the next pair of digits

Intuition Behind the Approach

1️⃣ Traverse Both Lists Together
- Use 2 pointers to move through the two lists
- Even if one list ends earlier (this might we case when the two numbers have different count of digits),
  we treat its digit as 0.

2️⃣ Simulate Elementary Addition
For each position:
    sum = digit1 + digit2 + carry
Now, this sum might exceed 9, like the sum can be 10 or 15 or 18.
The max value of this sum can be 19 (which is the case when both digit1 & digit2 == 9 and carry = 1)
If sum > 9 : we need to propagate a carry of 1 forward, and also we need to store only the lsb of sum as result
    Ex- for sum = 15, we need to store LSB of 15 which is 5 in result and move carry 1 forward.
    This LSB can be found using sum % 10.
Else: we can directly store the sum as result and no need to propagate a carry

3️⃣ Build Result Using Dummy Node
We use a dummy node to simplify list construction. Use a pointer (t3) to traverse this dummy chain and link the resultant digits
- Avoids special case for first node
- Always attach new node to t3->next
- Move t3 forward

>> Complexity Analysis:

-> Time Complexity
Let: m = length of l1, n = length of l2
We traverse both lists once.
The loop runs till all the digits are not traversed. Thus, max(n, m) times.
Time Complexity = O(max(n, m))

-> Space Complexity
We create a new linked list to store the result.
In worst case: Result length = max(n, m) + 1 (if final carry exists)
So auxiliary space used: Space Complexity = O(max(n, m))
But, since this is the answer list so we might not want to consider it as extra space. Then, space complexity = O(1)
*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *t1 = l1, *t2 = l2;        // pointers to traverse the two lists
    ListNode *dummy = new ListNode(-1);     // dummy node for the answer linked list
    ListNode *t3 = dummy;               // pointer to this answer chain / sumList
    int carry = 0;

    while (t1 || t2) {
        int d1 = (t1 != NULL) ? t1->val : 0;        // In case list-1 has ended, consider the digit to be 0
        int d2 = (t2 != NULL) ? t2->val : 0;        // In case list-2 has ended, consider the digit to be 0

        int sum = d1 + d2 + carry;
        
        if (sum > 9) carry = 1;
        else carry = 0;
        sum = sum % 10;     // this will work fine for both sum > 9 case and sum <= 9
        
        ListNode* newNode = new ListNode(sum);
        t3->next = newNode;         // join the new result digit at the end of answer chain / sumList
        t3 = newNode;               // move the sumList pointer forward

        if (t1) t1 = t1->next;      // move list-1 pointer forward if it isn't NULL 
        if (t2) t2 = t2->next;      // move list-2 pointer forward if it isn't NULL
    }

    // if a carry of 1 still remains, we need to create a new node with value '1' and chain it to sumList
    if (carry == 1)
        t3->next = new ListNode(1);
    
    return dummy->next;             // head of the sumList, i.e., the LSB of the resultant
}

ListNode* addTwoNumbers_2(ListNode* l1, ListNode* l2) {
    ListNode *t1 = l1, *t2 = l2;        // pointers to traverse the two lists
    ListNode *dummy = new ListNode(-1);     // dummy node for the answer linked list
    ListNode *t3 = dummy;               // pointer to this answer chain
    int carry = 0;
    // Instead of explicitly checking carry bit at end, we can run the loop till either list1 digit / list2 digit / carry exists
    while (t1 || t2 || carry) {
        int d1 = (t1 != NULL) ? t1->val : 0;
        int d2 = (t2 != NULL) ? t2->val : 0;

        int sum = d1 + d2 + carry;
        
        if (sum > 9) carry = 1;
        else carry = 0;
        sum = sum % 10;     // this will work fine for both sum > 9 and sum <= 9
        
        ListNode* newNode = new ListNode(sum);
        t3->next = newNode;
        t3 = newNode;
        
        if (t1) t1 = t1->next;      // move num1 pointer forward only if it isn't NULL 
        if (t2) t2 = t2->next;      // move num1 pointer forward only if it isn't NULL
    }
    
    return dummy->next;
}

int main() {
    return 0;
}