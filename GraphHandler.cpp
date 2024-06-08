#include "GraphHandler.h"

GraphHandler::GraphHandler(const std::string& filename) {
    readInput(filename);
}

void GraphHandler::readInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "There is some issue with file" << std::endl;
        return;
    }

    std::string line;
    bool readingPoints = true;  // Needed to check for which part of the input we are in
    int pointId = 1;
    while (std::getline(file, line)) {
        std::stringstream buffer(line);
        if (readingPoints) {
            float x, y;
            if (buffer >> x >> y) {
                points.emplace(pointId, Point{x, y});
                pointId++;
            } else {
                readingPoints = false;
            }
        }
        if (!readingPoints) {
            int id1, id2;
            if (buffer >> id1 >> id2) {
                graph[id1].emplace(id2);
                graph[id2].emplace(id1);
            }
        }
    }

    // To save memory, we pass the points to the borderHandler via reference
    borderHandler.setPoints(points);
}

void GraphHandler::calculateBorder() {
    borderHandler.calculateBorder();
}

void GraphHandler::printBorder() const {
    borderHandler.printResult();
}

void GraphHandler::printGraph() const {
    for (const auto& node : graph) {
        std::cout << "Point " << node.first << " connects to: ";
        for (const auto& neighbor : node.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
