#include "MoveXY.h"
#include <iostream>

int main()
{
    std::cout << "hello world" << std::endl;

    constexpr double armLen{22.5};
    constexpr double wristLen{33.4f};
    MoveXY foo(0, 0, armLen, wristLen);

    MoveXY::Point target{-wristLen, -armLen};
    int x = foo.getCircleInts(target);

    std::cout << "Num Sol: " << x << std::endl;
    std::cout << foo.get_theta_shoulder(foo.i1) << ", " << foo.i1.x << " : " << foo.i1.y << std::endl;
    std::cout << foo.get_theta_shoulder(foo.i2) << ", " << foo.i2.x << " : " << foo.i2.y << std::endl;
}
