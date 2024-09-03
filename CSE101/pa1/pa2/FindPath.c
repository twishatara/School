#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define LEN 500

int main(int argc, char* argv[]){
    int size = 0;
    int counter = 0;
    FILE *in = fopen(argv[1], "r"); // open infile
    FILE *out = fo:wqpen(argv[2], "w"); // open outfile
    char buf[500];
    if (argc != 3) { // specify 3 command line args (infile and outfile needed)
        printf("User input error: please specify an input and output file\n";
        exit(EXIT_FAILURE);
    }
    if (in == NULL || out == NULL) {
        printf("Unable to open infile or outfile\n");
        exit(EXIT_FAILURE);
    }
    //get the verticies for the graph
    fgets(buf, LEN, in); // get the lines from the infile and save in the buffer 
    sscanf(buf, "%d", &size); // read from buf into size

    Graph G = newGraph(size); // make a graph using size
    while (fgets(buf, LEN, in) != NULL) { // read and store the graph and print out its adjacency list representation
        int x = 0;
        int y = 0;
        sscanf(buf,"%d %d",&x, &y); // read from buff into a and b
        if (x == 0 && y == 0) { 
            break; 
        }
        addEdge(G,x,y); // add an edge for a and b into the graph
        printGraph(out,G); // print the graph to out
    }
    while (fgets(buf, LEN, in) != NULL) { // process the second part of the input
        int x = 0;
        int y = 0;
        sscanf(buf, "%d %d", &x, &y); // read in the source and destination
        if (x == 0 && y == 0) {
            break;
        }
        if (counter++ != 0) {
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
        BFS(G, x); // run bfs on the source vertex
        int d = getDist(G, y);
        fprintf(out, "The distance from %d to %d is ", x, y); // print the distance between the source and dest vertex to out
        if (d == INF) {
            fprintf(out, "infinity\n");
        }
        else {
            fprintf(out, "%d\n", d); // print the distance
        }
        List P = newList(); // make a new list
        getPath(P, G, y); // find the shortest path b
        if(front(P) == NIL) // if there is no path
            fprintf(out, "No %d-%d path exists", x, y);
        else { // else print out the path
            fprintf(out, "A shortest %d-%d path is: ", x, y);
            printList(out, P);
        }
        freeList(&P); // free the list
    }  
    fprintf(out, "\n");
    freeGraph(&G); // free the graph
    fclose(in); // close all the files 
    fclose(out);
    return(0);
}