#include "../include/BorderHandler.h"

void BorderHandler::setPoints(const std::unordered_map<int, Point>& pts) {
    points = &pts;
}

void BorderHandler::calculateBorder() {
    if (!points || points->empty()) return;

    auto leftPoint = points->begin()->second;
    for (const auto& entry : *points) {
        const auto& p = entry.second;
        if (p.x < leftPoint.x || (p.x == leftPoint.x && p.y < leftPoint.y)) {
            leftPoint = p;
        }
    }

    Point q{}, p = leftPoint;
    perimeter = 0.0f;

    while (true) {
        edgePoints.emplace_back(p);
        q = points->begin()->second;
        for (const auto& entry : *points) {
            const auto& r = entry.second;
            int o = isCC(p, q, r);
            if (q == p || o == 2 || (o == 0 && distance(p, r) > distance(p, q))) {
                q = r;
            }
        }
        perimeter += distance(p, q);
        p = q;

        if (p == leftPoint) {
            break;
        }
    }
}

void BorderHandler::exportBorder() const {
    int i = 0;
    std::string filePath = "txt/p3_path1.txt";
    while(std::filesystem::exists(filePath)) {
        i++;
        filePath = "txt/p3_path" + std::to_string(i) + ".txt";
    }
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    file << edgePoints.size() << std::endl;

    for (const auto& a : edgePoints) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 100);
        file << distrib(gen) << " ";
    }
    file.close();
}

void BorderHandler::printResult() const {
    for (const auto& a : edgePoints) {
        std::cout << "point: " << a.x << " " << a.y << std::endl;
    }
}

float BorderHandler::getPerimeter() const {
    return perimeter;
}

std::vector<Point> BorderHandler::getEdgePoints() const {
    return edgePoints;
}

inline float BorderHandler::distance(const Point& p1, const Point& p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

inline int BorderHandler::isCC(const Point& p, const Point& q, const Point& r) {
    float result = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (result == 0) {
        return 0;
    } else if (result > 0) {
        return 1;
    }
    return 2;
}
