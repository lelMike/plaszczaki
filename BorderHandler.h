#ifndef BORDERHANDLER_H
#define BORDERHANDLER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

struct Point {  // aka node
    float x;
    float y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

class BorderHandler {
public:
    BorderHandler() = default;
    void setPoints(const std::unordered_map<int, Point>& pts);
    void calculateBorder();
    void printResult() const;

private:
    [[nodiscard]] static float distance(const Point& p1, const Point& p2);
    [[nodiscard]] static int isCC(const Point& p, const Point& q, const Point& r);

    const std::unordered_map<int, Point>* points = nullptr;
    std::vector<Point> edgePoints;
};

#endif // BORDERHANDLER_H
