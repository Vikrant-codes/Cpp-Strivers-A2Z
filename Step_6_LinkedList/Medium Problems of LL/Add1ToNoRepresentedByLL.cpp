/*
GFG - Add 1 to a Linked List Number : Medium

You are given a linked list where each element in the list is a node and have an integer data. 
You need to add 1 to the number formed by concatinating all the list node numbers together and 
return the head of the modified linked list. 

Note: The head represents the first element of the given array.

Examples :-

Input: LinkedList: 4->5->6 __ Output: 457
Explanation: 4->5->6 represents 456 and when 1 is added it becomes 457. 

Input: LinkedList: 1->2->3 __ Output: 124
Explanation:  1->2->3 represents 123 and when 1 is added it becomes 124. 

Constraints :-
- 1 <= len(list) <= 10^5
- 0 <= list[i] <= 9
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node* next;

    Node(int x){
        data = x;
        next = NULL;
    }
};

// Optimal Approach (Iterative) : Time Complexity : O(3n) __ Space Complexity : O(1)
/*
Approach :-
Since the least significant digit is at the end of the list, we can’t process it directly using a single traversal. 
Therefore, to perform addition from the end, we need to reverse the list.

- Reverse the list and start from the head and add 1. Carry it forward if needed (if digit is 9).
    - If digit is less than 9, simply add 1 and exit the loop
    - If digit is 9, add it should become 10, so we make it 0 and forward a carry of '1'.
- If a carry remains after the last node, add a new node with value 1.
- Reverse the list again to restore the original order and return the head of the modified list.
*/

// helper function to reverse the linked list 
Node* reverseLL(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    while (curr) {
        Node* temp = curr->next;
        curr->next = prev;
        
        prev = curr;
        curr = temp;
    }
    
    return prev;
}
  
Node* addOne_A(Node* head) {
    // reverse the Linked List
    head = reverseLL(head);   
    
    // add one ... propagate carry forward if current digit is 9
    Node* curr = head;
    while (curr->next) {
        if (curr->data < 9) {
            curr->data += 1;
            break;
        }
        else {
            curr->data = 0;
        }
        curr = curr->next;
    }
    // loop exits if the first non-9 digit is found & incremented 
    // or if curr reaches the last digit (first digit of actual number)
    // we explicitly check the last digit case to check if it is 9
    if (curr->next == NULL) {
        if (curr->data < 9) curr->data += 1;
        else {
            curr->data = 0;             // make the last digit (first digit) 0
            curr->next = new Node(1);   // add a new '1' digit at the end
        }
    }
    
    return reverseLL(head);     // again reverse the Linked List and then return the head
}

Node* addOne_B(Node* head) {
    // reverse the Linked List
    head = reverseLL(head);   
    
    // add one ... propagate carry forward if current digit is 9
    Node* curr = head;
    while (curr) {
        if (curr->data < 9) {
            curr->data += 1;
            break;
        }
        // if current digit is 9
        else {
            curr->data = 0;
            // if this '9' is the last digit, we need to add a '1' at the end
            if (curr->next == NULL) {
                curr->next = new Node(1);
                break;
            }
        }
        curr = curr->next;
    }
    
    return reverseLL(head);
}

Node* addOneStriver(Node* head) {
    // reverse the Linked List
    head = reverseLL(head);   
    
    // add one ... propagate carry forward if current digit is 9
    Node* temp = head;
    int carry = 1;
    while (temp) {
        temp->data += 1;
        
        if (temp->data < 10) {
            carry = 0;
            break;
        }
        else {
            temp->data = 0;
            carry = 1;
        }
        
        temp = temp->next;
    }
    
    head = reverseLL(head);     // reverse the linked list
    
    if (carry == 1) {   // if carry is still '1', we need to add a new Node '1' at head
        Node* newNode = new Node(1);
        newNode->next = head;
        head = newNode;     // this newly added '1' node becomes the new head
    }
    
    return head;
}

// Optimal Approach (Recursive-Backtracking): Time Complexity : O(n) __ Space Complexity : O(n)
/*
In earlier approaches, we reversed the linked list so we can traverse the number represented by the linked-list
from least significant digit (right end) to most significant digit (left end).

We can also use recursive-backtracking approach to do this backward traversal of digits without reversing the linked list.

🔹 Core Idea
Instead of reversing the list, recursion naturally lets us:
- Go till the last node (LSB)
- Start adding +1 while unwinding the recursion
- Propagate carry backward (towards MSB)
So recursion simulates reverse traversal.

For that purpose we create a recursive function and pass head to it initially, 
this function then calls itself for the next node (say temp) till the whole linked list is traversed.
When the temp node (passed node to recursive fn) is NULL, this is the base condition and we return '1' as carry 
since we need to add 1 to the previous digit (which is LSB).
Now, in the recursive stack we move to the previous digit recursive function and update this node's data accordingly.
- If this node's data < 9, adding 1 would be easy and it will not propagate any carry forward.
  So, we simply increment this node's data and the carry is returned as '0'.
- But if the node's data == 9, adding 1 would make it 10. In that case we need to update it to '0' and 
  propagate a carry of '1' to the previous nodes.
Ex- consider for the number : 4 → 9 → 9 → 9.
We initially call the function with '4' as current node.
    - This function calls itself for '9' as current node.
        - This calls itself for the 3rd node ('9')
            - This calls itself for the 4th node ('9')
                - This calls itself for the next node which is NULL
                    due to current node being NULL, carry of 1 is forwarded
                Carry of '1' is added to current digit which is '9', so '9' becomes '0' and carry of '1' is propagated
                List becomes: 4 → 9 → 9 → 0, carry = 1
            Similarly, Carry of '1' is propagated and current node's data is updated to '0'
            List becomes: 4 → 9 → 0 → 0, carry = 1
        Again, carry of '1' is added and '9' becomes '0' and carry of '1' is again propagated
        List becomes: 4 → 0 → 0 → 0, carry = 1
    Now, carry of '1' is added to '4' which becomes '5' and no carry needed to be propagated so carry '0' is returned.
    List becomes: 5 → 0 → 0 → 0, carry = 0
The recursive stack ends..  

>> Recursive Stack Visualisation
Linked list : 4 → 9 → 9 → 9
We are adding +1

🔹 Phase 1: Recursive Calls (Going Down)
Function calls keep going forward until NULL.
    addHelper(4)
      → addHelper(9)
          → addHelper(9)
              → addHelper(9)
                  → addHelper(NULL)
                    Now we hit base case.
                    addHelper(NULL) returns 1   (initial carry)

🔹 Phase 2: Stack Unwinding (Going Up) : Now addition happens while returning.
🔸 Step 1: Last Node (9)
Node = 9, carry = 1 ... 9 + 1 = 10
→ set node = 0
→ return carry = 1
List becomes: 4 → 9 → 9 → 0

🔸 Step 2: Third Node (9)
Node = 9, carry = 1 ... 9 + 1 = 10
→ set node = 0
→ return carry = 1
List becomes: 4 → 9 → 0 → 0

🔸 Step 3: Second Node (9)
Node = 9, carry = 1 ... 9 + 1 = 10
→ set node = 0
→ return carry = 1
List becomes: 4 → 0 → 0 → 0

🔸 Step 4: First Node (4)
Node = 4, carry = 1 ... 4 + 1 = 5
→ no overflow
→ return carry = 0
List becomes: 5 → 0 → 0 → 0

Final returned carry = 0
Final Answer: 5 → 0 → 0 → 0

>> Visual Stack Representation
Think of recursion like this:
        [4]
          ↑
        [9]
          ↑
        [9]
          ↑
        [9]
          ↑
       NULL
Carry flows upward:
    NULL → 1
    9 → 0 carry 1
    9 → 0 carry 1
    9 → 0 carry 1
    4 → 5 carry 0

We see that for this example, after the recursive stack ends, carry '0' is returned so no need to add any new node.
But, for cases with all nodes having '9' value, like ( 9 → 9 → 9 ), the final returned carry is '1' as for these 
cases, the whole list nodes' values get updated to '0' and we need to add a new node with value '1' at the head.
So, after the recursive stack ends, we need to check if carry == 1, if yes, add a new node with value '1' at head.
return the head. 

>> Complexity Analysis:-

-> Time Complexity : 
    - The whole linked list is traversed once - O(n)
    - The addition operation is performed when the recursive stack starts returning (unwinding)
    - During this unwinding, a simple node data check is done and value is updated and carry is returned.
    - So, this amounts of O(1) for each recursive function call
    - Total Complexity : O(n)
-> Space Complexity : 
    - The recursive function calls are stored inside a recursive stack which takes O(n) space
    (This is the only drawback compared to iterative reverse method which is O(1) space)
*/
int addHelper(Node* temp) {
    if (temp == NULL)
        return 1;
    int carry = addHelper(temp->next);
    temp->data += carry;
    if (temp->data < 10) return 0;   // return 0 as carry
    else {
        temp->data = 0;
        return 1;           // return 1 as carry
    }
}

Node* addOne(Node* head) {
    int carry = addHelper(head);
    
    if (carry == 1) {
        Node* newNode = new Node(1);
        newNode->next = head;
        head = newNode;
    }
    
    return head;
}

int main() {
    return 0;
}