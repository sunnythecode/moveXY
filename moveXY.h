#include <iostream>

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
};