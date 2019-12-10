// Insertion Sort Algorithm
// By Anna DeVries

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <chrono>

// Sorts vector
void insertion_sort(int v[], int n){
    int value;
    int i, j;

    for (i=1;i<n;i++){
        value = v[i];
        j = i-1;
        while(j>=0&&v[j]>value){
            v[j+1] = v[j];
            j--;
        }
        v[j+1]=value;
    }
}

// Prints vector
void print_vector(int v[], int n){
    int i;
    std::cout << "Vector: ";
    for (i=0;i<n;i++)
        std::cout << " " << v[i];
    std::cout << std::endl;
}

int main(int argc, char* argv[]){
    // Check that there are two arguments
    if( argc != 2){
        std::cout << "Usage: " << argv[0] << " <size>\n";
        return EXIT_FAILURE;
    }

    // Check that argv[1] is a valid integer
    char* arg = argv[1];
    for(int i = 0; i < strlen(arg); i++) {
        if(arg[i] < '0' || arg[i] > '9'){
            std::cout << "Please enter an integer \n";
            std::cout << "Usage: " << argv[0] << " <size>\n";
            return EXIT_FAILURE;
        }
    }

    // Converts user input n to an integer
    int n = atoi(argv[1]);
    std::cout << "Size n = " << n << std::endl;

    // Allocates space for array and fills in array at size n as worst-case scenario
    int numbers = n - 1;
    int* v = new int[n];
    for(int i = 0; i < n; i++){
        v[i] = numbers;
        numbers--;
    }
    
    // Initialize clock
    auto start = std::chrono::high_resolution_clock::now();

    //print_vector(v,n);

    // Performs sorting operations
    insertion_sort(v,n);
    
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Duration to sort (sec): " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << " ns\n";

    //print_vector(v,n);

    // Frees memory 
    delete[] v;
}