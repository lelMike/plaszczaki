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
#include <SFML/Graphics.hpp>
#include <iomanip>

struct Edge {
    int node1;
    int node2;
    float maxFlow;
    float currentFlow;
};

class GraphHandler {
public:
    bool readInput(const std::string& filename);
    void calculateBorder();
    void printBorder() const;
    void printGraph(bool GUI = false) const;
    float calculateMaxFlow(int workers, bool debug = false);
    [[nodiscard]] float getPerimeter() const;

private:
    std::unordered_map<int, Point> points;
    std::unordered_map<int, std::vector<Edge>> graph;
    BorderHandler borderHandler;
    int startPoint = -1;

    bool findAugmentingPath(int source, int sink, std::vector<int>& parent);
};

#endif // GRAPHHANDLER_H
