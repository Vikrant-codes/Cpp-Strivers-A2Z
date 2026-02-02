#include <bits/stdc++.h>
using namespace std;

/*
Pre-requisites for LinkedList Implementation :-
- Pointers
- Dynamic Memory Allocation
- struct / class
*/

class Node {
public:
    int data;
    Node* next;

    // Constructor
    Node(int data) {
        this->data = data;
        next = nullptr;
    }
};

int main() {
    Node* nd = new Node(1);
    cout << nd << '\n';
    cout << nd->data << " : " << nd->next << '\n';  
    // To access members via pointers, we need to use arrow operator (->) instead of dot operator (.)
    
    int arr[] = {1, 2, 3, 4, 5};

    Node* head = new Node(arr[0]);
    Node* last = head;

    for (int i = 1; i < 5; i++) {
        Node* temp = new Node(arr[i]);
        last->next = temp;
        last = temp; 
    }

    // Traversal of Linked List
    Node* curr = head;
    while(true) {
        cout << curr->data << " -> ";

        if (curr->next == nullptr) break;
        
        curr = curr->next;
    }
    

    return 0;
}