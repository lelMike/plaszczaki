#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <limits>
#include <algorithm>
#include "BorderHandler.h"

struct Edge {
    int node1;
    int node2;
    float maxFlow;
    float currentFlow;
};

class GraphHandler {
public:
    explicit GraphHandler(const std::string& filename);
    void readInput(const std::string& filename);
    void calculateBorder();
    void printBorder() const;
    void printGraph() const;
    float calculateMaxFlow(int workers, bool debug = false);

private:
    std::unordered_map<int, Point> points;
    std::unordered_map<int, std::vector<Edge>> graph;
    BorderHandler borderHandler;
    int startPoint;

    bool findAugmentingPath(int source, int sink, std::vector<int>& parent);
};

#endif // GRAPHHANDLER_H
