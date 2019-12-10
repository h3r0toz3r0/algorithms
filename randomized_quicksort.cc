//// Randomized Quicksort ////
///  By Anna DeVries      ///

#include <iostream>
#include <stdlib.h>
#include <chrono>

// Rearranges the subarray A[p...r] in place
int partition(int A[], int p, int r){
    int x = A[r];       // pivot point
    int i = p - 1;
    int j,hold;

    for(j=p;j<=(r-1);j++){
        if(A[j] <= x){
            i = i + 1;
            std::swap(A[i],A[j]);
        }
    }

    std::swap(A[i+1],A[r]);
    return i+1;
}

// Randomizes pivot point
int randomized_partition(int A[], int p, int r){
    srand(time(NULL));
    int i = p+rand() % (r-p);
    std::swap(A[r],A[i]);
    return partition(A, p, r);
}

// Sorting operation
int randomized_quicksort(int A[], int p, int r){
    if(p < r){
        int q = randomized_partition(A,p,r);
        randomized_quicksort(A,p,q-1);
        randomized_quicksort(A,q+1,r);
    }
}

int main(){
    // Initialize array A[1,2,...,99,100]
    int A[100];
    for(int i=0;i<100;i++){
        A[i] = i+1;
    }
    int p = 0;
    int r = sizeof(A)/sizeof(A[0])-1;

    // Perform sorting operations 5 times
    for(int i=0;i<5;i++){
        // Initialize clock
        auto start = std::chrono::high_resolution_clock::now();

        // Perform sorting operations
        randomized_quicksort(A, p, r);
        
        // End and print clock
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Duration to sort trial "<<i+1<<": " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << " ns\n";
    }
   
    // Print new array
    std::cout<<"Sorted Array: ";
    for(int j=0;j<sizeof(A)/sizeof(A[0]);j++){
        std::cout<<A[j]<<" ";
    }
    std::cout<<std::endl;
}