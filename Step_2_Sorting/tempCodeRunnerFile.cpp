int pivot = arr[low];
    // int i = low + 1;
    // int j = high;
    // while(i <= j){
    //     while (arr[i] <= pivot && i <= high-1) i++;      // doing i <= high can lead to out of bounds for i == high since i++ will go out of bound
    //     while (arr[j] > pivot && j >= low+1) j--;        // doing j >= low can lead to out of bounds for j == low since j-- will go out of bound
    //     if (i < j) {
    //         swap(arr[i], arr[j]);
    //         i++;
    //         j--;
    //     }
    // }
    // swap(arr[low], arr[j]);
    // return j;