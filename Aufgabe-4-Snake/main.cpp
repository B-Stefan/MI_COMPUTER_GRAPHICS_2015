#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>


#include "../_lib/vec3.hpp"
#include "../_lib/utils.h"
#include "Sphere.h"
#include "Playground.h"
#include "Snake.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include "Point.h"
#include "Game.h"
#include "SnakeHeadObject.h"
#include "ScorePrinter.h"
#include <unistd.h>

using namespace std;
//Setup
bool useGlFrustrum = false;
bool useTwoGameMode = false;

//Setup view prot
static double window_width_ = 1024;
static double window_height_ = 768;

//Fix for retina / no-retina screen sizes
static int widhtActual = 0;
static int heightActual = 0;


//Values for Key-Input
//Rotation
double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;

//Translation
double translateX = 0;
double translateY = 0;
double translateZ = 0;

//Mouse position
double previewX = 0;
double previewYOffset = 0;
double previewY = 0;

//Zooom
double zoomValue = 1;


//Create objects
Point *origin = new Point(new Vec3(0, 2, 0)); //From this point all objects drawn to canvas
Game *game = new Game(origin); // Create a new snake game
Game *secenodGame = new Game(origin); // Create the second snake game.
Cuboid *cuboid = new Cuboid(3,3,origin);
Rectangle *rectangle = new Rectangle(3,3,origin);
bool mouseClicked = false;


//Method which listen to defined keys on Keybord with glfw_action (key == GLFW_KEY_W && action == GLFW_REPEAT)
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if (action == GLFW_REPEAT || action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_1:
                std::cout << "1 player mode " << std::endl;
                useTwoGameMode = false;
                break;
            case GLFW_KEY_2:
                std::cout << "2 player mode " << std::endl;
                useTwoGameMode = true;
                break;
            case GLFW_KEY_W:
                std::cout << "w" << std::endl;
                rotateX = 1;
                break;
            case GLFW_KEY_A:
                std::cout << "a" << std::endl;
                rotateY = rotateY + 0.2;
                break;
            case GLFW_KEY_S:
                std::cout << "s" << std::endl;
                rotateX = -1;
                break;
            case GLFW_KEY_D:
                std::cout << "d" << std::endl;
                rotateY = rotateY - 0.2;
                break;
            case GLFW_KEY_UP:
                std::cout << "up" << std::endl;
                translateY += 0.2;
                break;
            case GLFW_KEY_LEFT:
                std::cout << "left" << std::endl;
                translateX += 0.2;;
                break;
            case GLFW_KEY_DOWN:
                std::cout << "down" << std::endl;
                translateY -= 0.2;
                break;
            case GLFW_KEY_RIGHT:
                std::cout << "right" << std::endl;
                translateX -= 0.2;;
                break;
            case GLFW_KEY_RIGHT_BRACKET:
                std::cout << "zoom +" << std::endl;
                zoomValue += 0.2;
                break;
            case GLFW_KEY_SLASH:
                std::cout << "zoom -" << std::endl;
                zoomValue -= 0.2;
                break;

            case GLFW_KEY_SPACE:
                std::cout << "spalce " << std::endl;
                game->start();
                secenodGame->start();
                break;

            case GLFW_KEY_P:
                std::cout << "ZOOM ++" << std::endl;
                zoomValue += 1;
                break;

            case GLFW_KEY_L:
                std::cout << "ZOOM --" << std::endl;
                zoomValue -= 1;
                break;
        }
    } else if (action == GLFW_RELEASE) {
        //rotateX = 0;
        //rotateY = 0;
        //rotateZ = 0;
        //mouseClicked = false;

    }


}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        mouseClicked = true;
        std::cout << "ds" << std::endl;
    } else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        mouseClicked = false;
    }
}

void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

    if (previewYOffset < yoffset) {
        std::cout << "zoom in" << std::endl;
        zoomValue += 0.02;
    } else {
        std::cout << "zoom out" << std::endl;
        zoomValue -= 0.02;
    }
    previewYOffset = yoffset;
}


void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {

    glfwGetCursorPos(window, &xpos, &ypos);

    if (previewX > xpos && mouseClicked) {
        zoomValue += 0.02;
    } else if (previewX < xpos && mouseClicked) {
        zoomValue -= 0.02;
    }
    previewX = xpos;

}


// set viewport transformations and draw objects
void InitLighting() {
    GLfloat lp1[4] = {10, 5, 10, 0};
    GLfloat lp2[4] = {-5, 15, -10, 0};
    GLfloat red[4] = {1.0, .8, .8, 1};
    GLfloat blue[4] = {.8, .8, 1.0, 1};

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT1, GL_POSITION, lp1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_POSITION, lp2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
    glEnable(GL_LIGHT2);

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    int width = window_width_;
    int height = window_height_;

    //If retina
    if (widhtActual == 2048 && heightActual == 1536) {
        width = window_width_ * 2;
        height = window_height_ * 2;
    }

    if (useGlFrustrum == false) {


        // init viewport to canvassize
        glViewport(0, 0, width, height);


        // init coordinate system
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-15, 15, -10, 10, -20, 20);
        glOrtho(-15 + zoomValue, 15 -zoomValue, -10 + zoomValue, 10 - zoomValue, -20 , 20);


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else {

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glLoadIdentity();             /* clear the matrix */
        /* viewing transformation  */
        //gluLookAt (0.0, 0.0, 15, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0);
        glScalef(1.0, 1.0, 1.0);      /* modeling transformation */
        //glutWireCube (1.0);
        glFlush();


        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 20.0);
        glMatrixMode(GL_MODELVIEW);
    }


}
void zoomOut(double targetValue){
    double delta = fabs((targetValue-zoomValue)) * 0.02;
    if(delta < 0.01){
        delta = 0;
    }
    zoomValue =  zoomValue - delta;
}
void zoomIn(double targetValue){
    double delta = fabs((targetValue-zoomValue)) * 0.02;
    if(delta < 0.01){
        delta = 0;
    }
    zoomValue =  zoomValue + delta;
}
int main() {
    GLFWwindow *window = NULL;

    printf("Here we go!\n");

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(window_width_, window_height_, "Snake 3D", NULL, NULL);

    glfwGetFramebufferSize(window, &widhtActual, &heightActual);


    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    while (!glfwWindowShouldClose(window)) {

        Point::currentLoopNumber++;
        //Method that ask the key_callback method for Key inputs
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_pos_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetScrollCallback(window, mouse_scroll_callback);

        // switch on lighting (or you don't see anything)
        InitLighting();
        // set background color
        glClearColor(0.8, 0.8, 0.8, 1.0);
        //glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_NORMALIZE);
        glRotated(45, 1, 0, 0);
        glRotated(45, 0, 1, 0);

        if(useTwoGameMode){
            zoomOut(-5);
            game->setTranslationVec(-10, 0, 0);
            secenodGame->setTranslationVec(10, 0, 0);

            secenodGame->draw();
            secenodGame->setSnakeMovement(rotateY);
        }else {
            zoomIn(1);
            game->setTranslationVec(0, 0, 0);
            secenodGame->setTranslationVec(0, 0, 0);
        }

        game->draw();
        game->setSnakeMovement(translateX);
        rectangle->setRotation(rotateY,0,1,0);
        rectangle->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,1,0,0);
        //rectangle->draw();


        // make it appear (before this, it's hidden in the rear buffer)
        glfwSwapBuffers(window);

        glfwPollEvents();


    }

    glfwTerminate();

    printf("Goodbye!\n");

    return 0;
}
