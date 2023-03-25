#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class MoveXY
{
public:
    class Point
    {
    public:
        double x;
        double y;

        /**
         * @brief Get the magnitude of the vector drawn to this point
         *
         * @return double scalar
         */
        double magnitude()
        {
            return std::sqrt(x * x + y * y);
        }

        /**
         * @brief Get the angle of the vector drawn to this point
         *
         * @return double in degrees
         */
        double get_angle()
        {
            return atan2(y, x) * 180 / 3.1415;
        }

        void setCoords(double in_x, double in_y)
        {
            x = in_x;
            y = in_y;
        }
        void set_mag_angle(double magnitude, double angle)
        {
            y = magnitude * sinf(angle);
            x = magnitude * cosf(angle);
        }
    };

    struct ArmAngles
    {
        double shoulder;
        double elbow;
    };

    Point m_curr_elbow_xy;
    ArmAngles m_offset_theta, m_curr_theta, m_target_theta;
    float m_elbow_len, m_shoulder_len;
    Point i1, i2;

    /**
     * @brief Get the Quadrant object
     *
     * @param pt the input point
     * @return int Quadrant that the point is in
     */
    int getQuadrant(Point pt)
    {
        int res;
        if (pt.x >= 0)
        {
            res = (pt.y >= 0) ? 1 : 4;
        }
        else
        {
            res = (pt.y >= 0) ? 2 : 3;
        }

        return res;
    };

    /**
     * @brief Returns tha magnitude of the vector between the target point and the currently stored elbow point
     *
     * @param targetPos
     * @return double scalar
     */
    double distanceToElbow(Point targetPos)
    {
        return sqrt(((m_curr_elbow_xy.x - targetPos.x) * (m_curr_elbow_xy.x - targetPos.x)) + ((m_curr_elbow_xy.y - targetPos.y) * (m_curr_elbow_xy.y - targetPos.y)));
    };

    double convertToAdjustedCoordinateSystem(double offset, double start_angle_offset)
    {
        return 360 - start_angle_offset + offset;
    };

    double convertToOriginalCoordinateSystem(double adjustedAngle, double start_angle_offset)
    {
        return adjustedAngle + start_angle_offset - 360;
    };

    /**
     * @brief Culls non optimal solutions
     *
     * @param int1 solution 1
     * @param int2 solution 2
     * @param preferredQuadrant preferred quadrant
     * @return Point that is closest to the current elbow position, in the desired quadrant if possible
     */
    Point cull_elbow(Point int1, Point int2, int preferredQuadrant = 0)
    {
        std::vector<Point> outputPoints;
        if (preferredQuadrant != 0)
        {
            if (getQuadrant(int1) == preferredQuadrant)
            {
                outputPoints.push_back(int1);
            }
            if (getQuadrant(int2) == preferredQuadrant)
            {
                outputPoints.push_back(int2);
            }
        }

        if (outputPoints.size() == 0)
        {
            outputPoints.push_back(int1);
            outputPoints.push_back(int2);
        }

        if (outputPoints.size() == 1)
        {
            return outputPoints.at(0);
        }
        else if (distanceToElbow(outputPoints.at(0)) <= distanceToElbow(outputPoints.at(1)))
        {
            return outputPoints.at(0);
        }
        else
        {
            return outputPoints.at(1);
        }
    };

    size_t getCircleInts(Point target)
    {
        double d = Point{0 - target.x, 0 - target.y}.magnitude();

        // find number of solutions
        if (d > m_shoulder_len + m_elbow_len) // circles are too far apart, no solution(s)
        {
            m_target_theta.elbow = 180.0f;
            m_target_theta.shoulder = target.get_angle();

            return 0;
        }
        else if (d == 0 && m_shoulder_len == m_elbow_len) // circles coincide
        {
            return 0;
        }
        // one circle contains the other
        else if (d + std::min(m_shoulder_len, m_elbow_len) < std::max(m_shoulder_len, m_elbow_len))
        {
            return 0;
        }
        else
        {
            double a = (m_shoulder_len * m_shoulder_len - m_elbow_len * m_elbow_len + d * d) / (2.0 * d);
            double h = std::sqrt(m_shoulder_len * m_shoulder_len - a * a);

            // find p2
            Point p2{0 + (a * (target.x - 0)) / d, 0 + (a * (target.y - 0)) / d};

            // find intersection points p3
            i1.setCoords(p2.x + (h * (target.y - 0) / d), p2.y - (h * (target.x - 0) / d));
            i2.setCoords(p2.x - (h * (target.y - 0) / d), p2.y + (h * (target.x - 0) / d));

            if (d == m_shoulder_len + m_elbow_len)
                return 1;
            return 2;
        }
    };

    /**
     * @brief Get the theta that the shoulder would have to be commanded to reach the desired target.
     *
     * @param targetXY
     * @return double degrees in robot oriented coordinate system
     */
    double get_theta_shoulder(Point targetXY)
    {
        int quadrant = getQuadrant(targetXY);
        double angle = targetXY.get_angle() + 90.0f;

        if (angle > 360.0f)
            return angle - 360.0f;
        else
            return angle;
    };

    /**
     * @brief Get the theta that the elbow would have to be commanded to reach the desired target given a shoulder position
     *
     * @param shoulderXY
     * @param targetXY
     * @return double degrees in degrees in robot oriented coordinate system for the elbow
     */
    double get_theta_elbow(Point shoulderXY, Point targetXY)
    {
        Point delta{targetXY.x - shoulderXY.x, targetXY.y - shoulderXY.y};
        double res = delta.get_angle() + 90.0f + get_theta_shoulder(shoulderXY);
        if (res > 360.0f)
            res -= 360.0f;
        return res;
    }

    /**
     * @brief Calculate the optimal solution to travel to the target XY,
     * while trying to put the elbow in the desired quadrant. The results are stored in m_target_theta
     *
     * @param target target point
     * @param quadrant requested quadrant for elbow
     */
    void calc_solution_to_target(Point target, int quadrant = 1)
    {
        getCircleInts(target);
        Point res = cull_elbow(i1, i2, quadrant);
        m_target_theta.shoulder = get_theta_shoulder(res);
        m_target_theta.elbow = get_theta_elbow(res, target);
    }

    MoveXY(float start_angle_offset_shoulder, float start_angle_offset_elbow, float shoulder_len, float elbow_len)
    {
        m_curr_theta.elbow = 360.0f - start_angle_offset_elbow;
        m_curr_theta.shoulder = 360.0f - start_angle_offset_shoulder;

        m_offset_theta.shoulder = start_angle_offset_shoulder;
        m_offset_theta.elbow = start_angle_offset_elbow;

        m_shoulder_len = shoulder_len;
        m_elbow_len = elbow_len;
    }
};