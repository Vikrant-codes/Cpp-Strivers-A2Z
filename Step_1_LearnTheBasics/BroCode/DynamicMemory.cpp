#include <iostream>
using namespace std;

// Dynamic Memory & Variables
/*
>> Dynamic memory = memory that is allocated at runtime (while the program is running), not at compile time.
The 'new' operator is used to allocate memory in the heap rather than the stack.
• Size is decided during execution
• Memory comes from the heap
• You control when to allocate and free it

>> Static vs Dynamic
| Feature              | Static / Stack     | Dynamic / Heap       |
| -------------------- | ------------------ | -------------------- |
| When size is decided | Compile time       | Runtime              |
| Memory area          | Stack              | Heap                 |
| Lifetime             | Auto (scope-based) | Until manually freed |
| Control              | Compiler           | Programmer           |

Dynamic Memory is useful when we don't know how much memory we will need. 
It makes our program more flexible, especially when accepting user input.

>> What are “dynamic variables”?
A dynamic variable is a variable whose memory is allocated using new.
|   int* pNum = new int;
|   *pNum = 21;
What’s happening:
1. new int → allocates memory for one integer on heap
2. Returns the address
3. Address is stored in pointer pNum
4. pNum can then be used to access the allocated memory
5. *pNum accesses the value at that memory

📌 Important: pNum itself is on the stack, but the int it points to is on the heap

>> Why pointers are mandatory for dynamic memory
We cannot directly access heap memory without a pointer. Dynamic memory = always accessed via pointers.

>> Releasing dynamic memory (delete)
Unlike stack memory, heap memory is NOT auto-destroyed. To release/delete the allocated memory, we use delete keyword
Single variable: delete pNum;
Array: delete[] arr;

>> What happens if you DON’T delete it?
🔴 Memory Leak
Every time func() runs:
• memory is allocated
• memory is never returned
👉 Program keeps eating memory
👉 Long-running programs may crash or slow down
|   “Memory leak is wastage of heap memory due to improper deallocation.”

>> What happens when you delete memory?
Internally:
1. Memory is returned to the heap
2. Destructor is called (for objects)
3. That memory can be reused later
📌 Value is gone — memory is no longer yours

IMPORTANT: pointer after delete
|   delete p;
Now:
• p still holds the old address
• but that address is invalid
This is called a 'dangling pointer'.

✅ Correct practice:
|   delete p;
|   p = nullptr;

>> What happens if you use pointer AFTER delete ❌
|   delete p;
|   cout << *p;   // ❌ undefined behavior
• May crash
• May print garbage
• May appear to “work” (dangerous!)

Summary :
→ new allocates memory from heap
→ delete releases that memory
→ Not deleting causes memory leak
→ Using pointer after delete causes undefined behavior
→ Always set pointer to nullptr after delete
*/

// Dangling Pointers vs Wild Pointers
/*
🔴 Wild Pointer
| A wild pointer is a pointer that is declared but never initialized.
Code example - int* p;   // wild pointer
• Points to garbage address
• No memory assigned
• Very dangerous

✅ How to avoid wild pointers
int* p = NULL;   // or nullptr in C++

🔵 Dangling Pointer
| A dangling pointer points to memory that has already been freed or destroyed.

Example 1: After delete/free
|   int* p = new int;
|   delete p;
|   // p is now a dangling pointer

Example 2: Returning address of local variable
|   int* func() {
|       int x = 10;
|       return &x;   // dangling pointer
|   }

✅ How to avoid dangling pointers
|   delete p;
|   p = NULL;   // or nullptr

🔥 Key Difference Table (EXAM GOLD)
| Feature        | Wild Pointer             | Dangling Pointer         |
| -------------- | ------------------------ | ------------------------ |
| Initialization | ❌ Not initialized      | ✅ Was initialized       |
| Memory state   | ❌ Never allocated      | ❌ Memory freed          |
| Cause          | Forgot to assign address | Used after free/delete   |
| Example        | `int* p;`                | `delete p;`              |
| Fix            | Initialize to NULL       | Set to NULL after delete |
*/

int main() {
    // Dynamic Variables
    int* pNum = NULL;
    pNum = new int;             // When you use new, memory is allocated from the heap.
    *pNum = 21;

    cout << "Address : " << pNum << '\n';
    cout << "Value : " << *pNum << '\n';

    delete pNum;        // release the memory 
    
    // Dynamic Arrays
    char* pName = NULL;

    int size;       // to store the user-defined size
    cout << "Enter size of the dynamic array : ";
    cin >> size;

    pName = new char[size];
    // take user input of elements
    for (int i = 0; i < size; i++) {
        cout << "Enter char#" << i + 1 << " of name : ";
        cin >> pName[i];
    }
    // display the elements
    for (int i = 0; i < size; i++) {
        cout << pName[i] << " ";
    }

    delete[] pName;


    return 0;
}