#include <bits/stdc++.h>
using namespace std;

// Deletion in Doubly Linked List
/*
1. Deletion of Head (First Node)
Logic:
• If list is empty → no deletion.
• Store head node in a temporary pointer.
• Move head to next node.
• If new head exists:
    • Set new head’s prev to NULL.
• Otherwise:
    • List becomes empty (tail also becomes NULL).
• Delete the old head node.
Time Complexity: O(1) — direct access to head.

2. Deletion of Tail (Last Node)
Logic:
• If list is empty → no deletion.
• If only one node exists:
    • Delete head and make head and tail NULL.
• Otherwise:
    • Store tail node in a temporary pointer.
    • Move tail to previous node.
    • Set new tail’s next to NULL.
    • Delete old tail node.
Time Complexity: O(1) if tail pointer is maintained, else O(n)

3. Deletion of kth Node
Logic:
• If list is empty → no deletion.
• If k = 1 → delete head.
• Traverse to the kth node.
• If position exceeds list size → no deletion.
• Let:
    • prevNode = kth node’s previous node
    • nextNode = kth node’s next node
• Update:
    • prevNode->next = nextNode
    • If nextNode exists → nextNode->prev = prevNode
• If kth node is tail:
    • Update tail to previous node.
• Delete kth node.
Time Complexity: O(min(k, n))

4. Deletion of Node with Given Value
Logic:
• If list is empty → no deletion.
• Traverse the list to find the node containing given value.
• If node not found → no deletion.
• If node is head → delete head.
• Otherwise:
    • Let:
        • prevNode = node’s previous node
        • nextNode = node’s next node
    • Update:
        • prevNode->next = nextNode
        • If nextNode exists → nextNode->prev = prevNode
• If node is tail:
    • Update tail to previous node.
• Delete the node.
Time Complexity: O(n) — search required.

Core Idea Behind All Deletions
👉 First connect the neighboring nodes with each other, then delete the target node.

Safe order:
1) Update previous node’s next.
2) Update next node’s prev.
3) Delete the current node.
This ensures the list never loses connection in either direction.
*/

class Node {
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
    while(temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << '\n';
}

Node* deleteHead(Node* head) {
    if (head == NULL || head->next == NULL) {
        delete head;
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    head->prev = nullptr;
    temp->next = nullptr;       
    // It's not mandatory to do this because after 'delete temp;', the entire node is removed from memory.
    // Its next pointer will never be used again, so changing it before deletion has no effect.
    delete temp;
    return head;
}

Node* deleteTail(Node* head) {
    if (head == NULL || head->next == NULL) {
        delete head;
        return NULL;
    }
    Node* tail = head;
    while(tail->next) {
        tail = tail->next;
    }
    Node* newTail = tail->prev;
    tail->prev = nullptr;
    newTail->next = nullptr;
    delete tail;

    return head;
}

Node* deleteKthNode(Node* head, int k) {
    if (head == NULL) return NULL;
    if (k == 1)
        return deleteHead(head);
    int cnt = 0;
    Node* curr = head;
    while (curr) {
        cnt++;
        if (cnt == k) {
            Node* pv = curr->prev;
            pv->next = curr->next;
            // Handle Tail deletion
            if (curr->next)
                curr->next->prev = pv;
            delete curr;
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* deleteKthNodeStriver(Node* head, int k) {
    if (head == NULL) return NULL;
    Node* kthNode = head;
    int cnt = 0;
    while (kthNode) {
        cnt++;
        if (cnt == k) break;
        kthNode = kthNode->next;
    }
    // if k is larger than linked list size, i.e. if kthNode == NULL after loop ends, return head without deleting anything
    if (kthNode == NULL)
        return head;

    Node* prevNode = kthNode->prev;
    Node* nextNode = kthNode->next;

    // if both prevNode & nextNode are null, it means that there is only 1 node in linked list and that is the head itself
    if (prevNode == NULL && nextNode == NULL) {
        delete head;
        return NULL;
    }
    // if prevNode is null, it means the kthNode is head, so we call deleteHead function to delete it
    if (prevNode == NULL)
        return deleteHead(head);
    // if nextNode is null, it means the kthNode is tail, so we call deleteTail function to delete it
    if (nextNode == NULL)
        return deleteTail(head);
    // else the kthNode is somewhere is in the middle
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete kthNode;
    return head;
}

Node* deleteNodeByValue(Node* head, int val) {
    if (head == NULL) return NULL;
    if (head->data == val)
        return deleteHead(head);
    
    Node* curr = head->next;
    while (curr) {
        if (curr->data == val) {
            Node* pv = curr->prev;
            pv->next = curr->next;
            // Handle Tail deletion
            if (curr->next)
                curr->next->prev = pv;
            delete curr;
            break;
        }
        curr = curr->next;
    }
    return head;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};

    Node* head = createDLL(arr);
    traverseDLL(head);

    head = deleteHead(head);
    traverseDLL(head);

    head = deleteTail(head);
    traverseDLL(head);

    head = deleteKthNode(head, 4);
    traverseDLL(head);

    head = deleteNodeByValue(head, 3);
    traverseDLL(head);

    return 0;
}