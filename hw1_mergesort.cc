// Merge-Sort Algorithm
// By Anna DeVries

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <chrono>

// Sorts vector
void merge(int v[], int left, int midpoint, int right){
    int n_1 = midpoint - left + 1;
    int n_2 = right - midpoint;

    int* L = new int[n_1];
    int* R = new int[n_2];

    for (int i = 0; i < n_1; i++){
        L[i] = v[left + i];
    }

    for (int j = 0; j < n_2; j++){
        R[j] = v[midpoint + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while(i < n_1 && j < n_2){
        if(L[i] <= R[j]){
            v[k] = L[i];
            i++;
        }
        else{
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n_1){
        v[k] = L[i];
        i++;
        k++;
    }

    while(j < n_2){
        v[k] = R[j];
        j++;
        k++;
    }

    delete[] L, R;
}

void merge_sort(int v[], int left, int right){
    int midpoint;

    if (left < right){
        midpoint = left + (right - left) / 2;
        merge_sort(v, left, midpoint);
        merge_sort(v, midpoint + 1, right);
        merge(v, left, midpoint, right);
    }
}

// Prints vector
void print_vector(int v[], int n){
    int i;
    std::cout << "Vector: ";
    for (i = 0;i < n; i++)
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
    
    //print_vector(v, n);
    
    // Initialize clock
    auto start = std::chrono::high_resolution_clock::now();

    //print_vector(v,n);

    // Performs sorting operations
    merge_sort(v, 0, n-1);
    
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Duration to sort (sec): " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << " ns\n";

    //print_vector(v, n);

    // Frees memory 
    delete[] v;