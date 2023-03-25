#include "moveXY.h"
#include <iostream>

int main()
{
    std::cout << "hello world";

    moveXY foo = moveXY(0, 0, 0, 0);
    moveXY::Point target{4, 5};
    moveXY::Point p1{0, 0};
    moveXY::Point p2{0, 0};
    int x = foo.getCircleInts(5, 6, target, p1, p2);

    std::cout << "Num Sol" << x << std::endl;
    std::cout << p1.x << ", " << p1.y;
    std::cout << p2.x << ", " << p2.y;
}
