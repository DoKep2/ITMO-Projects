#ifndef ROTATES_H
#define ROTATES_H
#include "Structures.h"
Point PointRotateX(float x, float y, float z, float oy, float oz, float angle)
{
    Point point;
    point.x = x;
    point.y = (y - oy) * cos(angle) - (z - oz) * sin(angle) + oy;
    point.z = (y - oy) * sin(angle) + (z - oz) * cos(angle) + oz;
    return point;
}

Point PointRotateY(float x, float y, float z, float ox, float oz, float angle)
{
    Point point;
    point.x = (x - ox) * cos(angle) - (z - oz) * sin(angle) + ox;
    point.y = y;
    point.z = (x - ox) * sin(angle) + (z - oz) * cos(angle) + oz;
    return point;
}

Point PointRotateZ(float x, float y, float z, float ox, float oy, float angle)
{
    Point point;
    point.x = (x - ox) * cos(angle) - (y - oy) * sin(angle) + ox;
    point.y = (x - ox) * sin(angle) + (y - oy) * cos(angle) + oy;
    point.z = z;
    return point;
}
#endif
