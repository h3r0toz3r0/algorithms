// Rand-Select with linear expected running time //
// 5 November 2019                               //
// Author: Anna DeVries                          //

#include <iostream>
#include <stdlib.h>

// Rearranges the subarray A[p...r] in place
int partition(int A[], int p, int r){
    // Initalize variables
    int x = A[r];       // pivot point
    int i = p - 1;
    int j,hold;

    // Rearranges
    for(j = p; j < r; j++){
        if(A[j] <= x){
            i = i + 1;
            std::swap(A[i], A[j]);
        }
    }

    std::swap(A[i + 1],A[r]);
    return i + 1;
}

// Randomizes pivot point
int randomized_partition(int A[], int p, int r){
    // Initalize variables
    srand(time(NULL));
    int i = (rand() % (r - p)) + p;

    std::swap(A[r],A[i]);
    return partition(A, p, r);
}

// Randomized Selection in expected linear time
int rand_select(int A[], int p, int r, int i){
    // Initialize variables
    int q, k;
    if(p == r){
        return A[p];
    }
    q = randomized_partition(A, p, r);

    k = q - p + 1;
    if(i == k){
        return A[q];
    }
    else if(i < k){
        return rand_select(A, p, q - 1, i);
    }
    else{
        return rand_select(A, q + 1, r, i - k);
    }
}

// Randomizes order of array
int randomize(int A[], int n){
    srand(time(NULL));
    for(int i = n - 1; i > 0; i--){  
        int j = rand() % (i + 1); 
        int hold = A[i];
        A[i] = A[j];
        A[j] = hold;
    }
}

int main(){
    // Initialize array A[1,2,...,99,100] as a random permutation
    int A[100];
    int n, p, r, j, i;

    for(int i = 0; i < 100; i++){
        A[i] = i+1;
    }
    n = sizeof(A)/sizeof(A[0]);
    i = 1;
    p = 0;
    r = n - 1;
    randomize(A, n);

    // Print original array
    std::cout << "Original Array: ";
    for(j = 0; j < n; j++){
        std::cout << A[j] << " ";
    }
    std::cout << std::endl;

    // Randomized selection algorithm
    std::cout << "Smallest Element: " << rand_select(A, p, r, i) << std::endl;
}