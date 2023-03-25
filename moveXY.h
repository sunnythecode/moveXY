#include <iostream>
#include <vector>

class moveXY
{
private:
    struct Point
    {
        double x;
        double y;
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

protected:
public:
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
};