//
// Created by Stefan B. on 04.05.15.
//

#include "utils.h"
#include "vec3.hpp"
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <iostream>


void Utils::setGlobalCoords(Vec3 &local, Vec3 &global) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble viewVector[3];
    GLdouble projection[16];

    //get the matrices
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    GLdouble globalX, globalY, globalZ;
    viewVector[0] = modelview[8];
    viewVector[1] = modelview[9];
    viewVector[2] = modelview[10];

    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    int res = gluProject(local.p[0], local.p[1], local.p[2], modelview, projection, viewport, &globalX, &globalY,
                         &globalZ);
    global.p[0] = globalX;
    global.p[1] = globalY;
    global.p[2] = globalZ;

}
void Utils::drawAxis(Vec3 &point, double length) {

    //Normal z-axis
    glBegin(GL_LINES);
    glColor3f(0, 1, 0.0);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0],point.p[1], point.p[2]+1*length);
    glEnd();


    //x-axis
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0]+1+1*length,point.p[1], point.p[2]);
    glEnd();

    //y-axis
    glBegin(GL_LINES);
    glColor3f(point.p[0],point.p[1], 1);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0],point.p[1]+1*length, point.p[2]);
    glEnd();

}
