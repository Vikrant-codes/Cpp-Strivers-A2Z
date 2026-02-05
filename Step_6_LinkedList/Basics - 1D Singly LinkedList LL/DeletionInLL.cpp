#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

Node* createLinkedList(vector<int>& arr) {
    Node* head = new Node(arr[0]);
    Node* curr = head;

    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;
    }

    return head;
}

void traverseLinkedList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << '\n';
}

Node* deleteHead(Node* head) {
    // if Linked List is empty ... return NULL as it have nothing to delete
    if (head == NULL) 
        return head;

    Node* temp = head;
    head = head->next;

    delete temp;        // remove the previous head from memory 

    return head;
}

Node* deleteTail(Node* head) {
    // if the Linked List have less than 2 elements (either 0 or 1), then after deleting the tail, it would become empty
    // so return NULL
    if (head == NULL || head->next == NULL)
        return NULL;

    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->next == nullptr) 
            prev->next = nullptr;
        prev = prev->next;          // prev = curr will also be the same thing      
        curr = curr->next;
    }
    return head;
}

Node* deleteByValue(Node* head, int value) {
    // if it is the first Node (head node) itself
    if (head->data == value) 
        return head->next;
    
    // else implement logic accordingly
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->data == value) {
            // remove the link of current node from previous node
            prev->next = curr->next;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}

Node* deleteByPosition(Node* head, int pos) {
    // if it is the first Node (head node) itself
    if (pos == 1) 
        return head->next;
    
    int i = 2;
    
    // else implement logic accordingly
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (i == pos) {
            // remove the link of current node from previous node
            prev->next = curr->next;
            break;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return head;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    
    Node* head = createLinkedList(arr);
    traverseLinkedList(head);

    // delete the head Node from Linked List
    head = deleteHead(head);
    traverseLinkedList(head);

    // delete the tail Node of Linked List
    head = deleteTail(head);
    traverseLinkedList(head);

    // delete by value
    head = deleteByValue(head, 5);
    traverseLinkedList(head);

    // delete by position
    head = deleteByPosition(head, 3);
    traverseLinkedList(head);

    return 0;
}