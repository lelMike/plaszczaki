#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "BorderHandler.h"


class GraphHandler {
public:
    explicit GraphHandler(const std::string& filename);
    void readInput(const std::string& filename);
    void calculateBorder();
    void printBorder() const;
    void printGraph() const;

private:
    std::unordered_map<int, Point> points;
    std::unordered_map<int, std::unordered_set<int>> graph;
    BorderHandler borderHandler;
};

#endif // GRAPHHANDLER_H
