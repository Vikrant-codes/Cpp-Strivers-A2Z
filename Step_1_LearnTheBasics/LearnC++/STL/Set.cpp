#include <iostream>
#include <set>

using namespace std;

int main() {
    // Set is a sorted/ordered collection of distinct/unique values
    // Every operation take logarithmic time complexity O(log n)

    set<int> st;
    st.insert(1);       // {1}
    st.emplace(2);       // {1, 2}
    st.insert(2);       // {1, 2} .. stores only unique values
    st.insert(4);       // {1, 2, 4}
    st.insert(3);       // {1, 2, 3, 4} .. stores in sorted order
    for (int x : st) cout << x << " ";
    cout << endl;

    // begin(), end(), rbegin(), rend(), size(), empty(), swap() same as others

    auto it1 = st.find(3);       // returns iterator to the element
    auto it2 = st.find(5);      // if element not present then it returns set.end() location i.e. location after the last element

    st.erase(2);    // erases 3 .. takes logarithmic time
    st.erase(it1);  // erases the element at it2 reference ... it takes constant time
    // If the passed iterator is st.end(), calling st.erase(st.end()) will result in undefined behavior because st.end() is not a valid iterator for erasure.
    if (it2 != st.end()) {
        st.erase(it2);  // erases the element at it2 reference ... it takes constant time
    }
    for (int x : st) cout << x << " ";
    cout << endl;
    set<int> st2 = {1,2,3,4,5,6,7,8,9};
    auto it3 = st2.find(7);
    st2.erase(it3 , st2.end());

    st.swap(st2);       // swaps the elements of both the sets
    for (int x : st) cout << x << " ";
    cout << endl;
    for (int x : st2) cout << x << " ";
    cout << endl;

    // count() : returns the count of element in the set, since set contains only distinct values so it either returns 0 (if element not present in set) or 1

    int cnt = st.count(2);
    int cnt2 = st.count(5); 

    // lower_bound and upper_bound works in same way as in vectors but here no need to include algorithm header file as these are defined in set
    set<int> st_x = {1,2,3,4,5,6,7,8,9};
    auto lb = st_x.lower_bound(2);
    auto ub = st_x.upper_bound(2);
    cout << "Lower Bound : " << *lb << "\t Upper Bound : " << *ub << endl;
}