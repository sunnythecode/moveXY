#include <iostream>
#include <vector>

class moveXY
{
private:
    float m_startX,
        m_startY,
        m_start_angle_offset_shoulder,
        m_start_angle_offset_elbow;

protected:
public:
    struct Point
    {
        double x;
        double y;
    };

    moveXY(float startX, float startY, float start_angle_offset_shoulder, float start_angle_offset_elbow) : m_startX{startX}, m_startY{startY}, m_start_angle_offset_shoulder{start_angle_offset_shoulder}, m_start_angle_offset_elbow{start_angle_offset_elbow}
    {
    }

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
    std::vector<moveXY::Point> cull_elbow(Point int1, Point int2, int preferredQuadrant)
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
        if (outputPoints.size() == 0) {
            outputPoints.push_back(int1);
            outputPoints.push_back(int2);
        }
        return outputPoints;
    }
};