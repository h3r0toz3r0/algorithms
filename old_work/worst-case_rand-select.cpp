// Rand-Select with linear worst-case running time //
// 5 November 2019                                 //
// Author: Anna DeVries                            //

#include <iostream>
#include <stdlib.h>
#include <algorithm> 

// Rearranges the subarray A[p...r] in place
int partition(int A[], int p, int r, int x){
    // Initalize variables
    int i = p - 1;
    int j, hold;

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

// Returns median value
int median(int A[],int n){
    std::sort(A, A + n);
    return A[n / 2];
}

// Randomized Selection in worst-case linear time
int rand_select(int A[], int p, int r, int i){
    // Initalize varaibles
    int j, k, q, x, y;
    int B[(r - p + 5) / 5];   

    // Divide the n elements into n/5 groups of 5 elements each
    for(j = 0; j < ((r - p + 1) / 5); j++){
        B[j] = median(A + p + j * 5, 5); 
    }   

    // Recursively select the median x of the n/5 medians
    if(j * 5 < (r - p + 1)){ 
        B[j] = median(A + p + (j * 5), (r - p + 1) % 5);  
        j++; 
    }     
    if(j == 1){
        x = B[j - 1];
    }
    else{
        x = rand_select(B, 0, j - 1, j / 2);
    }   

    // Partition with x as pivot
    q = partition(A, p, r, x);  

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
    int n, p, r, j, i;
    int A[100];

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