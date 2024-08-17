//// Counting Sort ////
/// By Anna DeVries ///

#include <iostream>
#include <stdlib.h>

// Global Variables
int n;

// Sorting operation
int counting_sort(int A[],int B[],int k){
    // Initialize an empty array
    int C[k+1];
    for(int i=0;i<(k+1);i++){
        C[i] = 0;
    }

    // Count instances of each distinct element
    for(int j=0;j<n;j++){
        C[A[j]] = C[A[j]] + 1;
    }

    // Match C array with size of final array
    for(int i=1;i<(k+1);i++){
        C[i] = C[i] + C[i-1];
    }

    // Sort elements
    for(int j=(n-1);j>=0;j--){
        B[C[A[j]]-1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }
}

// Find largest distinct element
int distinct(int A[]){
    int largest = A[0];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(A[j]>largest){
                largest = A[j];
            }
            if(A[i]>largest){
                largest = A[i];
            }
        }
    }
    return largest; 
}

int main(){
    // Initialize array
    int A[] = {20,18,5,7,16,10,9,3,12,14,0};

    n = sizeof(A)/sizeof(A[0]);
    int B[n-1], k;
    k = distinct(A);

    // Sorting operation
    counting_sort(A,B,k);

    // Print results
    std::cout<<"Original Array: ";
    for(int j=0;j<n;j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Sorted Array: ";
    for(int j=0;j<n;j++){
        std::cout<<B[j]<<" ";
    }
    std::cout<<std::endl;
}