#pragma once
#include <math.h>

struct Vector2D
{
    float x,y = 0;

    void add(Vector2D Vector)
    {
        x += Vector.x;
        y += Vector.y;
    }

    void sub(Vector2D Vector)
    {
        x -= Vector.x;
        y -= Vector.y;
    }

    void multiply(Vector2D Vector)
    {
        x *= Vector.x;
        y *= Vector.y;  
    }

    void divide(Vector2D Vector)
    {
        x /= Vector.x;
        y /= Vector.y;
    }

    float distance(Vector2D Vector)
    {
        return sqrt((x-Vector.x)+(y-Vector.y));
    }
};
