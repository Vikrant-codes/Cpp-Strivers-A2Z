/*
Leetcode - 23. Merge k Sorted Lists : Hard

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Examples :-

Input: lists = [[1,4,5],[1,3,4],[2,6]] __ Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6

Input: lists = [] __ Output: []

Input: lists = [[]] __ Output: []

Constraints :-
• k == lists.length
• 0 <= k <= 10^4
• 0 <= lists[i].length <= 500
• -10^4 <= lists[i][j] <= 10^4
• lists[i] is sorted in ascending order.
• The sum of lists[i].length will not exceed 10^4.
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Naive Approach : Time Complexity : O(N log N) __ Space Complexity : O(N)
/*
>> Intuition
Each linked list is already sorted, but handling multiple linked lists together directly can feel complicated.
A simpler observation is:
If we collect all node values into one container, then after sorting those values, 
we can rebuild the final sorted linked list easily.
So instead of merging lists one by one, this approach treats the problem like:
- Extract all elements
- Sort them
- Build a new sorted linked list

>> Step-by-step Idea
1. Store all node values in an array
- Traverse every linked list and push each node’s value into a vector.
        for (ListNode* curr : lists)
    Here, curr points to the head of one linked list.
- Then:
        while (temp)
    visits every node of that list and stores its value.
    After this step: lists = [1->4->5, 1->3->4, 2->6], arr = [1,4,5,1,3,4,2,6]

2. Sort the array
- Now all values are present in a single array.
    sort(arr.begin(), arr.end());
- After sorting: arr = [1,1,2,3,4,4,5,6]
- At this point, the linked-list structure no longer matters because the ordering is already correct.

3. Create the final linked list
- Use the sorted array to build a brand-new linked list.
- A dummy node is used to simplify insertion.
    ListNode* dummy = new ListNode(-1);
- Then for every value:
        t->next = new ListNode(x);
    attach a new node and move forward.
- Finally:
        return dummy->next;
    because dummy itself is just a helper node.

>> Complexity Analysis
Let: N = total number of nodes across all linked lists
-> Time Complexity
    Traversing all lists: O(N)
    Sorting array: O(N log N)
    Building final list: O(N)
Overall: O(N log N)

-> Space Complexity
    Array stores all node values → O(N)
    New linked list nodes → O(N)
Extra auxiliary space: O(N)
*/
ListNode* mergeKListsNaive(vector<ListNode*>& lists) {
    vector<int> arr;

    // Step-1 : store the linked list data elements in an array
    for (ListNode* curr : lists) {
        ListNode* temp = curr;
        while (temp) {
            arr.push_back(temp->val);
            temp = temp->next;
        }
    }

    // Step-2 : sort the array
    sort(arr.begin(), arr.end());
    
    // Step-3 : Create a new linked list with the sorted data and return its head
    ListNode* dummy = new ListNode(-1);
    ListNode* t = dummy;
    for (int x : arr) {
        ListNode* newNode = new ListNode(x);
        t->next = newNode;
        t = t->next;
    }

    return dummy->next;
}

// Merge 2 lists Approach : Time Complexity : O(N * k) __ Space Complexity : O(1)
/*
>> Intuition
We already know how to merge 2 sorted linked lists efficiently using the classic two-pointer technique.
Now the problem gives us k sorted linked lists.
A straightforward idea is:
- Start with an empty merged list.
- Take each list one by one.
- Merge the current answer with the next list.
In this way, all list keep geeting merged to a final merged list one by one.

The key observation is that at every step: 
- both lists being merged are already sorted, 
- therefore the standard merge procedure works correctly.

>> Approach
We create a helper function merge(head1, head2):
• Use two pointers:
    • t1 for first list
    • t2 for second list
• Compare node values and attach the smaller node to the result.
• Move forward in the corresponding list.
• After one list finishes, append the remaining nodes of the other list.

Then in mergeKLists:
• Maintain a pointer head representing the merged result so far.
• Iterate through every linked list in lists.
• Continuously merge:
    head = merge(head, curr);

At the end, head contains the fully merged sorted linked list.

>> Complexity Analysis
Let:
k = number of linked lists
N = total number of nodes across all lists
n = average no. of nodes in a list

-> Time Complexity
Complexity of merge() : Each merge operation traverses all nodes present in the two lists being merged.
Merging two sorted linked lists having m and n nodes takes: O(m+n), because each node is visited exactly once.

Complexity of mergeKLists()
Suppose the k linked lists contain: n1, n2, n3, ..., nk nodes respectively.
We merge lists one-by-one into the cumulative answer list.

--> Merge Operations
Initially: ans is empty => size of ans = 0

- First Merge : merge(ans, list1) => Time: O(0+n1) = O(n1)
    Now ans contains n₁ nodes.
- Second Merge : merge(ans, list2) => Time: O(n1+n2) = O(n1 + n2)
    Now contains n₁ + n₂ nodes.
- Third Merge : merge(ans, list3) => Time: O((n1+n2) + n3) = O(n1 + n2 + n3)
    Now contains n1​+n2​+n3 nodes.
- k-th Merge : merge(ans, listk) => Time: O(n1 ​+ n2 ​+ n3​ + ⋯ + nk​) 

Total Time Complexity
Therefore total complexity becomes: O(n1) + O(n1 + n2) + O(n1 + n2 + n3) + ... + O(n1 + n2 + n3 + ... + nk)

Assuming all lists contains same no. of nodes, i.e., n1 = n2 = n3 = ... = nk = 'n'
Time for each merge becomes:
1st merge → O(n)
2nd merge → O(2n)
3rd merge → O(3n)
...
k-th merge → O(kn)

Thus, total time complexity :-
    = O(n) + O(2*n) + O(3*n) + ... + O(k*n)
    = O(n + 2*n + 3*n + ... + k*n) 
    = O( n * (1 + 2 + 3 + ... + k) ) 
    = O( n * (k * (k + 1) / 2) )
Ignoring Constants :- O(n* k^2) = O(n * k * k)
Expressing Complexity Using Total Nodes N -- Since total nodes : N = n*k
Substituting: O(n * k^2) = O(N * k)
So the final complexity is: O(N * k) or O(n * k * k)
where:
    - k = number of linked lists
    - n = average no. of nodes in each linked list
    - N = total number of nodes across all linked lists = n * k
	​
>> Why This Is Inefficient ? 
After every merge, the answer list becomes larger.
So while merging the next list, we repeatedly traverse nodes that were already processed in previous merges.
This repeated revisiting of nodes leads to the high time complexity.

-> Space Complexity : Only a few pointers are used during merging. -- O(1)
*/
ListNode* merge(ListNode* head1, ListNode* head2) {
    ListNode *t1 = head1, *t2 = head2;
    ListNode* dummy = new ListNode(-1);
    ListNode *temp = dummy;

    while (t1 && t2) {
        if (t1->val <= t2->val) {
            temp->next = t1;
            t1 = t1->next;
        }
        else {
            temp->next = t2;
            t2 = t2->next;
        }
        temp = temp->next;
    } 
    if (t1) temp->next = t1;
    if (t2) temp->next = t2;

    return dummy->next;
}

ListNode* mergeKListsX(vector<ListNode*>& lists) {
    ListNode* head = NULL;

    for (ListNode* curr : lists) {
        head = merge(head, curr);
    }
    
    return head;
}

// Optimal Approach : Time Complexity : O(N log k) __ Space Complexity : O(k)
/*
>> Intuition
At any moment, the smallest element among all the linked lists must be one of the current head nodes of those lists.
So instead of repeatedly merging entire lists, we can:
• Keep track of the smallest current node among all lists.
• Pick the minimum node.
• Add it to the answer.
• Move to the next node of that list.
• Repeat until all nodes are processed.
To efficiently get the minimum node every time, we use a Min Heap / Minimum Priority Queue.

### Approach
-> Step 1: Insert Heads of All Lists into Min Heap
• Each linked list is already sorted.
• So initially, the smallest candidate from each list is its head node.
• We insert {node->val, node} into the min heap.
• The heap always keeps the smallest value at the top.

-> Step 2: Extract Minimum Node
• The top of the heap contains the smallest node among all current nodes.
    pair<int, ListNode*> x = pq.top();
    pq.pop();
• Attach this node to the merged linked list.

-> Step 3: Insert Next Node of Removed Node
• Suppose the removed node belonged to some linked list.
• Since that list is sorted, its next node is the next possible candidate from that list.
• So we insert x.second->next into the heap (if it exists).

-> Step 4: Repeat Until Heap Becomes Empty
• Continue removing the smallest node and inserting the next node until all nodes are processed.
• The final linked list becomes completely sorted.

>> Why Min Heap Works ?
The heap always stores at most one active candidate node from each list.
So at every step:
    heap top = globally smallest available node
Thus nodes are added in sorted order.

--------------------------------------------------------------------------------------------------------------------------
It's like how we used two pointers to merge two sorted linked lists, we placed both pointers at the start and then 
picked the smallest node by checking the value at the current pointed nodes and added that node to the chain.
Then, we would move that pointer ahead to consider the next Node from that list. 

In similar way, here we are using a priority queue to get the smallest value Node and 
we don't have to deal with 'k' pointers for 'k' lists. 
Whichever list's current node is smallest, we add its next Node to the priority queue and we always extract the smallest 
available node from the priority queue and add it to the chain
--------------------------------------------------------------------------------------------------------------------------

>> Complexity Analysis
Let:
• k = number of linked lists
• N = total number of nodes across all lists

-> Heap Size:
At most one node from each list exists in the heap at a time.
So heap size never exceeds 'k'

-> Operations Per Node
Every node:
• is inserted into heap once
• is removed from heap once
Heap insertion: O(logk)
Heap deletion: O(logk)
So each node costs: O(logk)

Total Time Complexity :- Since there are total N nodes: O(N logk)
Space Complexity :- Priority queue stores at most k nodes. :- O(k)

>> Code Complexity Analysis :-
- for loop to insert head nodes of all the k linked lists :- it runs k times so O(k)
    - push operation is being used for all head node inside the for loop. push = O(log k)
So, time complexity of for loop :- O(k * log k)

- while loop :- runs till priority_queue is not empty, i.e., for all nodes in the lists. => O(N).
    - inside the while loop, we are using pq.top(), pq.pop() and pq.push(), all these takes O(log k)
    So, altogether these 3 methods take O(3 * log k)
So, time complexity of while loop :- O(N * 3 * log k) ~ O(N * log k)

Thus, total time complexity = O(k * log k) + O(N * log k)
*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    // minimum priority queue of pair of int (ListNode value) and ListNode reference
    priority_queue<
        pair<int, ListNode*>, 
        vector<pair<int, ListNode*>>, 
        greater<pair<int, ListNode*>>
    > pq;

    // insert the heads of all the k linked lists in the minimum priority queue
    for (ListNode* heads : lists) 
        if (heads) {
            // if heads would have been NULL, then heads->val would have given error 
            // error :- "runtime error: member access within null pointer of type 'ListNode'"      
            // so, this condition makes sure this case not happens
            pq.push({heads->val, heads});
        }
    
    ListNode* dummy = new ListNode(-1);     // dummy chain to connect the nodes in sorted order 
    ListNode* temp = dummy;
    
    // loop till priority_queue is not empty (till we have ListNodes left in the priority_queue)
    while (!pq.empty()) {
        pair<int, ListNode*> x = pq.top();  // get the minimum value Node from the priority_queue
        pq.pop();                           // remove that node from pq
        temp->next = x.second;              // add that node to the dummy chain (merged list)
        
        // if the removed node contains some next node, add it to the pq (only if its next is not NULL)
        if (x.second->next) 
            pq.push({x.second->next->val, x.second->next});
        
        temp = temp->next;                  // move temp ahead
    }
    
    return dummy->next;                     // head of the merged list
}

/*
The below approach adds all Nodes into the priority queue and then extracts the minimum nodes one by one, 
adding those nodes to the dummy chain and returns the dummy head. 
This approach will need O(N) extra space to store all the Nodes and all the priority queue operations will take 
O(log N), ... this will make this approach equivalent to the Naive approach.

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // minimum priority queue of pair of int (ListNode value) and ListNode reference
    priority_queue<
        pair<int, ListNode*>, 
        vector<pair<int, ListNode*>>, 
        greater<pair<int, ListNode*>>
    > pq;

    for (ListNode* curr : lists) {
        ListNode* temp = curr;
        while (temp) {
            pq.push({temp->val, temp});
            temp = temp->next;
        }
    }

    ListNode* dummy = new ListNode(-1);     // dummy chain to connect the nodes in sorted order 
    ListNode* temp = dummy;
    
    // loop till priority_queue is not empty (till we have ListNodes left in the priority_queue)
    while (!pq.empty()) {
        pair<int, ListNode*> x = pq.top();  // get the minimum value Node from the priority_queue
        pq.pop();                           // remove that node from pq
        temp->next = x.second;              // add that node to the dummy chain (merged list)
        
        temp = temp->next;                  // move temp ahead
    }
    return dummy->next;                     // head of the merged list
}
*/

int main() {

    return 0;
}