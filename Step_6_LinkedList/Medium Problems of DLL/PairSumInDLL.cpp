/*
GFG - Pair Sum in Doubly Linked List : Easy

Given a sorted doubly linked list of positive distinct elements, 
the task is to find pairs in a doubly-linked list whose sum is equal to given value target.

Examples :-

Input: 1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9, target = 7
Output: (1, 6), (2,5)
Explanation: We can see that there are two pairs (1, 6) and (2,5) with sum 7.

Input: 1 <-> 5 <-> 6, target = 6
Output: (1,5)
Explanation: We can see that there is one pair (1, 5) with sum 6.

Constraints :-
- 1 <= N <= 10^5
- 1 <= target <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

/* Doubly linked list node class
class Node
{
public:
    int data;
    Node *next, *prev;
    Node(int val) : data(val), next(NULL), prev(NULL)
    {
    }
};
*/
class Node {
public:
    int data;
    Node *next, *prev;
    Node(int val) : data(val), next(NULL), prev(NULL){}
};

// Naive Approach (Check sum of all pairs of nodes) : Time Complexity : O(n^2) __ Space Complexity : O(1)
vector<pair<int, int>> findPairsWithGivenSumNaive(Node *head, int target) {
    vector<pair<int, int>> ans;
    
    Node* curr = head;
    while (curr) {
        int a = curr->data;
        
        Node* temp = curr->next;
        
        while (temp) {
            int b = temp->data;
            if (a + b == target) {          // if this node & curr node data add up to target
                ans.push_back({a, b});      // push the pair to answer
                break;                      // break since elements are distinct so no more pair exists for current node
            }
            else if (a + b > target) 
                break; 
                // since dll is sorted, moving temp ahead will only increase the sum further, so break out of loop in that case
            
            temp = temp->next;
        }
        
        curr = curr->next;
    }
    
    return ans;
}

// Better Approach (Using HashSet) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach:-
1. Traverse the linked list from head to end.
2. For each node, consider its value as a.
3. Compute the value required to form the target sum: b = target - a.
4. Check if b has already appeared earlier in the list using a hash set.
5. If b exists in the set, it means a previous node together with the current node forms the required sum.
6. Add the pair {b, a} to the answer vector.
7. Insert the current value a into the set so future nodes can form pairs with it.
8. Continue this process until the list traversal is complete.
*/
vector<pair<int, int>> findPairsWithGivenSumBetter(Node *head, int target) {
    vector<pair<int, int>> ans;
    unordered_set<int> s;
    
    Node* curr = head;
    while (curr) {
        int a = curr->data;
        int b = target - a;     // calculate the remaining sum for pair node
        
        if (s.count(b))         // if node with remaining sum exists
            ans.push_back({b, a});
            
        s.insert(a);            // add the current nodes' data to the set
        
        curr = curr->next;
    }
    
    return ans;
}

// Optimal Approach (2 Pointers) : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
Approach :-
Since the doubly linked-list is sorted, we can use 2 pointers to find pairs which sum up to target.

Stepwise Approach:
1. Place one pointer i at the head of the doubly linked list.
2. Traverse the list once to place another pointer j at the tail.
3. Now treat i and j as the two ends of the list.
4. Calculate the sum of the values at i and j.
5. If the sum equals the target, store the pair {i->data, j->data} in the answer.
6. After finding a pair, move both pointers inward (i = i->next, j = j->prev).
7. If the sum is less than the target, move i forward to increase the sum.
8. If the sum is greater than the target, move j backward to decrease the sum.
9. Continue this process while the pointers have not met or crossed.
10. Return the list of all valid pairs.

Time Complexity : 
- O(n) : to reach the tail node for the right pointer
- O(n) : to traverse the two pointers
*/
vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target) {
    vector<pair<int, int>> ans;
    
    Node* i = head;     // pointer-1, at head
    Node* j = head;     // pointer-2, should point to tail
    // move pointer 'j' to tail node
    while (j->next)
        j = j->next;
    
    while (i && j && i != j && j->next != i) {
        int a = i->data;
        int b = j->data;
        
        if (a + b == target) {
            ans.push_back({a, b});
            i = i->next;
            j = j->prev;
        }
        else if (a + b < target) i = i->next;
        else j = j->prev;
    }
    
    return ans;
}

// Striver's implementation
vector<pair<int, int>> findPairsWithGivenSumStriver(Node *head, int target) {
    vector<pair<int, int>> ans;
    
    Node* left = head;     // left pointer, at head
    Node* right = head;     // right pointer should point to tail
    // move right pointer to tail node
    while (right->next)
        right = right->next;
    
    while (left->data < right->data) {
        int a = left->data;
        int b = right->data;
        
        if (a + b == target) {
            ans.push_back({a, b});
            left = left->next;
            right = right->prev;
        }
        else if (a + b < target) left = left->next;
        else right = right->prev;
    }
    
    return ans;
}

int main() {
    return 0;
}