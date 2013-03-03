#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_


class Vector3f
{
    public:
        Vector3f() {setZero();}
        Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

        Vector3f operator+(Vector3f v) const
        {
            return Vector3f(x + v.getX(), y + v.getY(), z + v.getZ());
        }

        Vector3f operator-(Vector3f v) const
        {
            return Vector3f(x - v.getX(), y - v.getY(), z - v.getZ());
        }

        Vector3f operator-() const
        {
            return Vector3f(-x, -y, -z);
        }

        void operator-=(Vector3f v)
        {
            x -= v.getX();
            y -= v.getY();
            z -= v.getZ();
        }

        void operator+=(Vector3f v)
        {
            x += v.getX();
            y += v.getY();
            z += v.getZ();
        }

        Vector3f operator*(float n) const
        {
            return Vector3f(x*n, y*n, z*n);
        }

        Vector3f operator/(float n)
        {
            return Vector3f(x/n, y/n, z/n);
        }

        float Dot(Vector3f& vec2)
        {
            return x*vec2.x + y*vec2.y + z*vec2.z;
        }

        Vector3f Cross(const Vector3f& vec2)
        {
            return Vector3f(y*vec2.z - z*vec2.y,
                            z*vec2.x - x*vec2.z,
                            x*vec2.y - y*vec2.x);
        }

        void doCross(Vector3f& vec2)
        {
            Vector3f tmp = *this;
            tmp.x = y*vec2.z - z*vec2.y;
            tmp.y = z*vec2.x - x*vec2.z;
            tmp.z = x*vec2.y - y*vec2.x;
            *this = tmp;
        }

        float getX() {return x;}
        float getY() {return y;}
        float getZ() {return z;}

       void setZero()
       {
            x = 0.0f; y = 0.0f; z = 0.0f;
       }
    //private:
        float x, y, z;
};

#endif
