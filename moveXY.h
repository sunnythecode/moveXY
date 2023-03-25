#include <iostream>


class moveXY {
    public:
    struct Point {
        double x;
        double y;
    };

    int getQuadrant(Point pt);

    std::vector<Point> cull_elbow();



};