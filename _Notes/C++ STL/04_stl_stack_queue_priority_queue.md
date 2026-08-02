# STL: stack, queue, and priority_queue

These three are called container adapters — rather than being independent data structures built entirely from scratch, each one wraps around another underlying container (by default, `deque`) and restricts how you're allowed to access it, in order to enforce a specific, well-defined access pattern.

## stack

A `stack` follows Last-In-First-Out (LIFO) ordering — the most recently added element is always the first one to come back out, much like a physical stack of plates where you can only add or remove from the top.

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    cout << s.top() << endl;

    s.pop();
    cout << s.top() << endl;

    cout << s.size() << endl;
    return 0;
}
```

After pushing `1`, `2`, and `3` in that order, `s.top()` returns `3`, since it was the last element added. Calling `s.pop()` removes that top element (note that `pop()` removes the element but doesn't return it), so a subsequent `s.top()` now returns `2`. `s.size()` reflects however many elements currently remain — `2` at this point. There's no way to look at or access anything other than the top element of a stack — that restriction is exactly the point, since it models situations like undo history, recursive call tracking, or checking for balanced parentheses, where only the most recent item should ever matter.

## queue

A `queue` follows First-In-First-Out (FIFO) ordering — the first element added is also the first one removed, much like people waiting in a line.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << q.front() << endl;
    cout << q.back() << endl;

    q.pop();
    cout << q.front() << endl;
    return 0;
}
```

After pushing `1`, `2`, and `3`, `q.front()` gives `1`, the very first element added, while `q.back()` gives `3`, the most recently added element. Calling `q.pop()` removes the front element (`1`), so a subsequent `q.front()` now returns `2`. Queues naturally model scenarios like task scheduling or breadth-first search, where items need to be processed in exactly the order they arrived.

## priority_queue

A `priority_queue` doesn't preserve insertion order at all — instead, it always keeps the largest element (by default) readily accessible at the front, regardless of when it was inserted. Internally, it's implemented using a data structure called a heap, which efficiently maintains this "largest first" property even as elements are added and removed.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    priority_queue<int> pq;

    pq.push(3);
    pq.push(7);
    pq.push(1);
    pq.push(5);

    cout << pq.top() << endl;

    pq.pop();
    cout << pq.top() << endl;
    return 0;
}
```

Even though `7` wasn't the first or last value pushed, `pq.top()` immediately returns `7`, since it's the largest of all the values currently stored. After `pq.pop()` removes it, `pq.top()` now returns `5`, the next-largest remaining value. This is extremely useful whenever you repeatedly need "the current maximum," such as in scheduling the most urgent task, or in graph algorithms like Dijkstra's shortest path.

By default, a `priority_queue` behaves as a max-heap, always surfacing the largest value first. To get a min-heap instead, which always surfaces the smallest value, you specify the underlying container and comparison type explicitly:

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(3);
minHeap.push(7);
minHeap.push(1);

cout << minHeap.top() << endl;
```

Here, `minHeap.top()` returns `1`, the smallest value, since `greater<int>` reverses the usual ordering that `priority_queue` uses internally.

## Comparing the Three

| Container | Access pattern | Common use case |
|---|---|---|
| `stack` | last in, first out | undo history, recursive backtracking, parenthesis matching |
| `queue` | first in, first out | task scheduling, breadth-first search |
| `priority_queue` | highest priority first | always retrieving the current maximum or minimum |

None of these three support iterating freely through all their elements or accessing an arbitrary middle element the way `vector` or `list` do — that restriction is intentional, since it's exactly what makes each one a faithful, mistake-resistant model of its intended access pattern.
