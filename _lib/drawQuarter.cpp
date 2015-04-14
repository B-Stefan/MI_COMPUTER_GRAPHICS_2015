//
// Created by Stefan B. on 11.04.15.
//
#include <GLFW/glfw3.h>
#include "drawQuarter.h"
#include "vec3.hpp"

void DrawQuarter::drawQuarter(Vec3& middlePoint, double &l) {

    Vec3 pointTopLeftCorner = Vec3(middlePoint.p[0]-l/2,
                              middlePoint.p[1]+l/2,
                              middlePoint.p[2]-l/2);

    //Front Plane
    Vec3 A = l * Vec3(0,0,0)  + pointTopLeftCorner;
    Vec3 B = l * Vec3(1,0,0)  + pointTopLeftCorner;
    Vec3 C = l * Vec3(1,-1,0) + pointTopLeftCorner;
    Vec3 D = l * Vec3(0,-1,0) + pointTopLeftCorner;

    //Back Plane
    Vec3 T = Vec3(0,0,l);
    Vec3 A_BACK =   A +T;
    Vec3 B_BACK =   B +T;
    Vec3 C_BACK =   C +T;
    Vec3 D_BACK =   D +T;
    drawPlane(A,B,C,D); //FRONT




    drawPlane(A_BACK,B_BACK,C_BACK,D_BACK); //FRONT
    drawPlane(A,A_BACK,D_BACK,D);
    drawPlane(A,A_BACK,B_BACK,B);
    drawPlane(B,B_BACK,C_BACK,C);
    drawPlane(D,D_BACK,C_BACK,C);


}

void DrawQuarter::drawPlane(Vec3 &A, Vec3 &B, Vec3 &C,Vec3 &D) {

    glEnable(GL_NORMALIZE);
    Vec3 normal = ((A % B) % (C % D));

    glBegin(GL_LINES);
    glNormal3f(normal.p[0],normal.p[1],normal.p[2]);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(A.p[0], A.p[1], A.p[2]);
    glVertex3f(A.p[0]+normal.p[0], A.p[1]+normal.p[1], A.p[2]+normal.p[2]);
    glEnd();          // Start Drawing A Triangle




    glBegin(GL_QUADS);
    glNormal3dv(normal.p);
    glVertex3f(A.p[0],A.p[1],A.p[2]);
    glVertex3f(B.p[0],B.p[1],B.p[2]);
    glVertex3f(C.p[0],C.p[1],C.p[2]);
    glVertex3f(D.p[0],D.p[1],D.p[2]);
    glEnd();
}