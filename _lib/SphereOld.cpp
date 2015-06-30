//
// Created by Stefan B. on 04.05.15.
//

#include "SphereOld.h"
#include "utils.h"
#import "GLFW/glfw3.h"
#import "iostream"
/*
 * Plane  class to draw, move and rotate a plane
 */
SphereOld::SphereOld(Vec3 &middle, double r) {
    this->middle = middle;
    this->r = r;


}
double SphereOld::getR() {
    return this->r;
}

Vec3 SphereOld::getMiddle()  {
    return this->middle;
}
void SphereOld::setMiddle(Vec3 v) {
    this->middle = v;
}
void SphereOld::drawSphere(){
        int     i, j,
                n1 = 24, n2 = 32;
        Vec3    normal, v1;
        double  a1, a1d = M_PI / n1,
                a2, a2d = M_PI / n2,
                s1, s2,
                c1, c2;

        glShadeModel(GL_SMOOTH);
        for(i = 0; i < n1; i++){
            a1 = i * a1d;

            glBegin(GL_TRIANGLE_STRIP);
            for(j = 0; j <= n2; j++){
                a2 = (j + .5 * (i % 2)) * 2 * a2d;

                s1 = sin(a1);
                c1 = cos(a1);
                s2 = sin(a2);
                c2 = cos(a2);
                normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
                v1 = this->r * normal;
                glNormal3dv(normal.p);
                glVertex3dv(v1.p);

                s1 = sin(a1 + a1d);
                c1 = cos(a1 + a1d);
                s2 = sin(a2 + a2d);
                c2 = cos(a2 + a2d);
                normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
                v1 =  this->r * normal;
                glNormal3dv(normal.p);
                glVertex3dv(v1.p);
            }
            glEnd();
        }
        this->borderLocal = v1;
}

void SphereOld::draw(){

    glPushMatrix();
    //Translate to middle
    glTranslated(this->middle.p[0], this->middle.p[1], this->middle.p[2]);
    Vec3 point = Vec3(0,0,0);
    Utils::drawAxis(point,10);

    this->drawSphere();

    glPopMatrix();

}