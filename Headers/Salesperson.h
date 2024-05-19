#ifndef HEADERS_SALESPERSON_H
#define HEADERS_SALESPERSON_H

#include "string"
#include "Graph.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <chrono>


using namespace std;

class Salesperson {
private:
    Graph<int> salesperson;
    unordered_map<int,pair<double,double>> nodeMap;
    vector<vector<double>> distMap;
public:
    /**
     * Reads user input to choose which graph to read
     * @param option
     */
    void readGraph(char option);
    /**
     * Reads the real world csv files and creates a graph
     * @param path
     * @param isNode
     */
    void readCSV(const string& path, bool isNode);
    /**
     * Reads user input to choose which toy graph to read
     */
    void readToy();
    /**
     * Reads user input to choose which real world graph to read
     */
    void readRealWorld();
    /**
    * Reads user input to choose which extra fully connected graph to read
    */
    void readExtra();
    /**
     * Reads the toy csv files and creates a graph
     * @param path
     * @param hasName
     */
    void readToyCSV(const string& path, bool hasName);
    /**
     * Reads the extra fully connected files and creates a graph
     * @param path
     * @param lines
     */
    void readExtraCSV(const string& path, int lines);

    /**
     * Builds an MST following Prim's starting at a specific node; MST is stored in the graph using the path field from Vertex.
     * @param root pointer to start node
     * @details Time Complexity: O(V), V being the number vertices
     */
    void primMst(Vertex<int>* root);

    /**
     * Calculates a 2-approximation TSP solution using the triangular inequality property by building an MST and doing a DFS through it.
     * @param time return argument of time taken to process
     * @return pair made up of the path (a vector of pointers to Vertex) and the cost;
     * @details Time Complexity: O(V + E), V being the number of vertices and E the number of edges
     */
    pair<vector<Vertex<int>*>, double> twoApprox(double& time);

    /**
     * Finds a DFS path through the path field of Vertex (used to represent an MST), i.e., builds a pre order of an MST.
     * @param res return argument of DFS
     * @param source start of DFS
     * @details Time Complexity: O(V + E), V being the number of vertices and E the number of edges
     */
    void mstDfs(vector<Vertex<int>*>& res, Vertex<int>* source);

    /**
     * Recursive function that does all the DFS work.
     * @param v
     * @param res cumulative vector storing the DFS path
     * @details Time Complexity: O(V + E), V being the number of vertices and E the number of edges
     */
    void mstDfsVisit(Vertex<int>* v, vector<Vertex<int>*>& res);

    /**
     *
     * @return the graph read
     */
    Graph<int> getGraph();
    /**
     * Calculates the best path and its cost recursively
     * @param curr
     * @param start
     * @param path
     * @param pathCost
     * @param bestPath
     * @param bestCost
     * @details Time complexity: O(V!), V being the number of vertices in the graph
     */
    void tspWork(Vertex<int> *curr, Vertex<int> *start, vector<int> &path, double &pathCost, vector<int> &bestPath,
             double &bestCost);
    /**
     * Calls tspWork and computes the time it takes to return the results
     * @param startVertex
     * @param timeTaken
     * @return a pair with the best path and its cost
     * @details Time complexity: O(V!), V being the number of vertices in the graph
     */
    pair<vector<int>, double> tspBacktracking(Vertex<int> *startVertex, double &timeTaken);

    /**
     * Calculates the distance between 2 points using the haversine formula
     * @param latA
     * @param lonA
     * @param latB
     * @param lonB
     * @return the calculated distance
     */
    double haversineDistance(double latA, double lonA, double latB, double lonB);

    /**
     * Calculates a path from node '0' using the Nearest Neighbour algorithm
     * @param timeTaken
     * @return a pair with the path found and its cost
     * @details Time complexity: O(V^2), being V the number of vertices in the graph
     */
    pair<vector<int>,double> nearestNeighbour(double &timeTaken);

};


#endif //HEADERS_SALESPERSON_H
