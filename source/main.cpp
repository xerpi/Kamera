#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "Camera.h"
#include "Vector3f.h"
#include "Vector2i.h"
#include "Bullet.h"
#include "Utils.h"

#define millis() (times())
#define fabs(x) ((x) > 0 ? (x) : -(x))
#define JOYSTICK_DEADZONE 15
#define SCREEN_W 800
#define SCREEN_H 600

sf::Clock clk;
uint64_t currentTime, lastTime,deltaTime;
unsigned int frame_count;
float fps;

sf::Window *window;
int16_t LjoyX = 0, LjoyY = 0;
int16_t RjoyX = 0, RjoyY = 0;

Weapon weapon;


bool done = false;
bool canFly = true, enableMouse = false;
Vector3f position;
float pitch = 0.0f;
float yaw = 0.0f;
Camera camera(&position, &pitch, &yaw);

bool joyConnected, lastJoyConnected;
sf::Vector2i mousePos1, mousePos2, mouseDelta;
uint8_t mouseButtons;


sf::Image bmp;
GLuint texture;
void initSFML();
bool LoadGLTextures();
bool initGL();
void handleInput();
void initFPS();
void FPS(float *fps_p);

void SetupProjection(void)
{
    glViewport(0,0,SCREEN_W, SCREEN_H);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f,(float)SCREEN_W/(float)SCREEN_H,0.1f,100.0f);
        camera.updateMatrix();
        Vector3f look = camera.getLookVector();
        Vector3f up = camera.getUpVector();
        gluLookAt(position.x, position.y, position.z,
                  position.x + look.x, position.y + look.y, position.z + look.z,
                  up.x, up.y, up.z);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SetupProjection();

    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, texture);
    drawBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


    weapon.updateBullets();
    weapon.drawBullets(texture);

	return true;
}

int main(int argc, char** argv)
{
    initSFML();
    if(not initGL()){printf("InitGL error\n"); return -1;}
    initFPS();
    position.z = -10.0f;
    while (!done)
    {
        handleInput();
        DrawGLScene();

        window->display();

        FPS(&fps);
        printf("FPS: %f\n", fps);
    }
    glDeleteTextures(1, &texture);
    delete window;
    printf("Exited cleanly\n");
    return 0;
}


void handleInput()
{
    mousePos1 = sf::Mouse::getPosition();
    Vector3f right = camera.getRightVector();
    Vector3f look = camera.getLookVector();
    Vector3f forward;
    if(canFly)
        forward = camera.getLookVector();
    else
        forward = camera.getForwardVector();

    joyConnected = sf::Joystick::isConnected(0);
    if(joyConnected)
    {
            LjoyX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            LjoyY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            RjoyX = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
            RjoyY = sf::Joystick::getAxisPosition(0, sf::Joystick::R);

            if(fabs(RjoyX) > JOYSTICK_DEADZONE)
                yaw   -= RjoyX/1500.0f;
            if(fabs(RjoyY) > JOYSTICK_DEADZONE)
                pitch += RjoyY/1500.0f;
            if(fabs(LjoyX) > JOYSTICK_DEADZONE)
                position -= right * (LjoyX/400.0f);
            if(fabs(LjoyY) > JOYSTICK_DEADZONE)
                position -= forward * (LjoyY/400.0f);

            if(sf::Joystick::isButtonPressed(0, 9)) position.y += 0.25f; //R2
            if(sf::Joystick::isButtonPressed(0, 8)) position.y -= 0.25f; //L2

        }
        mouseDelta = mousePos1-mousePos2;
        if(enableMouse)
        {
            pitch += mouseDelta.y/200.0f;
            yaw   -= mouseDelta.x/200.0f;
        }


        if (joyConnected && !lastJoyConnected)
            std::cout << "Joystick connected!" << std::endl;
        if (!joyConnected && lastJoyConnected)
            std::cout << "Joystick disconnected!" << std::endl;

    /************** MOVE PLAYER **************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            position += forward/10.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position -= forward/10.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            position += right/10.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position -= right/10.0f;
     /************** MOVE CAMERA **************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pitch -= 0.05f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            pitch += 0.05f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            yaw -= 0.05f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            yaw += 0.05f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            position.y -= 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            position.y += 0.1f;

        if(pitch > PI_2) pitch -= PI_2;
        if(yaw > PI_2) yaw -= PI_2;
        if(pitch < 0) pitch += PI_2;
        if(yaw < 0) yaw += PI_2;
    /************** SHOOT **************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Joystick::isButtonPressed(0, 11) ||
            (enableMouse && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        {
            Vector3f rot = (Vector3f){RAD_TO_DEG(pitch), RAD_TO_DEG(yaw), 0.0f};
            weapon.addBullet(position, rot, look);
        }

        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    done = true;
                    break;
                case sf::Keyboard::Space:
                    canFly = not canFly;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        printf("JOYSTICK: Left X: %i  Left Y: %i  Right X: %i  Right Y: %i\n", LjoyX, LjoyY, RjoyX, RjoyY);
        printf("pitch: %f  yaw: %f\nposx: %f  posy: %f  posz: %f\n", pitch, yaw, position.x, position.y, position.z);
        printf("lookx: %f  looky: %f  lookz: %f\nrightx: %f  righty: %f  rightz: %f\n\n", look.x, look.y, look.z,
                                                                                       right.x, right.y, right.z);
        lastJoyConnected = joyConnected;
        mousePos2 = mousePos1;
}


bool LoadGLTextures()
{
	GLenum texture_format;
	GLint  nOfColors;
	if (bmp.loadFromFile("data/texture.bmp"))
	{
        texture_format = GL_RGBA;
        nOfColors = 4;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, bmp.getSize().x, bmp.getSize().y, 0,
                      texture_format, GL_UNSIGNED_BYTE, bmp.getPixelsPtr());
        return true;
	}
	return false;
}

bool initGL()
{
	if (!LoadGLTextures())
    {
        printf("Error loading textures\n");
        return false;
    }
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_LIGHT0);								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
	glEnable(GL_LIGHTING);								// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);						// Enable Material Coloring
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return true;										// Initialization Went OK
}


void initSFML()
{
    window = new sf::Window(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML - OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window->setVerticalSyncEnabled(true);
}


void initFPS()
{
    currentTime = clk.getElapsedTime().asMilliseconds();
	lastTime = currentTime;
	frame_count = 0;
}

void FPS(float *fps_p)
{
	frame_count++;
	currentTime = clk.getElapsedTime().asMilliseconds();
	deltaTime = currentTime - lastTime;
	if(deltaTime >= 1000)
	{
		*fps_p = (float)frame_count/(deltaTime/1000.0f);
		frame_count = 0;
		lastTime = clk.getElapsedTime().asMilliseconds();
	}
}
