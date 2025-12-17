// A vector is a dynamic array in C++ that can grow or shrink in size automatically. It is part of the <vector> library.

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>  // Required for lower_bound() & upper_bound()
#include <set>       // Required for set : used here to demonstrate vector creation using iterators
using namespace std;

void printElements(vector<int> v) {
    /*
    for(int i=0; i<v.size(); i++){
        cout << v[i] << "\t";
    } 
    */
    // auto & Range-Based Loop (Best Readability) : Performance similar to v[i], Best for readability, Uses iterators internally
    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    // Declarations
    vector<int> v;  // Declare an empty vector
    v = {1,2,3,4,5};
    vector<int> x = {1,4,9,16,25};      // Declaration & Initialization

    // vector_name[i] or vector_name.at(i) : ith element of the vector
    // vector.front() --> Returns the first element... vector.back() --> Returns the last element
    cout << "First element of vectors v and x : " << v.front() << "\t" << x.at(0) << endl;
    cout << "Size of the vectors : " << v.size() << "\t" << x.size() << endl;
    cout << "Last element of vector v and x : " << v.back() << "\t" << x.back() << endl;

    v.push_back(6); // Add elements
    x.emplace_back(36); // Add elements
    printElements(v);
    printElements(x);

    // Vector having pairs as elements : Pair of int & String --> vector<pair<int, string>>

    vector<pair<int, string>> pair_vector;
    pair_vector.push_back({1,"A"});
    pair_vector.emplace_back(2,"B");
    cout << "First Pair Element of Vector : " << pair_vector[0].first << " " << pair_vector[0].second << endl;
    cout << "Second Pair Element of Vector : " << pair_vector[1].first << " " << pair_vector[1].second << endl;

    vector<int> v2(5);      // initial size of vector v2 = 5 ... conatins garbage values or 0s
    vector<int> v3(5,10);   // initial size of vector v3 = 5 ... conatining default value = 10 at each index
    printElements(v2);
    printElements(v3);
    cout << "Size of v2 (Before pushing): " << v2.size() << endl;
    v2.push_back(99);
    cout << "Size of v2 (After pushing): " << v2.size() << endl;

    vector<int> copy_v3(v3);     // passing another vector as parameter generates a copy of that vector
    printElements(copy_v3);

    // Deletion in Vectors : vector.erase(memory_address) , memory_address -- iterator

    vector<int> ex = {1,-1,2,3,-2,-3,-4,4,5};
    cout << "Deletion in Vectors" << endl << "Initial Vector : ";
    printElements(ex);
    // erase function takes iterators (memory address) as arguments to remove the desired element.
    // It erases the desired element(s) then shifts the remaining elements to the left
    // vector.erase(location) : removes element at the location
    ex.erase(ex.begin()+1);         // ex.begin()+1 is the location of the 2nd element .. so 2nd element i.e. -1 is removed
    printElements(ex);              // {1,2,3,-2,-3,-4,4,5}
    // vector.erase(start, end) : [start,end) removes elements from start till end-1
    ex.erase(ex.begin()+3, ex.begin()+6);       
    printElements(ex);              // {1,2,3,4,5}

    // Insertion in Vectors

    // Inserting a Single Element --> vector.insert (iterator position, const T& value);
    vector<int> vec = {10, 20, 30, 40};
    cout << "Insertion in Vectors" << endl << "Initial Vector : ";
    printElements(vec);
    vec.insert(vec.begin() + 1, 100);  // Insert 100 at index 1
    vec.emplace(vec.begin() + 1, 90);
    printElements(vec);                // 10 90 100 20 30 40
    // Inserting Multiple Copies --> vector.insert (iterator position, size_type n, const T& value);
    vec.insert(vec.begin() + 2, 3, 50); 
    printElements(vec);                 // 10 90 100 50 50 50 20 30 40
    // Inserting a Range from Another Vector --> vector.insert (iterator position, InputIterator first, InputIterator last);
    vector<int> vec1 = {10, 20, 30};
    vector<int> vec2 = {100, 200, 300};
    vec1.insert(vec1.begin() + 1, vec2.begin(), vec2.end());
    printElements(vec1);                // 10 100 200 300 20 30

    // Inserting Complex Objects (Best for emplace())
    vector<pair<int, string>> cmpv;
    cmpv.insert(cmpv.begin(), make_pair(2,"Bob"));
    cmpv.emplace(cmpv.begin(), 1, "Alice");       // Directly constructs in-place
    cmpv.emplace_back(3, "Charlie");
    cout << cmpv[0].first << " " << cmpv[0].second << " _ " << cmpv[1].first << " " << cmpv[1].second << " _ ";
    cout << cmpv[2].first << " " << cmpv[2].second << endl;

    vector<int> nv = {1,2,3,4,5};
    nv.pop_back();          // Removes last element
    cout << "After pop_back() : ";
    printElements(nv);
    vector<int> nv2 = {4,3,2,1};
    nv.swap(nv2);           // swaps both vectors
    printElements(nv);
    printElements(nv2);
    nv2.clear();            // erases entire vector 
    printElements(nv2);
    // vector.empty() : Returns 0 (False) if vector contains at least 1 element , otherwise 1 (True)
    cout << "Is nv empty ? " << nv.empty() << endl << "Is nv2 empty ? " << nv2.empty() << endl;

    // vector.resize(n) --> Changes the size of the vector.
    vector<int> example(5);
    cout << "Size of example vector : " << example.size() << endl;
    example.resize(10); // Resizes the vector to 10 elements
    cout << "Size of example vector after resizing : " << example.size() << endl;

    /*
    upper_bound() and lower_bound() functions 
    🔹available in ordered containers like vector, set, map or multiset.
    🔹used to perform binary search in sorted vectors or other containers efficiently.
    1️⃣ lower_bound() : Finds the first element that is greater than or equal to a given value.
    2️⃣ upper_bound() : Finds the first element that is strictly greater than the given value.
    3️⃣ Practical Use Case: Count Frequency of an Element. We can find the frequency of an element using upper_bound() - lower_bound().
    */
    vector<int> exv = {10, 20, 20, 20, 30, 40, 50};
    auto lb = lower_bound(exv.begin(), exv.end(), 20);  // Finds first ≥ 20
    cout << "Lower Bound of 20: " << (lb != exv.end() ? to_string(*lb) : "Not Found") << endl;
    auto ub = upper_bound(exv.begin(), exv.end(), 20);  // Finds first > 20
    cout << "Upper Bound of 20: " << (ub != exv.end() ? to_string(*ub) : "Not Found") << endl;
    int count = ub - lb;
    cout << "Frequency of 20 : " << count << endl;

    // special way to create a vector: by giving two iterators — begin and end of another container.
    // vector<Type> new_vector(old_container.begin(), old_container.end());
    set<int> s = {1,2,3,4,5,1};
    vector<int> vec_from_set(s.begin(), s.end()); // Create a vector from a set
    for(int x : vec_from_set) cout << x << " ";

    // reserve function in Vectors 
    vector<int> new_vc;
    new_vc.reserve(10);   // // Pre-allocates memory for 10 elements
    /*
    Que> Does vector dynamic resizing happens when we use reserve or not ?

    | Scenario                     | Reallocations?       | When resizing happens    |
    | ---------------------------- | -------------------  | ------------------------ |
    | No `reserve()`               | Yes, multiple times  | Whenever capacity full   |
    | `reserve(10)` + ≤10 elements | ❌ No                | Never (fits perfectly)   |
    | `reserve(10)` + >10 elements | ✅ Once              | When adding 11th element |
    */

    // reserve works for strings, vectors, unordered_map & unordered_set
    /*
    ✅ Containers that support .reserve()
    | Container                                  | Works?  | Purpose                                         |
    | ------------------------------------------ | ------- | ----------------------------------------------- |
    | `std::string`                              | ✅      | Preallocate memory for characters               |
    | `std::vector`                              | ✅      | Preallocate memory for elements                 |
    | `std::deque`                               | ❌      | Doesn’t use contiguous storage                  |
    | `std::list`                                | ❌      | Linked list — no contiguous memory              |
    | `std::forward_list`                        | ❌      | Singly linked list — no contiguous memory       |
    | `std::array`                               | ❌      | Fixed size — cannot reserve                     |
    | `std::unordered_map`, `std::unordered_set` | ✅      | Preallocate *buckets* to reduce rehashing       |
    | `std::map`, `std::set`                     | ❌      | Tree-based — dynamic nodes, no reserving memory |
    */
    return 0;
}