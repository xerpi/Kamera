#ifndef _Vector2i_H_
#define _Vector2i_H_

#include <stdio.h>
#include <math.h>
#include <string.h>

class Vector2i
{
    public:
        Vector2i() {setZero();}
        Vector2i(float _x, float _y) : x(_x), y(_y) {}

        Vector2i operator+(Vector2i& v)
        {
            return Vector2i(x + v.getX(), y + v.getY());
        }

        Vector2i operator-(Vector2i& v)
        {
            return Vector2i(x - v.getX(), y - v.getY());
        }

        void operator-=(Vector2i v)
        {
            x -= v.getX();
            y -= v.getY();
        }

        void operator+=(Vector2i v)
        {
            x += v.getX();
            y += v.getY();
        }

        Vector2i operator*(float n)
        {
            return Vector2i(x*n, y*n);
        }


        float Dot(Vector2i& vec2)
        {
            return x*vec2.x + y*vec2.y;
        }

        int getX() {return x;}
        int getY() {return y;}

       void setZero()
       {
            x = 0.0f; y = 0.0f;
       }
    //private:
        int x, y;
};

#endif
