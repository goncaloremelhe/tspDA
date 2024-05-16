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
public:
    void readGraph(char option);
    void readCSV(const string& path, bool isNode);
    void readToy();
    void readRealWorld();
    void readExtra();
    void readToyCSV(const string& path, bool hasName);
    void readExtraCSV(const string& path, int lines);
    Graph<int> getGraph();

    void completeGraph();
    double otherHeuristicFast(int n, double &timetaken);
    double haversineDistance(double latA, double lonA, double latB, double lonB);
    void tspWork(Vertex<int> *curr, Vertex<int> *start, vector<int> &path, double &pathCost, vector<int> &bestPath, double &bestCost);

    pair<vector<int>, double> tspBacktracking(Vertex<int> *startVertex, double &timeTaken);

};


#endif //HEADERS_SALESPERSON_H
