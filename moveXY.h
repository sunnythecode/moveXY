#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class moveXY
{
public:
    struct Point
    {
        double x;
        double y;
        double norm()
        {
            return std::sqrt(x * x + y * y);
        }
        void setCoords(double in_x, double in_y)
        {
            x = in_x;
            y = in_y;
        }
    };

    struct ArmSolution
    {
        double shoulder;
        double elbow;
    };

    Point m_start_xy,
        m_curr_xy;
    ArmSolution m_offset_theta;
    ArmSolution m_curr_theta;

    int getQuadrant(Point pt)
    {
        int res = -1;
        if (pt.x >= 0)
        {
            res = (pt.y >= 0) ? 1 : 4;
        }
        else
        {
            res = (pt.y >= 0) ? 2 : 3;
        }

        return res;
    }
    std::vector<Point> cull_elbow(Point int1, Point int2, int preferredQuadrant)
    {
        std::vector<Point> outputPoints;
        if (getQuadrant(int1) == preferredQuadrant)
        {
            outputPoints.push_back(int1);
        }
        if (getQuadrant(int2) == preferredQuadrant)
        {
            outputPoints.push_back(int2);
        }
        if (outputPoints.size() == 0)
        {
            outputPoints.push_back(int1);
            outputPoints.push_back(int2);
        }
        return outputPoints;
    }

    moveXY(float startX, float startY, float start_angle_offset_shoulder, float start_angle_offset_elbow)
    {
        m_curr_theta.elbow = 360.0f - start_angle_offset_elbow;
        m_curr_theta.shoulder = 360.0f - start_angle_offset_shoulder;
        m_curr_xy.x = m_start_xy.x = startX;
        m_curr_xy.y = m_start_xy.x = startY;
    }

    size_t getCircleInts(float originRadius, float targetRadius, Point target, Point &i1, Point &i2)
    {
        double d = Point{0 - target.x, 0 - target.y}.norm();

        // find number of solutions
        if (d > originRadius + targetRadius) // circles are too far apart, no solution(s)
        {
            return 0;
        }
        else if (d == 0 && originRadius == targetRadius) // circles coincide
        {
            return 0;
        }
        // one circle contains the other
        else if (d + std::min(originRadius, targetRadius) < std::max(originRadius, targetRadius))
        {
            return 0;
        }
        else
        {
            double a = (originRadius * originRadius - targetRadius * targetRadius + d * d) / (2.0 * d);
            double h = std::sqrt(originRadius * originRadius - a * a);

            // find p2
            Point p2{0 + (a * (target.x - 0)) / d, 0 + (a * (target.y - 0)) / d};

            // find intersection points p3
            i1.setCoords(p2.x + (h * (target.y - 0) / d), p2.y - (h * (target.x - 0) / d));
            i2.setCoords(p2.x - (h * (target.y - 0) / d), p2.y + (h * (target.x - 0) / d));

            if (d == originRadius + targetRadius)
                return 1;
            return 2;
        }
    }

    double distanceToElbow(Point currPos, Point targetPos);

    double convertToAdjustedCoordinateSystem(double offset, double start_angle_offset);

    double convertToOriginalCoordinateSystem(double adjustedAngle, double start_angle_offset);
};