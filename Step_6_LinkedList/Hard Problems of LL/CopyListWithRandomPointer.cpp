/*
Leetcode - 138. Copy List with Random Pointer : Medium

A linked list of length n is given such that each node contains an additional random pointer, 
which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, 
where each new node has its value set to the value of its corresponding original node. 
Both the next and random pointer of the new nodes should point to new nodes in the copied list such 
that the pointers in the original list and copied list represent the same list state. 
None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, 
then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. 
Each node is represented as a pair of [val, random_index] where:
    val: an integer representing Node.val
    random_index: the index of the node (range from 0 to n-1) that the random pointer points to, 
        or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Examples :-

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Constraints :-
• 0 <= n <= 1000
• -10^4 <= Node.val <= 10^4
• Node.random is null or is pointing to some node in the linked list.
*/

#include <bits/stdc++.h>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// Naive-Approach :- Time Complexity : O(n^2) __ Space Complexity : O(n)
/*
>> Intuition
The main idea of this approach is:
• First create a completely separate copy of every node.
• Store all copied nodes in an array so they can be accessed using indices.
• Then recreate the next and random connections for the copied list.
The difficult part of this problem is handling the random pointer because it can point to any node in the list.

This solution handles it by:
• Finding the index of the original node pointed to by random.
• Using the same index in the copied-node array.

So essentially:
    “If original node at index i points randomly to original node at index j, 
    then copied node at index i should point randomly to copied node at index j.”

>> Approach
Step 1: Create copied nodes
- Traverse the original list and create a new node for every original node.
- Store these copied nodes inside a vector:     vector<Node*> arr;
- At this point:
    - Nodes exist,
    - but next and random pointers are not connected yet.

Now, the array contains 'n' new nodes which are copies of the original list nodes, 
but these copied nodes are currently disconnected.
We need to connect their next & random pointers.


Step 2: Connect next & random pointers
- Use index variable (idx) to get the current copy Node using arr[idx]
- Connect the next pointer for copy Nodes: arr[idx]->next = arr[idx+1];  (no need to do anything for last position arr node)
- This recreates the normal linked list structure.
- For each original node, the code finds the index position of the node where the random pointer points (if it is not null).
- Use another traversal pointer variable ('curr') to traverse the list again & find the index position of the random node.
- Suppose the random node is found at position pos.
- Now, we must connect the current clone/copy Node's random pointer with the clone Node at index 'pos'.
    arr[idx]->random = arr[pos];

>> Why It Works
The copied list preserves the same relative structure because:
    - arr[i] corresponds to the copy of the original node at index i.
    - Any random relationship in the original list is recreated using the same indices in the copied list.
Thus:
    - no copied node points to an original node,
    - and the deep copy structure is maintained correctly.

>> Complexity Analysis
Let n be the number of nodes.

-> Time Complexity
First traversal:- Creating copied nodes: O(n)
Second traversal:-  
For every node, the code may again traverse the list to find the random node index:
    while (curr != mover->random)
This can take O(n) for each node.
So overall: O(n^2)

>> Space Complexity
Vector storing copied nodes: O(n)
Additionally, the copied linked list itself also uses O(n) space, 
but that is not counted as extra auxiliary space in most analyses since it is required for the answer.
So auxiliary space: O(n)
*/
Node* copyRandomList1(Node* head) {
    if (!head) return NULL;

    vector<Node*> arr;

    Node* mover = head;
    while (mover) {
        Node* newNode = new Node(mover->val);
        arr.push_back(newNode);
        mover = mover->next;
    }

    mover = head;
    int idx = 0;
    while (mover) {
        if (idx != arr.size()-1) 
            arr[idx]->next = arr[idx+1];

        if (mover->random) {
            int pos = 0;
            Node* curr = head;

            while (curr != mover->random) {
                curr = curr->next;
                pos++;
            }

            arr[idx]->random = arr[pos];
        }
            
        idx++;
        mover = mover->next;
    }

    return arr[0];
}

// same logic as above but this one is more readable as we have defined a function to getPosition which inrease readibility.
// returns the 0-based index of the target node in the linked list (used to get the index position of the random node)
int getPosition(Node* head, Node* target) {
    Node* curr = head;
    int pos = 0;

    while (curr != target) {
        pos++;
        curr = curr->next;
    }

    return pos;
}

Node* copyRandomList1x(Node* head) {
    if (!head) return NULL;

    vector<Node*> arr;
    
    Node* mover = head;
    
    while (mover) {
        Node* newNode = new Node(mover->val);
        arr.push_back(newNode);
        mover = mover->next;
    }
    
    mover = head;
    int idx = 0;
    while (mover) {
        if (idx != arr.size()-1) 
            arr[idx]->next = arr[idx+1];
    
        if (mover->random) {
            int pos = getPosition(head, mover->random);
            arr[idx]->random = arr[pos];
        }
        
        idx++;
        mover = mover->next;
    }

    return arr[0];
}

// Optimized Naive Aproach :- Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
>> Intuition
This approach improves the previous naive solution by removing the extra vector.
Instead of storing copied nodes in an array, we directly create the cloned linked list using a dummy node.
The important observation here is:
    The original list and cloned list maintain the exact same ordering.
So while searching for the target of a random pointer in the original list, 
we can simultaneously move a pointer in the cloned list.
When we reach the original random node, the cloned pointer will automatically be at its corresponding cloned node.

>> Approach
Step 1: Create the cloned linked list
- Use a dummy node to create and link clone Nodes of all the nodes of original list.
- Leave the random pointers null for now as to assign them values we will need creation of all nodes.

Step 2: Assign random pointers
- Now traverse both lists simultaneously: 
    - mover = head : original list current node pointer
    - temp = dummy->next : clone list current node pointer
- For every original node:
    - search for that target node inside the original list (if its random pointer exists).
  During this search:
    - t1 traverses the original list,
    - t2 traverses the cloned list at the same speed.
    Since both lists have identical structure and ordering, when t1 reaches the original random node, 
    t2 automatically reaches the cloned random node.
    
    So, the random pointer of current clone node must point to t2, i.e, temp->random = t2;

>> Why This Works
The solution relies on positional correspondence between the two lists.
If we place two pointers at the heads of original list and copy list, and move them together, 
then when 1st pointer reaches original random node, 2nd pointer also reaches copy random node.

>> Improvement Over Previous Solution
Previous approach:
- stored cloned nodes in a vector,
- used indices for mapping.
This approach:
- removes the vector entirely,
- uses synchronized traversal instead.

>> Complexity Analysis :-
Let n be the number of nodes.
-> Time Complexity
Creating cloned list: O(n)
Setting random pointers:
    For every node, we may scan the list again:
    Worst case: O(n), the random node might be at the last of the linked list, so O(n) per node.
    So total: O(n^2)

-> Space Complexity
No vector or hashmap is used. Only a few pointers are maintained.
So auxiliary space: O(1)
(The cloned list itself is not counted as extra space since it is required output.)
*/
Node* copyRandomList(Node* head) {
    if (!head) return NULL;

    Node* dummy = new Node(-1);
    Node* temp = dummy;
    Node* mover = head;
    
    while (mover) {
        Node* newNode = new Node(mover->val);
        temp->next = newNode;
        temp = temp->next;
        mover = mover->next;
    }
    
    mover = head;
    temp = dummy->next;
    
    while (mover) {
        if (mover->random) {
            Node* t1 = head;
            Node* t2 = dummy->next;

            while (t1 != mover->random) {
                t1 = t1->next;
                t2 = t2->next;
            }

            temp->random = t2;
        }

        mover = mover->next;
        temp = temp->next;
    }
    
    return dummy->next;
}

// Better Approach (HashMap) :- Time Complexity : O(n) + O(n*logn) __ Space Complexity : O(n)
/*
>> Intuition
The main difficulty in this problem is: For a clone Node, how to find its random clone Node. 
For a clone Node, we can get its corresponding original node by using simultaneous tarversal, 
and we can thus obtain the original random node, but we don't know how to quickly find the cloned random Node.

This solution solves that efficiently using a map: map<Node*, Node*> mpp;
The map maps original node to its respective cloned node, i.e. : original node  ->  cloned node
Once this mapping is available, assigning random pointers becomes very easy,
as we can get the cloned random node easily using the original random node. 
This removes the repeated traversal present in the naive approaches.

>> Approach
Step 1: Create cloned nodes and store mapping
- Traverse the original list and create a clone for every node. : Node* clone = new Node(curr->val);
- Store the mapping: mpp[curr] = clone;
- At the same time, connect the cloned nodes using next.
- So after this traversal: cloned list is formed, & every original node knows its corresponding clone through the map.

Step 2: Assign random pointers
- Traverse the original list again.
- For every node: curr->random
  we can directly obtain: 
    - clone of current node: mpp[curr]
    - clone of random node: mpp[curr->random]
  Thus, mpp[curr]->random = mpp[curr->random];
  This correctly recreates the random relationship in the cloned list.

>> Why This Works
The map guarantees a one-to-one correspondence: original node  ->  cloned node
So if: original A.random -> original B
then: clone(A).random -> clone(B), is achieved directly using the hashmap.
No searching is needed.

>> Complexity Analysis
Let n be the number of nodes.
-> Time Complexity
First traversal: Creating nodes + storing mapping: O(n)
Second traversal: Assigning random pointers: O(n)
Each map access in std::map costs: O(logn)
So total complexity becomes: O(nlogn)

-> Space Complexity
The map stores one entry per node: O(n)
Auxiliary space: O(n)
*/
Node* copyRandomList(Node* head) {
    map<Node*, Node*> mpp;

    Node* curr = head;
    Node* dummy = new Node(-1);
    Node* temp = dummy;
    
    while (curr) {
        Node* clone = new Node (curr->val);
        temp->next = clone;
        mpp[curr] = clone;
        temp = temp->next;
        curr = curr->next;
    }
    
    curr = head;
    
    while (curr) {
        if (curr->random) {
            mpp[curr]->random = mpp[curr->random];
        }
        curr = curr->next;
    }
    
    return mpp[head];
}

// Striver's Implementation of the HashMap Approach (we can assign random and next pointers in the same traversal). 
Node* copyRandomList(Node* head) {
    map<Node*, Node*> mpp;
    Node* temp = head;
    
    while (temp) {
        Node* clone = new Node (temp->val);
        mpp[temp] = clone;
        temp = temp->next;
    }

    temp = head;
    while (temp) {
        Node* clone = mpp[temp];
        if (temp->next) clone->next = mpp[temp->next];
        if (temp->random) clone->random = mpp[temp->random];
        temp = temp->next;
    }
    
    return mpp[head];
}

// Optimal Approach : 
/*
>> Intuition
The key idea is extremely clever:
    Instead of storing a mapping externally, temporarily store the cloned node directly beside its original node.
So the list transforms like this:
-------------------------------------------
    Original:
    A -> B -> C

    After inserting clones:
    A -> A' -> B -> B' -> C -> C'
-------------------------------------------
Now every original node’s clone is immediately available using: original->next
This automatically creates an implicit mapping: original node -> clone node, without using extra space.

>> Approach 
Step 1: Insert clone nodes in between
- For every original node: A -> B
- insert its clone between them: A -> A' -> B
We are using the helper function insertClonesInBetween to achieve this task.

Why This Helps ?
Now: clone of any node X is simply: X->next
This is the core trick of the solution.

Step 2: Connect random pointers
- Suppose A.random -> C
- We need to connect A'.random -> C' , where A' and C' are respective clone nodes of A & C
- We can get the clone node of a node x using x.next

- temp denotes the current original Node.
- clone of current node :- clone = temp->next
- now, clone's random must point to the corresponding clone node of temp's random (which is temp.random.next).
- So, clone->random = temp->random->next

We are using the helper function connectRandomLinks to achieve this task.

Step 3: Separate the cloned list
- Currently the list looks like: A -> A' -> B -> B' -> C -> C'
- Now:
    - extract all clone nodes into a separate list,
    - restore the original list back to normal.
    -i.e, we must do :-
        Original: A -> B -> C
        Clone:    A' -> B' -> C' 
- We can use dummy node chain to create the list of clone nodes and separate them from original list.
- We need to change next pointers of original nodes, so original nodes points to original next nodes instead of clone nodes.
- Return the head of the clone list.

We are using the helper function getDeepCopyList to achieve this task.

>> Why This Works ?
The solution works because cloned nodes are placed immediately after their originals.
This guarantees: original->next = clone, throughout the process.
So:  
    corresponding clone nodes become directly accessible, 
    random links can be assigned in constant time.
The interleaving structure temporarily replaces the need for a hashmap.

>> Complexity Analysis
Let n be the number of nodes.
-> Time Complexity
    - Insert clone nodes: O(n)
    - Connect random pointers: O(n)
    - Separate cloned list: O(n)
    Total: O(n) + O(n) + O(n) O(3n)

-> Space Complexity
No hashmap, vector, or extra data structure is used. Only a few pointers are maintained.
Auxiliary space: O(1)
(The cloned list itself is required output, so it is not counted.)

|| Core Insight of the Optimal Solution
The brilliant observation is:
    Instead of storing mapping externally, embed the mapping inside the linked list itself.
By interleaving original and cloned nodes: original -> clone 
becomes instantly accessible in constant time, enabling both:
    - efficient random-pointer assignment,
    - and O(1) extra space.
*/
void insertClonesInBetween(Node* head) {
    Node* temp = head;

    while (temp) {
        Node* clone = new Node(temp->val);
        clone->next = temp->next;
        temp->next = clone;

        temp = temp->next->next;        // or, temp = clone->next
    }
}

void connectRandomLinks(Node* head) {
    Node* temp = head;

    while (temp) {
        if (temp->random) {
            Node* clone = temp->next;
            clone->random = temp->random->next;
        }
        temp = temp->next->next;
    }
}

Node* getDeepCopyList(Node* head) {
    Node* dummy = new Node(-1);
    Node* curr = dummy;
    Node* temp = head;

    while (temp) {
        // creating new list (adding clone Nodes to this clone list)
        curr->next = temp->next;
        curr = curr->next;

        // disconnecting and going back to the initial state of the original linked list
        temp->next = temp->next->next;
        temp = temp->next;
    }
    return dummy->next;
}

Node* copyRandomList(Node* head) {
    if (!head) return head;

    // Insert copy nodes (or clone nodes) in between the Nodes of original list
    insertClonesInBetween(head);
    // connect random pointer links of the clone nodes
    connectRandomLinks(head);
    
    // link clone nodes to each other and revert the original list to its original state and return the cloneHead
    return getDeepCopyList(head);
}

int main() {
    return 0;
}