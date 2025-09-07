#include <iostream>
#include <algorithm>
#include <functional> // used for greater<int>() ... though it is also included inside of <algorithm> so no need to include it explicitly
#include <vector>

using namespace std;

// user defind comparator : a function that takes two elements as input and compare them according to user defined logic.
// This comparator can be used to act as the key for sorting a container
// Syntax -> bool comp_name(data_type ele1 , data_type ele2 ) {....logic....} : assumption is ele1 is smaller than ele2 according to the logic
// bool comp (ele1 , ele2) checks whether ele1, ele2 are in correct user defined order or not i.e. if ele2 is logically greater to ele1 or not
// The comparator returns: 
// true → No swap (elements stay in the same order). ✅
// false → Swap the elements. ❌

bool comp (pair<int, int> p1, pair<int, int> p2) {
    if (p2.second > p1.second) return true;
    if ((p2.second == p1.second) && (p2.first < p1.first)) return true;
    return false;
}

int main() {
    // Reverse an Array
    // reverse(RAIterator_start, RAIterator_end) -> reverses the elements from start to end - 1 ... RAIterator means RandomAccessIterator
    // reverse works for all containers except map
    int arr[] = {1,2,3,4,5};
    reverse(arr, arr+5); // arr+5 is the end iterator which points to the element after the last element of the array

    // sort(RAIterator_start, RAIterator_end) -> sorts element upto end - 1
    // sort works for all containers except map

    int arr[] = {4,3,1,2,5};
    sort(arr, arr+5);
    cout << "Sorted Array : ";
    for(int x : arr) cout << x << " ";

    vector<int> v = {16,9,1,4,25};
    sort(v.begin(), v.end());
    cout << endl << "Sorted Vector : ";
    for(int x : v) cout << x << " ";

    // Sort only particular portion
    int arr2[] = {3,7,1,5,9,8,2};
    sort(arr2+4, arr2+7);
    cout << endl << "Partially Sorted Array : ";
    for(int x : arr2) cout << x << " ";

    // Sort in descending order
    cout << endl << "Reverse Sorted Array : ";
    sort(arr2, arr2+7, greater<int>());
    // greater<int>() is an object or instance of the greater<int> class.
    // It is used when you need to pass the comparator as an argument to a function, such as std::sort.

    // greater<int> is a type or class template provided by the <functional> header in C++.
    // It is used to specify the comparator type for containers like priority_queue or set.

    // Sort using user defined comparator

    pair<int, int> par[] = {{1,2}, {2,1}, {4,1}};
    // Sort the pair array according to the second element of each pair and in case the second element is same 
    // then sort it according to the first element but in decreasing order
    // so the desired sorted pair array is { {4,1}, {2,1}, {1,2} }
    sort(par, par+3, comp);         // comp is the user defined comparator function which will work as key for sorting the elements of the container
    cout << endl << "User defined comparator sorted array : ";
    for(auto x : par) cout << x.first << " - " << x.second << "\t";
    cout << endl;

    // __builtin_popcount() : return the no of set bits (bits which are 1) .
    int x = 7;
    int y = 6;
    cout << "__builtin_popcount(7) = " << __builtin_popcount(7) << " since 7 is 111 in binary so 3 bits are set to 1 rest are 0" << endl;
    cout << "__builtin_popcount(6) = " << __builtin_popcount(6) << " since 6 is 110 in binary so only 2 bits are set to 1 rest are 0" << endl;
    // __builtin_popcountll() is used for long long numbers
    long long ln = 1234567890123;
    cout << "__builtin_popcountll(1234567890123) = " << __builtin_popcountll(ln) << endl;

    // next_permutation(RAIterator_start, RAIterator_end) : returns the next permutation of a container. Returns false if no permutation exists. 
    // next_permutation works for all containers except map
    string s = "213";
    string nxt = next_permutation(s.begin(), s.end()) ? s : "No next permutation exists"; 
    cout << "Next permutation of string 213 is : " << nxt << endl;
    cout << "All permutations of 213 are : ";
    sort(s.begin(), s.end());
    do {
        cout << s << " ";
    }
    while (next_permutation(s.begin(), s.end()));

    // max_element(RAIterator_start, RAIterator_end) : returns the iterator pointing to the maximum element in the container
    // min_element(RAIterator_start, RAIterator_end) : returns the iterator pointing to the minimum element in the container
    int arr3[] = {1,2,3,4,5,6,7,8,9};
    cout << endl << "Max element in the array is : " << *max_element(arr3, arr3+9) << endl;
    cout << "Min element in the array is : " << *min_element(arr3, arr3+9) << endl;


}