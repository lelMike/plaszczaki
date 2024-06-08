#include "BorderHandler.h"

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
        p = q;

        if (p == leftPoint) {
            break;
        }
    }
}

void BorderHandler::printResult() const {
    for (const auto& a : edgePoints) {
        std::cout << "point: " << a.x << " " << a.y << std::endl;
    }
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
