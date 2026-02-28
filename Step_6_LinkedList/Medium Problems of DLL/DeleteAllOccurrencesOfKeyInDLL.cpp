/*
GFG - Delete all occurrences of a given key in a doubly linked list : Medium

You are given the head_ref of a doubly Linked List and a Key. 
Your task is to delete all occurrences of the given key if it is present and return the new DLL.

Examples :-

Input: 
2<->2<->10<->8<->4<->2<->5<->2
2
Output: 
10<->8<->4<->5
Explanation: All Occurences of 2 have been deleted.

Input: 
9<->1<->3<->4<->5<->1<->8<->4
9
Output: 
1<->3<->4<->5<->1<->8<->4
Explanation: All Occurences of 9 have been deleted.

Your Task:
Complete the function void deleteAllOccurOfX(struct Node** head_ref, int key), 
which takes the reference of the head pointer and an integer value key. 
Delete all occurrences of the key from the given DLL.

Constraints :-
- 1 <= Number of Nodes <= 10^5
- 0 <= Node Value <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

/* a Node of the doubly linked list
struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
}; */

// This struct doesn’t have a constructor because this is C-style structure, not C++-style class design.
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

/*
head_ref is a pointer pointing to the head node pointer.
the head pointer can be reached using *head_ref.

head_ref is used because we want to modify the original head pointer inside the function without returning it.

Why normal Node* head doesn’t work?
When you pass:
    void func(Node* head)
A copy of the head pointer is passed.
If you do head = head->next, only the copy changes.
Original head outside the function remains unchanged ❌

Why Node** head_ref works?
When you pass:
    void func(Node** head_ref)
You pass the address of the head pointer.
Inside the function, *head_ref refers to the original head.
So changing:
*head_ref = (*head_ref)->next;
modifies the real head pointer ✅
*/
void deleteAllOccurOfX(struct Node** head_ref, int x) {
    Node* temp = *head_ref;
    
    while (temp) {
        Node* nextNode = temp->next;    // next node
        
        if (temp->data == x) {
            Node* prevNode = temp->prev;    // prev node
            // change links of prevNode & nextNode
            if (prevNode) prevNode->next = nextNode;
            if (nextNode) nextNode->prev = prevNode;
            
            // if temp was head node itself, we need to move head
            if (temp == *head_ref) 
                *head_ref = (*head_ref)->next;
                
            delete temp;        // delete current node
        }
        
        temp = nextNode;        // move to the next node
    }
}

int main() {
    return 0;
}