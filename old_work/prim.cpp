//  Prim's Algorithm        //
//  19 November 2019        //
//  Author: Anna DeVries    //

//              Libraries                                                                               //
#include <iostream> 
#include <stdlib.h> 
#include <vector>
#include <bits/stdc++.h>
#include <algorithm> 
#include <iterator>

//              Macros                                                                                  //
#define V 8

//              Add point from graph to each graph representation                                       //
void add_point(int matrix[V][V], std::vector<std::pair<int, int>> list[], int node, int connection, int weight){
    //      Add Points to Matrix                //
    matrix[node][connection] = weight;
    matrix[connection][node] = weight;

    //      Add Points to List                  //
    list[node].push_back(std::make_pair(connection, weight)); 
    list[connection].push_back(std::make_pair(node, weight)); 

    return;
}

//              Find Minimum to Extract                                                                 //
int extract_min(std::vector<int> Q, std::vector<int> key, std::vector<int> trash){
    //      Local Variables                     //
    int prev, next, index, extract_min_index;

    //      Initialize Variables                //
    prev = INT_MAX;
    extract_min_index = 0;

    //      Iterate through list                //
    for(index = 0; index < V; index++){
        next = key[index];

        //      Compare minimum with next value     //
        if(next < prev){
            if(std::find(std::begin(trash), std::end(trash), index) == std::end(trash)){
                prev = next;
                extract_min_index = index;
            }
        }
    }

    return extract_min_index;
}

//              Determines if a Value is contained within Priority Queue                                //
bool locate(std::vector<std::pair<int, int>> Q, std::pair<int, int> i){
    //      Compare node values of Q and Graph  //
    for(auto j : Q){
        if(j.first == i.first){
            return true;
        }
    }

    return false;
}

//              Determines Index of Node Value for Q                                                    //
int locate_index(std::vector<std::pair<int, int>> Q, std::pair<int, int> i){
    //      Local Variables                     //
    int index = 0;

    //      Compares Vertices                   //
    for(auto j : Q){
        if(j.first == i.first){
            return index;
        }

        index++;
    }

    return index;
}

//              Returns Left Node Value                                                                 //
int left(int i){
    return 2 * i + 1;
}

//              Returns Right Node Value                                                                //
int right(int i){
    return 2 * i + 2;
}

//              Corrects Single Instance                                                                //
std::vector<std::pair<int, int>> heapify(std::vector<std::pair<int, int>> A, int i, int heapsize){
    //      Local Variables                     //
    int l = left(i);
    int r = right(i);
    int largest = i;

    //      Determines Largest Value            //
    if(l < heapsize && A[l].second > A[largest].second){
        largest = l;
    }
    if(r < heapsize && A[r].second > A[largest].second){
        largest = r;
    }

    //      Swap Values                        //
    if(largest != i){
        std::swap(A[i], A[largest]);
        A = heapify(A, largest, heapsize);
    }

    return A;
}

//              Sorts Heap                                                                               //
std::vector<std::pair<int, int>> heapsort(std::vector<std::pair<int, int>> A, int n){
    //      Builds Heap                       //
    for(int i = n / 2 - 1; i >= 0; i--){
        A = heapify(A, i, n);
    }

    //      Sorts Heap                        //
    for(int i = n - 1; i >= 0; i--){
        std::swap(A[0], A[i]);
        A = heapify(A, 0, i);
    }

    return A;
}

//              Version 1:                                                                              //
// Utilizing adjacency matrix to present graph and unsorted array for priority queue                    //
void prim_alg_v1(int graph[V][V]){
    //      Local Variables                     //
    int u, v, s, index;
    std::vector<int> key;
    std::vector<int> pi[V];
    std::vector<int> Q;
    std::vector<int> trash;
    std::vector<int>::iterator it;

    //      Print Adjacency Matrix              //
    std::cout << "Graph to Adjacency Matrix" << std::endl;
    std::cout << "    ";
    for(u = 0; u < V; u++) {
        std::cout << u << "  ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl;
    for(u = 0; u < V; u++) {
        std::cout << u << "|  ";
        for(v = 0; v < V; v++) {
            std::cout << graph[u][v] << "  ";
        }
        std::cout << std::endl;
    }

    //      Initialize key and Q                //
    for(u = 0; u < V; u++){
        key.push_back(INT_MAX);
        Q.push_back(u);
    }

    //      Randomly Select Node                //
    srand(time(NULL));
    s = rand() % (Q.size() - 1) + 0;
    key[s] = 0;

    //      While priority queue exists         //
    while(Q.size() != 0){
        //      Extract min from Q                  //
        u = extract_min(Q, key, trash);
        trash.push_back(u);
        
        it = std::find(Q.begin(), Q.end(), u);
        index = std::distance(Q.begin(), it);
        Q.erase(Q.begin() + index, Q.begin() + (index + 1));

        //      Compare and replace key values      //
        for(v = 0; v < V; v++){
            if(graph[u][v] > 0 && std::find(std::begin(Q), std::end(Q), v) != std::end(Q) && graph[u][v] < key[v]){
                key[v] = graph[u][v];
                pi[v].push_back(u);
            }
        }
    }

    //      Calculate MST                       //
    int summation = 0;
    std::cout << std::endl << "Key: ";
    for(auto i : key ){
        std::cout << i << "  ";
        summation += i;
    }
    std::cout << std::endl << "MST = " << summation << std::endl;

    return;
}

//              Version 2:                                                                              //
// Utilizng adjacency lists to present graph and heap for priority queue                                //
void prim_alg_v2(std::vector<std::pair<int, int>> graph[]){
    //  Local Variables                     //
    int u, v, s, first_key, first_node, Q_index;
    std::vector<int> key;
    std::vector<int> pi[V];
    std::vector<std::pair<int, int>> Q;

    //  Print Adjacency List                //
    std::cout << "Graph to Adjacency List [(node connection, weight)]" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    for (u = 0; u < V; u++) { 
        std::cout << "A[" << u << "] = {"; 
        for (v = 0; v < graph[u].size(); v++){
            std::cout << " (" << graph[u][v].first << ", " << graph[u][v].second << ") "; 
        }
        std::cout << "}" << std::endl; 
    } 

    //      Initialize key and Q                //
    for(u = 0; u < V; u++){
        key.push_back(INT_MAX);
        Q.push_back(std::make_pair(u, key[u]));
    }

    //      Randomly Select Node                //
    srand(time(NULL));
    s = rand() % (Q.size() - 1) + 0;
    key[s] = 0;
    Q[s].second = 0;

    //      While priority queue exists         //
    while( Q.size() != 0){
        //      Sort Heap                           //
        Q = heapsort(Q, Q.size());

        //      Extract min from Q                  //
        first_node = Q[0].first;
        first_key = Q[0].second;
        Q.erase(Q.begin(), Q.begin() + 1);

        //      Compare and replace key values      //
        for(auto i : graph[first_node]){
            if( locate(Q, i) && i.second < key[i.first]){
                key[i.first] = i.second;
                pi[i.first].push_back(i.first);

                Q_index = locate_index(Q, i);
                Q[Q_index].second = i.second;
            }
        }
    }

    //      Calculate MST                       //
    int summation = 0;
    std::cout << std::endl << "Key: ";
    for(auto i : key ){
        std::cout << i << "  ";
        summation += i;
    }
    std::cout << std::endl << "MST = " << summation << std::endl;

    return;
}

//              Main function                                                                           //
int main(){ 
    //  Local Variables                     //
    int i, j;
    int matrix[V][V];
    std::vector<std::pair<int, int>> list[V]; 

    //  Initialize Matrix                   //
    for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            matrix[i][j] = 0;
        }
    }

    //  Add Points to Graph                 //
    add_point(matrix, list,  0, 1, 6); 
    add_point(matrix, list,  0, 2, 12);
    add_point(matrix, list,  1, 2, 5); 
    add_point(matrix, list,  2, 3, 9); 
    add_point(matrix, list,  1, 4, 14);
    add_point(matrix, list,  1, 7, 8); 
    add_point(matrix, list,  2, 5, 7); 
    add_point(matrix, list,  5, 6, 15);
    add_point(matrix, list,  4, 7, 3); 
    add_point(matrix, list,  5, 7, 10);

    //  Version 1                           //
    std::cout << std::endl;
    std::cout << "  Version 1" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;
    prim_alg_v1(matrix);

    //  Version 2                           //
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  Version 2" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;
    prim_alg_v2(list);

    std::cout << std::endl;

    return 0;
}