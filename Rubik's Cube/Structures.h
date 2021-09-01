#ifndef STRUCTURES_H
#define STRUCTURES_H
typedef struct rgb
{
    float r;
    float g;
    float b;
    bool operator ==(const rgb& other)
    {
        return (r == other.r && g == other.g && b == other.b);
    }
} rgb;

typedef struct Point
{
    float x;
    float y;
    float z;
} Point;

struct NumPlanes
{
    int l = 0, r = 1, f = 2, b = 3, d = 4, u = 5;
} Planes;
#endif
