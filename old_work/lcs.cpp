// Dynamic programming of LCS //
// 5 November 2019            //
// Author: Anna DeVries       //

#include <iostream>
#include <stdlib.h>

// Initialize b table as global variable, such as b[m][n].
int b[7][6]; 

// Allows b table to store integers but users to call them with words.
enum DIRECTIONS{
    DIAGONAL=1,
    UP=2,
    LEFT=3
};

// Recursively prints out an LCS of X and Y in the proper, forward order.
void print_lcs(int X[], int i, int j){
    // Initalize variables
    int n, m;

    // If tables are empty, return
    if(i == 0 || j == 0){
        // Check last element for an arrow reference to c[0][j] || c[i][0]. If arrow is "up-left", print last X value.
        if(b[i][j] == DIAGONAL){
            std::cout << (char)X[i] << " ";
        }
        return;
    }

    // If last value in b table is "up-left", remove last row and column from table.
    // This value produces a LCS value
    if(b[i][j] == DIAGONAL){
        print_lcs(X, i - 1, j-1);
        std::cout << (char)X[i] << " ";
    }
    // If last value in b table is "up", remove last row from table.
    else if(b[i][j] == UP){
        print_lcs(X, i - 1, j);  
    } 
    // If last value in b table is "left", remove last column from table.
    else{
        print_lcs(X, i, j - 1);  
    }
}

// Constructs b and c tables for solving LCS.
void lcs_length(int X[], int Y[], int m, int n){
    // Initialize variables
    int i, j, k;

    // Print original arrays.
    std::cout << std::endl;
    std::cout << "X: ";
    for(j = 0; j < m; j++){
        std::cout << (char)X[j] << " ";
    }
    std::cout << std::endl;

    std::cout << "Y: ";
    for(j = 0; j < n; j++){
        std::cout << (char)Y[j] << " ";
    }
    std::cout << std::endl;

    // Initialize tables.
    int c[m + 1][n + 1];
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            b[i][j] = 0;
        }
    }
    for(i = 0; i <= m; i++){
        for(j = 0; j <= n; j++){
            c[i][j] = 0;
        }
    }

    // Fill values of table c and b in row-major order.
    for(i = 1; i <= m; i++){
        for(j = 1; j <= n; j++){
            if(X[i - 1] == Y[j - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i - 1][j - 1] = DIAGONAL;        
            }
            else if(c[i - 1][j] >= c[i][j-1]){
                c[i][j] = c[i - 1][j];
                b[i - 1][j - 1] = UP;        
            }
            else{
                c[i][j] = c[i][j-1];
                b[i - 1][j - 1] = LEFT;        
            }
        }
    }

    // Print c table
    std::cout << std::endl;
    std::cout << "C Table:" << std::endl;
    for(i = 0; i <= m; i ++){
        for(j = 0; j <= n; j++){
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print b table
    std::cout << std::endl;
    std::cout << "B Table:" << std::endl;
    for(i = 0; i < m; i ++){
        for(j = 0; j < n; j++){
            std::cout << b[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Find LCS
    std::cout << "Possible LCS: ";
    print_lcs(X, m-1, n-1);
    std::cout << std::endl;
    std::cout << std::endl;

    return;
}

int main(){
    // Initialize array A[] and B[]
    int X[] = {'A','B','C','B','D','A','B'};
    int Y[] = {'B','D','C','A','B','A'};
    int m = sizeof(X)/sizeof(X[0]);
    int n = sizeof(Y)/sizeof(Y[0]);

    lcs_length(X, Y, m, n);

    return 0;
}