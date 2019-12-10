//  Dijkstra's Algorithm        //
//  8 December 2019             //
//  Author: Anna DeVries        //

/*      Libraries                       */
#include <iostream> 
#include <stdlib.h> 
#include <vector>
#include <bits/stdc++.h>
#include <limits>
#include <stdio.h>

/*      Struct objects                  */
//  Edge object 
struct Edge {
	int src;
	int dst;
	int weight;

	Edge(int s, int d, int w) : src(s), dst(d), weight(w) {};
};

//  Graph object
struct Graph {
    int V;
    int E;
    std::vector<Edge> edges;

    Graph(int v) : V(v) {
        E = 0;
        edges = std::vector<Edge>();
    }
};

/*      Graph functions                 */
//  Add edge to graph
void addEdge(Graph* graph, int src, int dst, int weight){
    graph->edges.push_back(Edge(src, dst, weight));
    graph->E++;
}

/*      Utility functions               */
//  Print edges
void printAdjList(Graph graph){
    std::cout << "Active Edges" << std::endl;
    std::cout << "------------" << std::endl;
    //  Print each node and its destinations
    for(int i = 0; i < graph.E; i++){
        std::cout << "{" << i << ": " << graph.edges[i].src;
        std::cout << ", " << graph.edges[i].dst << ", ";
        std::cout << graph.edges[i].weight << "}" << std::endl;
    }
    std::cout << std::endl;
}

//  Extracts minumum element from queue
int extract_min(std::vector<int> d, std::vector<bool> q){
    //  Local variables
    int min = INT_MAX;
    int index = 0;

    //  Finds first unvisted element
    for(int i = 0; i < q.size(); i++){
        if (!q[i]){
            index = i;
            min = d[i];
            break;
        }
    }

    //  Finds min element
    for(int i = 0; i < d.size(); i++){
        if(d[i] < min && !q[i]){
            index = i;
            min = d[i];
        }
    }

    //  Returns min element's node
    return index;
}

/*      Dijkstra's Algorithm        */
void dijkstra(Graph graph, int startPoint){
    //  Local variables
    std::vector<int> d;
	std::vector<int> parents;

	//  Start INITIALIZE-SINGLE-SOURCE
	for (int i = 0; i < graph.V; i++) {
		d.push_back(INT_MAX);
		parents.push_back(-1);
	}

	d[startPoint] = 0;
	parents[startPoint] = 0;
	//  End INITIALIZE-SINGLE-SOURCE

    //  Initialize priority Q
    std::vector<bool> Q;
	for (int i = 0; i < graph.V; i++) {
		Q.push_back(false);
	}

    for(int i = 0; i < graph.V; i++){
        int u = extract_min(d, Q);
        Q[u] = true; // Extract min element from Q

        for(auto edge : graph.edges){
            //  Start RELAX FUNCTION
            if(edge.src == u){
                if(!Q[edge.dst] && d[edge.dst] > d[u]+edge.weight){
                    d[edge.dst] = d[u] + edge.weight;
                    parents[edge.dst] = u;
                }
            }
            //  End RELAX FUNCTION
        }
    }

    //  Print results
    printf("\nDijsktra's Algorithm Results\n");
	printf("----------------------------\n");
	std::cout << "Node\tParent\tDistance" << std::endl;
	for (int i = 0; i < graph.V; i++) {
		if (parents[i] < 0) {
			std::cout << i << "\t\t" << d[i] << std::endl;
		}
		else {
			printf("%d\t%d\t%d\n", i, parents[i], d[i]);
		}
	}
}

/*      Main Function       */
int main(){
    //  Local variables
    int src = 0;
    int V = 5;
    Graph graph = Graph(V);

    //  Add edges to graph
    addEdge(&graph, 0, 1, 10);
    addEdge(&graph, 0, 2, 5);
    addEdge(&graph, 1, 2, 2);
    addEdge(&graph, 1, 3, 1);
    addEdge(&graph, 2, 3, 9);
    addEdge(&graph, 2, 1, 3);
    addEdge(&graph, 2, 4, 2);
    addEdge(&graph, 3, 4, 4);
    addEdge(&graph, 4, 3, 6);
    addEdge(&graph, 4, 0, 7);

    //  Print edges of graph
    printAdjList(graph);

    //  Perform shortest path algorithm
    dijkstra(graph, src);
}

