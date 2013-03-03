#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>
#include <string.h>

class Matrix4x4
{
    public:
        Matrix4x4()
        {
            identity();
        }

        void identity()
        {
            float *p = (float *)matrix;
            p[0]  =  p[5] =  p[10] = p[15] = 1.0;
            p[1]  =  p[2] =  p[3]  =  p[4] = 0.0;
            p[6]  =  p[7] =  p[8]  =  p[9] = 0.0;
            p[11] = p[12] = p[13]  = p[14] = 0.0;
        }

        void copy(Matrix4x4 &dst)
        {
            memcpy(dst.getMatrixPointer(), getMatrixPointer(), sizeof(float) * 16);
        }
        void copy(Matrix4x4 *dst)
        {
            memcpy(dst->getMatrixPointer(), getMatrixPointer(), sizeof(float) * 16);
        }


        float *getMatrixPointer()
        {
            return (float *)matrix;
        }

        void multiply(Matrix4x4 &mtx, Matrix4x4 &dst)
        {
            float (*dest)[4] = (float (*)[4])dst.getMatrixPointer();
            float (*m1)[4]   = (float (*)[4])getMatrixPointer();
            float (*m2)[4]   = (float (*)[4])mtx.getMatrixPointer();
            dest[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0];
            dest[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1];
            dest[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2];
            dest[0][3] = m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3];

            dest[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0];
            dest[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1];
            dest[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2];
            dest[1][3] = m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3];

            dest[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0];
            dest[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1];
            dest[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2];
            dest[2][3] = m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3];

            dest[3][0] = m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0];
            dest[3][1] = m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1];
            dest[3][2] = m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2];
            dest[3][3] = m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3];
        }

        //Set matrix rotation X
            void setRotationX(float angle)
            {
                float s = sinf(angle);
                float c = cosf(angle);

                matrix[1][1] = c;
                matrix[1][2] = s;

                matrix[2][1] = -s;
                matrix[2][2] = c;
            }

        //Set matrix rotation Y
            void setRotationY(float angle)
            {
                float s = sinf(angle);
                float c = cosf(angle);

                matrix[0][0] = c;
                matrix[0][2] = -s;

                matrix[2][0] = s;
                matrix[2][2] = c;
            }

        //Set matrix rotation Z
            void setRotationZ(float angle)
            {
                float s = sinf(angle);
                float c = cosf(angle);

                matrix[0][0] = c;
                matrix[0][1] = -s;

                matrix[1][0] = s;
                matrix[1][1] = c;
            }

        void translate(float x, float y, float z)
        {
            matrix[0][3] = matrix[0][0]*x + matrix[0][1]*y + matrix[0][2]*z;
            matrix[1][3] = matrix[1][0]*x + matrix[1][1]*y + matrix[1][2]*z;
            matrix[2][3] = matrix[2][0]*x + matrix[2][1]*y + matrix[2][2]*z;
        }

     //Rotate this matrix around X axis
        void rotateX(float angle)
        {
            Matrix4x4 rotated, tmp;
            rotated.setRotationX(angle);
            multiply(rotated, tmp);  // tmp = this * rotated
            tmp.copy(this);  //this = tmp
        }

    //Rotate this matrix around Y axis
        void rotateY(float angle)
        {
            Matrix4x4 rotated, tmp;
            rotated.setRotationY(angle);
            multiply(rotated, tmp);  // tmp = this * rotated
            tmp.copy(this);  //this = tmp
        }

    //Rotate this matrix around Z axis
        void rotateZ(float angle)
        {
            Matrix4x4 rotated, tmp;
            rotated.setRotationZ(angle);
            multiply(rotated, tmp); // tmp = this * rotated
            tmp.copy(this); //this = tmp
        }

    private:
        float matrix[4][4];
};

#endif
