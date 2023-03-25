#include "moveXY.h"
#include <iostream>

int main()
{
    std::cout << "hello world" << std::endl;
    moveXY foo(20.0f, 30.0f, 22.5f, 34.3f);

    moveXY::Point target{4, 5};
    moveXY::Point p1{0, 0};
    moveXY::Point p2{0, 0};
    int x = foo.getCircleInts(5, 6, target, p1, p2);

    std::cout << "Num Sol: " << x << std::endl;
    std::cout << p1.x << ", " << p1.y << std::endl;
    std::cout << p2.x << ", " << p2.y << std::endl;
}
