#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Vector3f.h"
#include "Utils.h"

#define BULLET_STEP_INC 0.1f

enum BulletStatus
{
    DEAD = 0,
    ALIVE = 1
};

class Bullet
{

public:
    Vector3f  position, rotation, speed;
    BulletStatus status;
    float step;


    Bullet(Vector3f _position, Vector3f _rotation, Vector3f _speed) : position(_position),
                                                                      rotation(_rotation),
                                                                      speed(_speed)
                                                                      {status = ALIVE;}
    Bullet(float posx, float posy, float posz, Vector3f _rotation, Vector3f _speed) : speed(_speed),
                                                                                      rotation(_rotation)
    {
        position.x = posx;
        position.y = posy;
        position.z = posz;
        status = ALIVE;
        step = 0.0f;
    }

    void move()
    {
        position += speed;
        step += BULLET_STEP_INC;
        position.y += sinf(step)/5.0f;
    }

    void kill()
    {
        status = DEAD;
    }

    void setSpeed(float _speed)
    {
        speed.x=_speed;
        speed.y=_speed;
        speed.z=_speed;
    }
    void draw()
    {
        drawBox(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, 0.05f, 0.05f, 0.1f);
       // printf("posx: %f  posy: %f  posz: %f\n", position.x, position.y, position.z);
    }

};

class Weapon
{
public:
    Weapon(){};

    void addBullet(Vector3f _position, Vector3f _rotation, Vector3f _speed)
    {
        bulletVector.push_back(Bullet(_position, _rotation, _speed));
    }

    void addBullet(float posx, float posy, float posz,Vector3f _rotation, Vector3f _speed)
    {
        bulletVector.push_back(Bullet(posx, posy, posz, _rotation, _speed));
    }

    void updateBullets()
    {
        std::vector<Bullet>::iterator it;
        for(it = bulletVector.begin(); it != bulletVector.end(); it++)
        {
            if(it->status == DEAD)
                bulletVector.erase(it);
            else
                it->move();
        }
    }

    void drawBullets(GLuint texture)
    {
        printf("n bullets: %i\n", bulletVector.size());
        std::vector<Bullet>::iterator it;
        for(it = bulletVector.begin(); it != bulletVector.end(); it++)
        {
            glLoadIdentity();
            glBindTexture(GL_TEXTURE_2D, texture);
            it->draw();
        }
    }

private:
    std::vector<Bullet> bulletVector;
};

#endif
