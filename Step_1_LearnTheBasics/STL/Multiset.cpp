#include <iostream>
#include <set>

using namespace std;

int main(){
    // Multiset, similar to sets, also stores elements in ordered manner but /
    // it can store multiple occurences of elements, unlike sets which store only distinct elements

    multiset<int> ms = {1,2,1,3,1,4,2,3};       // Elements stored in ordered manner {1, 1, 1, 2, 2, 3, 3, 4}
    for(int x : ms) cout << x << " ";           // 1 1 1 2 2 3 3 4
    cout << endl;
    cout << "No. of occurences of 1, 2, 3 and 4 : " << ms.count(1) << " " << ms.count(2) << " " << ms.count(3) << " " << ms.count(4) << endl;

    // Deletion in Multiset
    // Remove all occurences
    ms.erase(3);                                // erases all occurences of 3
    cout << "No. of occurences of 3 : " << ms.count(3) << endl; // 0
    // Remove only one occurence
    ms.erase(ms.find(2));                       // find() gives the iterator to the first occurence of the element so only one occurence is removed
    // Remove some occurences of an element
    ms.erase(ms.find(1), next(ms.find(1), 2));
    for(int x : ms) cout << x << " ";           // 1 2 4

    // Rest other functions are same as set

}