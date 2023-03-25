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

std::vector<moveXY::Point> moveXY::cull_elbow() {
    
    

}