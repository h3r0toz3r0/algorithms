//// Heap Sort ////
///By Anna DeVries///

#include <iostream>
#include <stdlib.h>
int heapsize,n;

// Returns left node value
int left(int i){
    return 2*i + 1;
}

// Returns right node value
int right(int i){
    return (2*i)+ 2;
}

// Corrects single instance, ensuring parent key > children keys
int max_heapify(int A[], int i){
    int l = left(i);
    int r = right(i);
    int largest;

    if(l < heapsize && A[l] > A[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if(r < heapsize && A[r] > A[largest]){
        largest = r;
    }

    if(largest != i){
        std::swap(A[i],A[largest]);
        max_heapify(A,largest);
    }
}

// Converts array into max_heap
int build_max_heap(int A[]){
    heapsize = n;

    for(int i=(n/2) - 1;i>=0;i--){
        max_heapify(A,i);
    }
}

// Sorts array
int heapsort(int A[]){
    build_max_heap(A);

    for(int i=n-1;i>=0;i--){
        std::swap(A[0],A[i]);
        heapsize = heapsize - 1;
        max_heapify(A,0);
    }
}

int randomize(int A[]){
    srand(time(NULL));
    for(int i=n-1;i>0;i--){  
        int j = rand() % (i + 1); 
        int hold = A[i];
        A[i] = A[j];
        A[j] = hold;
    }
}

int main(){
    // Initialize array A[1,2,...,99,100] as a random permutation
    int A[100];
    for(int i=0;i<100;i++){
        A[i] = i+1;
    }
    n = sizeof(A)/sizeof(A[0]);
    randomize(A);

    // Print original array
    std::cout<<"Original Array: ";
    for(int j=0;j<n;j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;

    // Sorting operation
    heapsort(A);
    
    // Print sorted array
    std::cout<<"Sorted Array: ";
    for(int j=0;j<n;j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;
}