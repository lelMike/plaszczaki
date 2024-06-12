#include "GraphHandler.h"

GraphHandler::GraphHandler(const std::string& filename) : startPoint(-1) {
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
            std::string token;
            buffer >> token;

            if (token.empty() || token == "-" || token == " ") {
                readingPoints = false;
                continue;
            }

            if (token[0] == '*') {
                x = std::stof(token.substr(1));
                buffer >> y;
                startPoint = pointId;
            } else {
                x = std::stof(token);
                buffer >> y;
            }

            points.emplace(pointId, Point{x, y});
            pointId++;
        } else {
            int id1, id2;
            float maxFlow;
            if (buffer >> id1 >> id2 >> maxFlow) {
                graph[id1].emplace_back(Edge{id1, id2, maxFlow, 0.0f});
                graph[id2].emplace_back(Edge{id2, id1, maxFlow, 0.0f});
            }
        }
    }

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
        for (const auto& edge : node.second) {
            std::cout << "Point " << edge.node2 << " (max flow: " << edge.maxFlow << ") ";
        }
        std::cout << std::endl;
    }
}

float GraphHandler::calculateMaxFlow(int workers, bool debug) {
    if (startPoint == -1 || borderHandler.getEdgePoints().empty()) return 0;

    float totalMaxFlow = 0;
    std::vector<int> parent(points.size() + 2);  // +2 for virtual sink

    // Starting point
    float startX = points[startPoint].x;
    float startY = points[startPoint].y;

    int virtualSink = points.size() + 1;

    // Infinite capacity for the virtualSink
    for (const Point& edgePoint : borderHandler.getEdgePoints()) {
        int edgePointId = -1;
        for (const auto& point : points) {
            if (point.second == edgePoint) {
                edgePointId = point.first;
                break;
            }
        }

        if (edgePointId != -1) {
            graph[edgePointId].emplace_back(Edge{edgePointId, virtualSink, std::numeric_limits<float>::max(), 0.0f});
            graph[virtualSink].emplace_back(Edge{virtualSink, edgePointId, 0, 0.0f});
        }
    }

    // Reset current flow
    for (auto& nodeEdges : graph) {
        for (auto& edge : nodeEdges.second) {
            edge.currentFlow = 0.0f;
        }
    }

    while (findAugmentingPath(startPoint, virtualSink, parent)) {
        float pathFlow = std::numeric_limits<float>::max();
        std::vector<int> path;
        for (int v = virtualSink; v != startPoint; v = parent[v]) {
            int u = parent[v];
            path.push_back(v);
            for (const auto& edge : graph[u]) {
                if (edge.node2 == v) {
                    pathFlow = std::min(pathFlow, edge.maxFlow - edge.currentFlow);
                    break;
                }
            }
        }
        path.push_back(startPoint);
        std::reverse(path.begin(), path.end());

        if (debug) {
            std::cout << "Start point: (" << startX << ", " << startY << ")" << std::endl;

            std::cout << "Augmenting path: ";
            for (int node : path) {
                const Point& point = points[node];
                std::cout << node << " (" << point.x << ", " << point.y << ") ";
            }
            std::cout << "with flow: " << pathFlow << std::endl;
        }

        for (int v = virtualSink; v != startPoint; v = parent[v]) {
            int u = parent[v];
            for (auto& edge : graph[u]) {
                if (edge.node2 == v) {
                    edge.currentFlow += pathFlow;
                    break;
                }
            }
            for (auto& edge : graph[v]) {
                if (edge.node2 == u) {
                    edge.currentFlow -= pathFlow;
                    break;
                }
            }
        }

        totalMaxFlow += pathFlow;
    }

    return std::min(totalMaxFlow, static_cast<float>(workers));
}

bool GraphHandler::findAugmentingPath(int source, int sink, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    std::vector<bool> visited(points.size() + 2, false);
    std::vector<int> stack = {source};
    visited[source] = true;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        for (const auto& edge : graph[u]) {
            int v = edge.node2;
            if (!visited[v] && edge.currentFlow < edge.maxFlow) {
                parent[v] = u;
                if (v == sink) {
                    return true;
                }
                stack.push_back(v);
                visited[v] = true;
            }
        }
    }

    return false;
}
