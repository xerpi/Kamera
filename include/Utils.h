#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define PI   3.14159265359
#define PI_2 6.28318530718

#define RAD_TO_DEG_VAL (180/PI)
#define DEG_TO_RAD_VAL (PI/180)

#define DEG_TO_RAD(x) (x*DEG_TO_RAD_VAL)
#define RAD_TO_DEG(x) (x*RAD_TO_DEG_VAL)

void drawBox(float x, float y, float z, float rotx, float roty, float rotz, float scalex, float scaley, float scalez);



#endif
