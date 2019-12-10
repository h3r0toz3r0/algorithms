#include <iostream>
#include <stdio.h> 
#include <algorithm>
#include <stack>

// Comparison function.
// Determines max element.
bool comp(int a, int b){ 
        return (a < b); 
}

// Max-Min-Grouping function.
// Optimize grouping of elements into subarrays such that Bmin is maximized.
int* max_min_grouping(int A[],int N,int M){
// Initialize arrays and variables.
    int* G = (int*)malloc(sizeof(int) * M);
    int C[N][M];
    int* maxi; 
    int i, j, k, x, sum;

// Print A[].
    std::cout<<"A: ";
    for(i = 0;i < N; i++){
        std::cout<<A[i]<<" ";
    }
    std::cout<<std::endl;

// Initialize C[] and set all elements to 0.
    for(j = 0; j < M; j++){
        for(i = 0; i < N; i++){
            C[i][j] = 0;
        }
    }

// Initialize G[] and set all elements to 0.
    for(j = 0; j < M; j++){
        G[j] = 0;
    }

// Fill in row 1 of table C.
    C[0][0] = A[0];
    for(i = 1; i < N; i++){
// For current index, sum value index in A[] and value index-1 in C[].
        C[i][0] = C[i - 1][0] + A[i];
    }

// Fill in the rest of the table, beginning at row 2 of table C.
    for (i = 0; i < N; i++){ 
        for (j = 1; j < M; j++){ 

// If index value is less than the amount of subarrays, then this state is impossible and 0 is placed into table C.
            if(i < j){
                C[i][j] = 0;
            }

// Otherwise, case is functional.
// Initialize B[] as a temporary holding array of values.
            else{
                int B[i + 1];
                for(x = 0; x <= i; x++){
                     B[x] = 0;
                }

// Sum values of k using previous table entries.
// Compare sum and value at C[index]. Store min value into temporary array B[].
                for(k = j - 1; k < i; k++){
                    sum = C[i][0] - C[k][0]; 
                    B[k] = std::min(C[k][j - 1], sum);
                }
// Find the max element from temporary array B[] and add to table C.
                maxi = std::max_element(B, B + i, comp); 
                C[i][j] = *maxi;
            }
        } 
    } 

// Print table C[].
    std::cout<<"C: \n";
    for(j = 0;j < M; j++){
        for(i = 0;i < N; i++){
            std::cout<<C[i][j]<<" ";
        }
        std::cout << std::endl;
    }

// Pushes last row values 0 to len(A[]) onto stack and places largest values on top.
    std::stack<int> values;
    for(i = 0; i < N; i++){
        values.push(C[i][M-1]);
    }

// Initialize variables and pops last result.
    int largest = values.top();
    values.pop();

    int counter = 1;
    int last = N;
    j = M-1;

// Compare last result of the last row with values in other rows.
    for(i = N - 1; i >= 0; i--){
// If the next value equals largest, counter is added to G[] and restarted for next row.
        if(C[i][j] == largest){
            G[j + 1] = counter;
            last -= counter;
            counter = 0;
            j--;
        }
// If the next value is less than largest, the next largest value in the last row is popped.
        if(C[i][j] < largest){
            largest = values.top();
            if(largest == 0){
                if(j >= 0){
                    std::cout << "No Solution!\n";
                }
                break;
            }
            values.pop();
        }
        counter++;
    }
    G[0] = last+1;

    return G; 

}

int main(){
// Example 1.
    int A[] = {3, 9, 7, 8, 2, 6, 5, 10, 1, 7, 6, 4}; 
    int M = 3;
// Expected: {3,4,5}

// Example 2.
    // int A[] = {0, 0, 0, 0, 0, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    // int M = 2; 
// Expected: {6, 9}

// Example 3.
    // int A[] = {9, 1, 1, 1, 9}; 
    // int M = 2; 
// Expected: {2, 3}

// Example 4.
    // int A[] = {39, 500, 600, 400};
    // int M = 4;
// Expected: {1, 1, 1, 1}

// Example 5.
//     int A[] = {3, 9, 7, 8, 2, 6, 5, 10, 1, 7, 6, 4}; 
//     int M = 11;
// Expected: No Solution

    int N = sizeof(A)/sizeof(A[0]);
    int* ptr = max_min_grouping(A, N, M);
    
// Print G[] optimal.
    std::cout<<"G: ";
    for(size_t i = 0; i < M; i++){
        std::cout<<ptr[i]<<" ";
    }
    std::cout<<std::endl;

    return 0;
}