#include "MoveXY.h"
#include <iostream>

int main()
{
    std::cout << "hello world" << std::endl;

    constexpr double armLen{22.5};
    constexpr double wristLen{33.4f};
    MoveXY foo(0, 0, armLen, wristLen);

    MoveXY::Point target{16, 16};
    int x = foo.getCircleInts(target);

    std::cout << "Num Sol: " << x << std::endl;

    foo.m_curr_elbow_xy.x = 20;
    foo.m_curr_elbow_xy.y = 20;

    foo.calc_solution_to_target(target);

    std::cout << "sol 1: " << foo.get_theta_shoulder(foo.i1) << ", " << foo.i1.x << " : " << foo.i1.y << " elbow:" << foo.get_theta_elbow(foo.i1, target) << std::endl;
    std::cout << "sol 2:" << foo.get_theta_shoulder(foo.i2) << ", " << foo.i2.x << " : " << foo.i2.y << " elbow:" << foo.get_theta_elbow(foo.i2, target) << std::endl;
    std::cout << "pick : " << foo.m_target_theta.shoulder << " elbow:" << foo.m_target_theta.elbow << std::endl;
    return 1;
};
