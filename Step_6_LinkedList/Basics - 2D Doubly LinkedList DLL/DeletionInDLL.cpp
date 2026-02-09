#include <bits/stdc++.h>
using namespace std;

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
    if(arr.empty()) return NULL;
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
    if (k == 1) {
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        temp->next = nullptr;
        delete temp;
        return head;
    }
    int cnt = 0;
    Node* curr = head;
    while (curr) {
        cnt++;
        if (cnt == k) {
            Node* pv = curr->prev;
            pv->next = curr->next;
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

    head = deleteKthNode(head, 5);
    traverseDLL(head);

    return 0;
}