#include <bits/stdc++.h>
using namespace std;

// Insertion in Doubly Linked List
/*
1. Insertion Before Head (Beginning)
Logic:
• Create a new node.
• Store data in the new node.
• If list is empty:
    • New node becomes head (and tail).
• Otherwise:
    • Make new node’s next point to current head.
    • Make current head’s prev point to new node.
    • Move head to the new node.
• New node becomes the first node.
Time Complexity: O(1) — direct access to head.

2. Insertion After Head
Logic:
• Create a new node.
• If list is empty → no insertion.
• Make new node’s next point to head’s next.
• Make new node’s prev point to head.
• If head’s next exists:
    • Update its prev to new node.
• Otherwise:
    • New node becomes the tail.
• Link head’s next to new node.
Time Complexity: O(1) — no traversal needed.

3. Insertion Before Tail
Logic:
• Create a new node.
• If list is empty → no insertion.
• If only one node exists:
    • Same as insertion before head.
• Otherwise:
    • Make new node’s prev point to tail’s previous node.
    • Make new node’s next point to tail.
    • Update previous node’s next to new node.
    • Update tail’s prev to new node.
Time Complexity: O(1) if tail pointer is maintained, else O(n)

4. Insertion After Tail (End)
Logic:
• Create a new node.
• If list is empty:
• New node becomes head and tail.
• Otherwise:
• Make new node’s prev point to current tail.
• Make tail’s next point to new node.
• Update tail to new node.
• New node’s next becomes NULL.
Time Complexity: O(1) if tail pointer exists, else O(n)

5. Insertion at Position (kth Node)
Logic:
• Create a new node.
• If list is empty and k ≠ 1 → no insertion.
• If k = 1 → insertion before head.
• Traverse till (k−1)th node.
• If position exceeds list size → no insertion.
• Make new node’s:
    • next → kth node
    • prev → (k−1)th node
• Update (k−1)th node’s next to new node.
• Update kth node’s prev to new node.
Time Complexity: O(min(k, n))

6. Insertion Before a Given Node / Data
Logic:
• Create a new node.
• If list is empty → no insertion.
• If target node is head → insertion before head.
• Traverse to find the target node.
• If target not found → no insertion.
• Make new node’s:
    • next → target node
    • prev → target node’s previous node
• Update previous node’s next to new node.
• Update target node’s prev to new node.
Time Complexity: O(n) — search required.

7. Insertion After a Given Node / Data
Logic:
• Create a new node.
• Traverse to find target node.
• If target not found → no insertion.
• Make new node’s:
    • prev → target node
    • next → target node’s next
• If target’s next exists:
    • Update its prev to new node.
• Otherwise:
    • New node becomes new tail.
• Update target node’s next to new node.
Time Complexity: O(n)

Core Idea Behind All Insertions
👉 In doubly linked list, update new node’s links first, then adjust surrounding nodes.

Typical safe order:
1) Connect new node with neighbors (prev and next).
2) Update previous node’s next.
3) Update next node’s prev.
This prevents breaking the chain in either direction.
*/

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
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << '\n';
}

Node* insertBeforeHead(Node* head, int val) {
    if (head == NULL)
        return new Node(val);
    Node* newHead = new Node(nullptr, val, head);       // newHead's next will point to head
    head->prev = newHead;                               // link the head's prev to newHead
    return newHead;
}

Node* insertAfterHead(Node* head, int val) {
    if (head == NULL)
        return new Node(val);
    Node* temp = new Node(head, val, head->next);     // the newNode's prev will be head and next will be head->next
    head->next = temp;                                // Attach new node after head 
    if (temp->next)                                   // Fix backward link of the next node (if it exists)
        temp->next->prev = temp;
    return head;
}

Node* insertBeforeTail(Node* head, int val) {
    if (head == NULL || head->next == NULL)
        return insertBeforeHead(head, val);
    Node* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    // insert a new node between tail & tail's prev
    Node* prevNode = tail->prev;
    Node* newNode = new Node(prevNode, val, tail);  // newNode's prev would be tail's prev and its next is tail
    prevNode->next = newNode;
    tail->prev = newNode;
    return head;
}

Node* insertAfterTail(Node* head, int val) {
    if (head == NULL)
        return new Node(val);
    Node* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    Node* newTail = new Node(tail, val, nullptr);
    tail->next = newTail;
    return head;
}

Node* insertBeforeKthNode(Node* head, int val, int k) {
    if (head == NULL)
        return head;
    if (k == 1)
        return insertBeforeHead(head, val);
    int cnt = 1;
    Node* curr = head->next;
    while (curr) {
        cnt++;
        if (cnt == k) {
            Node* prevNode = curr->prev;
            Node* newNode = new Node(prevNode, val, curr);
            curr->prev = newNode;
            prevNode->next = newNode;
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* insertAfterKthNode(Node* head, int val, int k) {
    if (head == NULL)
        return head;
    int cnt = 0;
    Node* curr = head;
    while (curr) {
        cnt++;
        if (cnt == k) {
            Node* nextNode = curr->next;
            Node* newNode = new Node(curr, val, nextNode);
            curr->next = newNode;
            if (nextNode)
                nextNode->prev = newNode;
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* insertBeforeValueX(Node* head, int val, int x) {
    if (head == NULL)
        return head;
    if (head->data == x)
        return insertBeforeHead(head, val);
    Node* curr = head->next;
    while (curr) {
        if (curr->data == x) {
            Node* prevNode = curr->prev;
            Node* newNode = new Node(prevNode, val, curr);
            curr->prev = newNode;
            prevNode->next = newNode;
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* insertAfterValueX(Node* head, int val, int x) {
    if (head == NULL)
        return head;
    Node* curr = head;
    while (curr) {
        if (curr->data == x) {
            Node* nextNode = curr->next;
            Node* newNode = new Node(curr, val, nextNode);
            curr->next = newNode;
            if (nextNode)
                nextNode->prev = newNode;
            break;
        }
        curr = curr->next;
    }
    return head;
}

int main() {
    vector<int> arr = {3};
    Node* head = createDLL(arr);
    traverseDLL(head);

    head = insertBeforeHead(head, 1);
    traverseDLL(head);

    head = insertAfterHead(head, 2);
    traverseDLL(head);

    head = insertBeforeTail(head, 4);
    traverseDLL(head);
    
    head = insertAfterTail(head, 5);
    traverseDLL(head);

    head = insertBeforeKthNode(head, 7, 4);
    traverseDLL(head);

    head = insertAfterKthNode(head, 6, 3);
    traverseDLL(head);

    head = insertBeforeValueX(head, 8, 6);
    traverseDLL(head);

    head = insertAfterValueX(head, 9, 7);
    traverseDLL(head);

    return 0;
}