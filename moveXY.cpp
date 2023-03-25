#include "moveXY.h"


int moveXY::getQuadrant(Point pt) {
    int res = -1;
    if (pt.x >= 0) 
    {
        res = (pt.y >= 0) ? 1:4;
    } 
    else 
    {
        res = (pt.y>=0) ? 2:3;
    }

    return res;
}

double moveXY::distanceToElbow(Point currPos, Point targetPos) {
    return sqrt(((currPos.x - targetPos.x) * (currPos.x - targetPos.x)) + ((currPos.y - targetPos.y) * (currPos.y - targetPos.y)));
}


std::vector<moveXY::Point> moveXY::cull_elbow() {
    
    

}