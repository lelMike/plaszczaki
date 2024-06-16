#include "../include/GraphHandler.h"

bool GraphHandler::readInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "There is some issue with file" << std::endl;
        return true;
    }

    std::string line;
    bool readingPoints = true;
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
    return false;
}

void GraphHandler::calculateBorder() {
    borderHandler.calculateBorder();
    borderHandler.exportBorder();
}

void GraphHandler::printBorder() const {
    borderHandler.printResult();
}

void GraphHandler::printGraph(bool GUI) const {
    if (GUI) {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

        sf::Font font;
        if (!font.loadFromFile("fonts/arial.ttf")) { // Ensure the path is correct
            std::cerr << "Error loading font\n";
            return;
        }

        // Getting minimum and maximum coordinates, to get the correct scale and offset
        float minX = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::min();
        float minY = std::numeric_limits<float>::max();
        float maxY = std::numeric_limits<float>::min();

        for (const auto& point : points) {
            minX = std::min(minX, point.second.x);
            maxX = std::max(maxX, point.second.x);
            minY = std::min(minY, point.second.y);
            maxY = std::max(maxY, point.second.y);
        }

        float scaleX = 700.0f / (maxX - minX);
        float scaleY = 500.0f / (maxY - minY);
        float offsetX = 50.0f - minX * scaleX;
        float offsetY = 550.0f + minY * scaleY; // 550 = window height - 50 for margin

        // Calculate the positions for the x and y axis lines
        float xAxisY = offsetY - 0.0f * scaleY;
        float yAxisX = offsetX + 0.0f * scaleX;

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);

            // Draw dotted x axis
            sf::VertexArray xAxis(sf::Lines);
            for (float x = 0; x <= 800; x += 10) {
                xAxis.append(sf::Vertex(sf::Vector2f(x, xAxisY), sf::Color::Black));
                xAxis.append(sf::Vertex(sf::Vector2f(x + 5, xAxisY), sf::Color::Black));
            }
            window.draw(xAxis);

            // Draw dotted y axis
            sf::VertexArray yAxis(sf::Lines);
            for (float y = 0; y <= 600; y += 10) {
                yAxis.append(sf::Vertex(sf::Vector2f(yAxisX, y), sf::Color::Black));
                yAxis.append(sf::Vertex(sf::Vector2f(yAxisX, y + 5), sf::Color::Black));
            }
            window.draw(yAxis);

            // Draw points
            for (const auto& point : points) {
                float x = point.second.x * scaleX + offsetX;
                float y = offsetY - point.second.y * scaleY;

                sf::CircleShape shape(5);
                shape.setPosition(x - 5, y - 5);
                if (point.first == startPoint) {
                    shape.setFillColor(sf::Color::Red);
                } else {
                    shape.setFillColor(sf::Color::Black);
                }
                window.draw(shape);

                sf::Text text;
                text.setFont(font);
                std::ostringstream oss;
                oss << "P" << point.first << "\n"
                    << "x:" << std::fixed << std::setprecision(2) << point.second.x << "\n"
                    << "y:" << std::fixed << std::setprecision(2) << point.second.y;
                text.setString(oss.str());
                text.setCharacterSize(12);
                text.setFillColor(sf::Color::Black);
                text.setPosition(x + 5, y - 15);
                window.draw(text);
            }

            // Draw edges
            for (const auto& node : graph) {
                for (const auto& edge : node.second) {
                    float x1 = points.at(edge.node1).x * scaleX + offsetX;
                    float y1 = offsetY - points.at(edge.node1).y * scaleY;
                    float x2 = points.at(edge.node2).x * scaleX + offsetX;
                    float y2 = offsetY - points.at(edge.node2).y * scaleY;

                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Blue),
                        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Blue)
                    };
                    window.draw(line, 2, sf::Lines);

                    sf::Text flowText;
                    flowText.setFont(font);
                    std::ostringstream oss;
                    oss << std::fixed << std::setprecision(2) << edge.maxFlow;
                    flowText.setString(oss.str());
                    flowText.setCharacterSize(12);
                    flowText.setFillColor(sf::Color::Blue);
                    float midX = (x1 + x2) / 2;
                    float midY = (y1 + y2) / 2;
                    flowText.setPosition(midX + 5, midY + 5);
                    window.draw(flowText);
                }
            }

            // Draw border
            const auto& edgePoints = borderHandler.getEdgePoints();
            for (size_t i = 0; i < edgePoints.size(); ++i) {
                float x1 = edgePoints[i].x * scaleX + offsetX;
                float y1 = offsetY - edgePoints[i].y * scaleY;
                float x2 = edgePoints[(i + 1) % edgePoints.size()].x * scaleX + offsetX;
                float y2 = offsetY - edgePoints[(i + 1) % edgePoints.size()].y * scaleY;

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }

            window.display();
        }
    } else {
        for (const auto& node : graph) {
            std::cout << "Point " << node.first << " connects to: ";
            for (const auto& edge : node.second) {
                std::cout << "Point " << edge.node2 << " (max flow: " << edge.maxFlow << ") ";
            }
            std::cout << std::endl;
        }
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

float GraphHandler::getPerimeter() const {
    return borderHandler.getPerimeter();
}
