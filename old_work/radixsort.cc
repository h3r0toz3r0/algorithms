//// Radix Sort ////
///By Anna DeVries///

#include <iostream>
#include <stdlib.h>
#include <cmath>

// Global Variables
int n;

// Sorting operations -- stable sort
int counting_sort(int A[],int k){
    int B[n-1],i;
  
    // Initialize an empty array
    int C[10];
    for(int i=0;i<(10);i++){
        C[i] = 0;
    }

    // Count instances of each distinct element
    for(int j=0;j<n;j++){
        C[(A[j]/k)%10] = C[(A[j]/k)%10] + 1;
    }

    // Match C array with size of final array 
    for(int i=1;i<10;i++){
        C[i] = C[i] + C[i-1];
    }

    // Sort elements 
    for(int j=(n-1);j>=0;j--){
        B[C[(A[j]/k)%10]-1] = A[j];
        C[(A[j]/k)%10] = C[(A[j]/k)%10] - 1;
    }

    // Copy B[] into A[] 
    for(i=0;i<n;i++){ 
        A[i] = B[i]; 
    }
}

// Sorting operation -- radix sort
int radix_sort(int A[], int d){ 
    for(int i=1;d/i>0;i*=10){
       counting_sort(A,i); 
    }
} 

// Find largest distinct element and return its number of digits
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
    int A[] = {329,457,657,839,436,720,353};
    n = sizeof(A)/sizeof(A[0]);
    int d = distinct(A);

    // Print original array
    std::cout<<"Original Array: ";
    for(int j=0;j<n;j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;

    // Sorting operation
    radix_sort(A,d);

    // Print sorted array
    std::cout<<"Sorted Array: ";
    for(int j=0;j<n;j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;
}