#include "Camera.h"

Vector3f UP_VECTOR(0.0f, 1.0f, 0.0f);
Vector3f DOWN_VECTOR(0.0f, -1.0f, 0.0f);

/*
float Dot(Vector3f& vec1, Vector3f& vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

Vector3f Cross(const Vector3f& vec1, const Vector3f& vec2)
{
    return Vector3f(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}

void Cross(Vector3f& vec1, Vector3f& vec2, Vector3f& result)
{
    result.x = vec1.y*vec2.z - vec1.z*vec2.y;
    result.y = vec1.z*vec2.x - vec1.x*vec2.z;
    result.z = vec1.x*vec2.y - vec1.y*vec2.x;
}

Vector3f Cross(Vector3f& vec1, Vector3f& vec2)
{
    return (Vector3f){vec1.y*vec2.z - vec1.z*vec2.y,
                          vec1.z*vec2.x - vec1.x*vec2.z,
                          vec1.x*vec2.y - vec1.y*vec2.x};
}

*/
