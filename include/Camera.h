#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "Matrix.h"
#include "Vector3f.h"

extern Vector3f UP_VECTOR;
extern Vector3f DOWN_VECTOR;


float Dot(Vector3f& vec1, Vector3f& vec2);
Vector3f Cross(const Vector3f& vec1, const Vector3f& vec2);
void Cross(Vector3f& vec1, Vector3f& vec2, Vector3f& result);
Vector3f Cross(Vector3f& vec1, Vector3f& vec2);



class Camera
{
    public:
        Camera(Vector3f *position, float *pitch, float *yaw)
        {
            this->position = position;
            this->pitch = pitch;
            this->yaw = yaw;
            setupVectors();
        }

        Vector3f getLookVector()
        {
            return *lookVector;
        }
        Vector3f getUpVector()
        {
            return *upVector;
        }
        Vector3f getRightVector()
        {
            return *rightVector;
        }
        Vector3f getForwardVector()
        {
            return rightVector->Cross(UP_VECTOR);
        }
        void updateMatrix()
        {
            matrix.identity();
            matrix.rotateX(*pitch);
            matrix.rotateY(*yaw);
            matrix.translate(position->x, position->y, position->z);
        }

    private:
        Vector3f *position;
        float *pitch, *yaw;
        Matrix4x4 matrix;
        Vector3f *upVector, *lookVector, *rightVector;

        void setupVectors()
        {
            float (*p)[4] = (float (*)[4])matrix.getMatrixPointer();
            rightVector = (Vector3f *)&p[0];
            upVector    = (Vector3f *)&p[1];
            lookVector  = (Vector3f *)&p[2];
        }
};

#endif
