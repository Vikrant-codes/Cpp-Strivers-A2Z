#include <bits/stdc++.h>
using namespace std;

/*
Pre-requisites for LinkedList Implementation :-
- Pointers
- Dynamic Memory Allocation
- struct / class
*/

/*
### Singly Linked List (SLL)
A singly linked list is a linear data structure made up of nodes where each node stores:
1. Data
2. Pointer to the next node
The nodes are connected sequentially using pointers, forming a chain.

1. Node Structure
Each node contains two parts: [ data | next ]
• data → value stored in the node
• next → address of the next node in the list

2. Basic Organization
- The first node is called the head.
- The last node is called the tail.
    tail->next = nullptr
Example:
    [10] → [20] → [30] → [40] → NULL
- The list starts from the head and ends where the next pointer becomes nullptr.

3. Traversal
- Traversal always starts from the head and proceeds using the next pointer:
    head → head->next → head->next->next ...
- Traversal stops when a node’s next becomes nullptr.

4. Linking Principle
- For two consecutive nodes:
    A->next = B
- Each node stores only the address of the next node, maintaining a one-directional chain.

5. Memory Representation
- Nodes are dynamically allocated in memory.
- Nodes are not stored in contiguous locations.
- Connections between nodes are maintained using pointers instead of indices.

6. Basic Operations Supported
A singly linked list supports:
• Insertion (beginning, end, or middle)
• Deletion of nodes
• Traversal
• Searching
All operations involve updating the next pointer appropriately.

>> What is a 1D Linked List?
A 1D (singly) linked list is a linear data structure where:
• Each element is called a node
• Each node contains:
    - Data
    - Address (pointer) to the next node
• Nodes are not stored contiguously in memory
Node structure :- [data | next]
Example :- 10 → 20 → 30 → 40 → NULL

>> How is LL different from an array?
| Array                | Linked List             |
| -------------------- | ----------------------- |
| Contiguous memory    | Non-contiguous memory   |
| Fixed size           | Dynamic size            |
| Direct access (O(1)) | Sequential access       |
| Insert/delete costly | Insert/delete efficient |

>> Why is a Linked List used?
Main reasons :-
- Dynamic size: No need to know size in advance
- Efficient insertion/deletion: No shifting of elements like arrays
- Memory utilization: Uses memory as needed (no pre-allocation)

>> Practical / Real-world Uses
- Implementing stacks & queues
- Undo/Redo operations
- Music playlist (next song pointer)
- Browser history
- Adjacency list in graphs
- Dynamic memory management
*/

// Basic Linked List Implementation
class Node {
public:
    int data;
    Node* next;

    // Constructor
    Node(int data) {
        this->data = data;
        next = nullptr;         // next = NULL; or next = 0; is also valid
    }
};

// function that creates a linked list from an array
Node* arr2LL(vector<int> arr) {
    if (arr.empty()) return NULL;
    
    Node* head = new Node(arr[0]);
    Node* curr = head;

    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;           // curr = curr->next;
    }

    return head;
}

// Traversal of Linked List (Traversal = visiting each node once)
// Time Complexity : O(n)
void traverseLL(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " -> ";       
        curr = curr->next;
    }
    cout << '\n';
}

// Size/Length of Linked List
/*
Logic
- Initialize counter = 0
- Traverse the Linked List and increment the counter

Time Complexity : O(n)
*/
int sizeOfLL(Node* head) {
    int size = 0;
    Node* curr = head;
    while (curr) {
        curr = curr->next;
        size++;
    }
    return size;
}

// Search an Element in Linked List
/*
Logic
- Traverse the Linked List
- Compare each node’s data

Time Complexity:- 
- Worst Case (element not present / element is in the tail of LL): O(n)
- Best Case (element is present at head Node): O(1)
- Average Case (element is present in somewhere in the middle): O(n/2) 
*/
bool searchInLL(Node* head, int key) {
    Node* curr = head;
    // while(curr != NULL) or we can simply use while(curr)
    while (curr) {
        if (curr->data == key)
            return true;
        curr = curr->next;
    }
    return false;
}

/*
>> Visual Summary

|   head
|    ↓
|   [10|*] → [20|*] → [30|*] → [40|NULL]

• head stores address of first node
• Each node knows only about the next node
*/

int main() {
    Node* nd = new Node(1);
    cout << nd << '\n';
    cout << nd->data << " : " << nd->next << '\n';  
    // To access members via pointers, we need to use arrow operator (->) instead of dot operator (.)
    
    vector<int> arr = {1, 2, 3, 4, 5};
    Node* head = arr2LL(arr);
    traverseLL(head);
    cout << "size of linked list : " << sizeOfLL(head) << '\n';

    cout << "Searching an Element in Linked List ->\n";
    int x;
    cout << "Enter the element you want to search in the Linked List : ";
    cin >> x;
    if(searchInLL(head, x))
        cout << "The element exists !!\n";
    else
        cout << "The element does not exist !!\n";

    return 0;
}