#include <iostream>
#include <queue>

using namespace std;

int main() {
    // Elements are inserted on the basis of priority : maximum at top and minimum at last
    // A tree data structure is maintained for priority_queue

    // Time Complexity : push() = O(log n) , top() = O(1) and pop() = O(log n)

    // max_heap : for maximum priority_queue and min_heap : for minimum priority_queue

    // In C++, priority_queue is a max heap by default.

    priority_queue<int> pq;
    pq.push(5);     // {5}
    pq.push(2);     // {5, 2}
    pq.push(8);     // {8, 5, 2}
    pq.push(10);    // {10, 8, 5, 2}
    pq.emplace(3);    // {10, 8, 5, 3, 2}
    cout << "Top element : " << pq.top() << endl;       // prints 10
    pq.pop();       // {8, 5, 3, 2}
    cout << "Top element : " << pq.top() << endl;       // prints 8

    // size swap empty function same as others

    // Minimum priority_queue / min_heap

    // To make priority_queue a min heap (minimum priority queue), we use greater<>.
    /*
    Syntax :-   priority_queue<int, vector<int>, greater<int>> pq;
    - int → type of elements
    - vector<int> → underlying container
    - greater<int> → makes smallest element come first

    Syntax for minimum priority queue of pairs:-
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;
        
    Pairs are compared lexicographically:
    - first element first
    - then second if needed
    */

    cout << "Minimum priority_queue / min_heap" << endl;
    priority_queue<int, vector<int>, greater<int>> mpq;
    mpq.push(5);     // {5}
    mpq.push(2);     // {2, 5}
    mpq.push(8);     // {2, 5, 8}
    mpq.push(10);    // {2, 5, 8, 10}
    mpq.emplace(3);     // {2, 3, 5, 8, 10}
    cout << "Top element : " << mpq.top() << endl;       // prints 2
    mpq.pop();      // {3, 5, 8, 10}
    cout << "Top element : " << mpq.top() << endl;       // prints 3

    /*
    ### Common Methods of priority_queue in C++
    | Method    | Description                                             |
    | --------- | ------------------------------------------------------- |
    | `push(x)` | Insert element into priority queue.                     |
    | `top()`   | Returns highest priority element.                       |
    | `pop()`   | Removes top element --> pop() does not return anything. |
    | `empty()` | Check if queue is empty                                 |
    | `size()`  | Returns number of elements.                             |

    >> top() :-
        - For max heap → largest
        - For min heap → smallest
    */
}