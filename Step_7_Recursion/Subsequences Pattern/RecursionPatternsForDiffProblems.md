# Basic Structure of different recursive patterns

## 1. Print all Subsequences 
*for each element of arr, there can be two conditions: take the element or don't take the element. We explore both scenarios and do the same for further elements.*

```
void fun(ind, list) {
    // Base Case
    (if ind == n) {
        print(list);
        return;
    }

    // take current element condition
    list.add(arr[ind]);
    fun(ind + 1, list);

    // not take current element condition
    list.remove(arr[ind]);
    fun(ind + 1, list);
}
```

## 2. Print all solutions (Print all subsequences whose sum is K)
*if base condition satisfied, check the required condition, if true print current solution.*

```
void fun() {
    // Base Case
    (base condition) {
        if (condition satisfied) 
            print(current_solution);

        return;
    }

    // further recursive calls to explore more/other ways
    fun()
    fun()
    ... 
}
```

Example: Print all subsequences whose sum is K
```
void fun(ind, list, sum) {
    // Base Case
    (if ind == n) {
        if (sum == k) {
            print(list);
        }
        return;
    }

    // take current element condition
    list.add(arr[ind]);
    sum += arr[ind];
    fun(ind + 1, list, sum);

    // not take current element condition
    list.remove(arr[ind]);
    sum -= arr[ind];
    fun(ind + 1, list, sum);
}
```

## 3. Print any 1 solution (Print any 1 subsequence with sum k)
*return true/false depending on solution found or not, avoid further recursive calls if any solution is found.*

```
bool fun() {
    // Base Case
    (base condition) {
        if (condition satisfied) {
            print(current_solution);
            return true;
        }

        // else condition not satisfied
        return false;
    }

    // explore more/other ways, but if any of them returns true, stop further calls and return immediately 
    
    // 1st recursive call, if it returns true, stop further execution by returning true to go back to the outermost caller
    if (fun()) {
        return true;
    } 

    // 2nd recursive call
    if (fun()) {
        return true;
    }

    ...

    // if none of the recursive call returned true, return a false
    return false;
}
```

Example: Print any 1 subsequences whose sum is K
```
bool fun(ind, list, sum) {
    // Base Case
    (if ind == n) {
        if (sum == k) {
            print(list);
            return true;
        }
        return false;
    }

    // take current element condition
    list.add(arr[ind]);
    sum += arr[ind];
    if (fun(ind + 1, list, sum)) return true;

    // not take current element condition
    list.remove(arr[ind]);
    sum -= arr[ind];
    if (fun(ind + 1, list, sum)) return true;

    return false;
}
```


## 4. Count all solutions which satisfies some condition (Count all subsequences whose sum is k)
*return 1 or 0 depending on condition satisfied, add the returned values of all recursive calls and return this final sum value.*

```
int fun() {
    // Base Case 
    (base condition) {
        if (condition satisfied) {
            return 1;
            // this 1 will contribute to the final count
        }
    
        // condition not satisfied
        return 0;
    }

    // if only two recursive calls, we can do it like below

    // left = fun();   
    // right = fun();
    // return left + right;

    // for multiple recursive calls, we can do it like this
    
    sum = 0;

    sum += fun();
    sum += fun();
    ...
    sum += fun();
    // n recursive calls

    return sum;
}
```

Example: Count all subsequences whose sum is K
```
int fun(ind, sum) {
    // Base Case
    (if ind == n) {
        if (sum == k) {
            print(list);
            return 1;
        }
        return 0;
    }

    // take current element condition
    sum += arr[ind];

    left = fun(ind + 1, sum);

    // not take current element condition
    sum -= arr[ind];
    
    right = fun(ind + 1, sum);

    return left + right;
}
```