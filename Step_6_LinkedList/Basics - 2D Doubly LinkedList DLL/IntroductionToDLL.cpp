#include <bits/stdc++.h>
using namespace std;

/*
### Doubly Linked List (DLL)
A doubly linked list is a linear data structure made up of nodes where each node stores:
1. Data
2. Pointer to the previous node
3. Pointer to the next node
These nodes are connected in sequence, forming a chain where traversal is possible in both directions.

1. Node Structure
Each node contains three parts: [ prev | data | next ]
• prev → address of the previous node
• data → value stored in the node
• next → address of the next node

2. Basic Organization
- The first node is called the head.
    head->prev = nullptr
- The last node is called the tail.
    tail->next = nullptr
- Example:
    NULL ← [10] ⇄ [20] ⇄ [30] ⇄ [40] → NULL
- Each node is linked with its neighbors in both directions.

3. Traversal
- Traversal can be done in two ways:
(a) Forward Traversal
    Start from head and move using next pointers.
    head → head->next → head->next->next ...
(b) Backward Traversal
    Start from tail and move using prev pointers.
    tail → tail->prev → tail->prev->prev ...

4. Linking Principle
- Every connection between two adjacent nodes must satisfy:
    A->next = B
    B->prev = A
- Both links must always be maintained to keep the list valid.

5. Memory Representation
- Nodes are stored dynamically in memory.
- They are not necessarily contiguous.
- Connections are maintained using pointers rather than indices.

6. Basic Operations Supported
A doubly linked list supports:
• Insertion (beginning, end, or middle)
• Deletion of any node
• Forward and backward traversal
• Searching
All operations involve updating both prev and next pointers correctly.
*/

class Node {
public:
    Node* prev;
    int data;
    Node* next;

    Node(int val) : Node(nullptr, val, nullptr) {}

    Node(Node* p, int val, Node* n) {
        prev = p;
        data = val;
        next = n;
    }
};

Node* arr2DLL(vector<int>& arr) {
    if (arr.empty()) return NULL;
    Node* head = new Node(arr[0]);
    Node* temp = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* newNode = new Node(arr[i]);
        temp->next = newNode;
        newNode->prev = temp;
        temp = newNode;
        // we could have also used below code
        /*
        Node* newNode = new Node(temp, arr[i], NULL);
        temp->next = newNode;
        temp = newNode;
        */
    }
    return head;
}

void traverseDLL(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << '\n';
}

int sizeOfDLL(Node* head) {
    Node* curr = head;
    int size = 0;
    while (curr) {
        size++;
        curr = curr->next;
    }
    return size;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    Node* head = arr2DLL(arr);
    traverseDLL(head);
    cout << "Size of the Doubly Linked List : " << sizeOfDLL(head);

    return 0;
}