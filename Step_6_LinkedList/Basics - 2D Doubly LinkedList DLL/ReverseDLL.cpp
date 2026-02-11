#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    Node* prev;
    int data;
    Node* next;

    Node(int val) : Node(nullptr, val, nullptr){}

    Node(Node* p, int val, Node* n) {
        prev = p;
        data = val;
        next = n;
    }
};

Node* createDLL(vector<int>& arr) {
    if (arr.empty()) return NULL;
    Node* head = new Node(arr[0]);
    Node* temp = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* newNode = new Node(temp, arr[i], nullptr);
        temp->next = newNode;
        temp = newNode;
    }
    return head;
}

void traverseDLL(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << " <- " << temp->data << " -> ";
        temp = temp->next;
    }
    cout << '\n';
}

/*
Naive Idea would be to reverse the data of the Linked list's Nodes. Since Nodes holds data and if we reverse the data itself,
it would mean the linked list is reversed.
Example, consider the linked list: NULL <- 1 <-> 2 <-> 3 <-> 4 -> NULL
The reversed list should look like: NULL <- 4 <-> 3 <-> 2 <-> 1 -> NULL
This can be achieved if we store the data of all Nodes : data = {1, 2, 3, 4}
Then traverse the linked list from head to tail and replace the current Node's data in reverse order of data.

Using a stack data structure to store this data would be helpful as we can insert the data and 
also get the data in reversed order easily by getting stack's top value and then popping it.
*/
// Time Complexity : O(2n) __ Space Complexity : O(1) 
Node* reverseDLLNaive(Node* head) {
    stack<int> st;
    
    Node* curr = head;
    while (curr) {
        st.push(curr->data);
        curr = curr->next;
    }
    
    curr = head;
    while (curr) {
        curr->data = st.top();
        st.pop();
        curr = curr->next;
    }

    return head;
}

/*
Step-by-step intuition

1. What does reversal actually mean?
Original list: 
NULL <- 1 <-> 2 <-> 3 <-> 4 -> NULL
After reversal: NULL <- 4 <-> 3 <-> 2 <-> 1 -> NULL
Notice:
• No node values change.
• Only pointer directions change.
So if every node swaps: next ↔ prev, the whole list automatically reverses.

2. What happens after swapping?
Suppose we are at node 2.
Before swap:
    prev = 1
    next = 3
After swap:
    prev = 3
    next = 1
Now something important happens:
👉 The next node to process is not next anymore.
Because:
• next now points backward.
• The original forward node is now in prev.
So we move using:
    curr = curr->prev;

3. Why does this reach the new head?
Initially: head’s prev = NULL
After swapping: head’s next = NULL
As we keep moving forward (using prev after swap), we eventually reach the original tail.
For the original tail: 
• its next was NULL
• after swap its prev becomes NULL
That means: curr->prev == NULL
→ this node is the new head.
So we stop there and return it.

4. Visual flow
Original: 1 <-> 2 <-> 3 <-> 4
          ^
          curr
After swapping node 1: (next=NULL, prev=2)

Move to curr->prev → node 2
Repeat until reaching node 4.
Node 4 after swap: prev = NULL

This is the new head.

>> Key intuition in one line
| Reversing a DLL is just swapping next and prev at every node; traversal continues using prev because links get flipped.
*/
// Time Complexity : O(n) __ Space Complexity : O(1)
Node* reverseDLL(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;
    Node* curr = head;

    while (curr) {
        // swap the next & prev of curr Node
        Node* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;

        // due to swapping prev & next pointers, the next Node in the linkedlist is now pointed to by prev
        // so do curr->prev to access the next Node whose pointers need to be swapped
        if (curr->prev == NULL) break;
        curr = curr->prev;
    }
    return curr;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    Node* head = createDLL(arr);
    traverseDLL(head);

    head = reverseDLLNaive(head);
    traverseDLL(head);

    return 0;
}