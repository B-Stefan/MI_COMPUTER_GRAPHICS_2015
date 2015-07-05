//
// Created by Stefan B. on 30.06.15.
//

#include "Sphere.h"
#include "GlObject.h"
#import "GLFW/glfw3.h"
#import "iostream"
#import "math.h"

Sphere::Sphere(double r, Point *origin):GlObject::GlObject(origin) {
    this->radius = r;
}

void Sphere::draw() {
    GlObject::draw();
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
            v1 = *this->originPoint->getPosition() + this->radius * normal;
            glNormal3dv(normal.p);
            glVertex3dv(v1.p);

            s1 = sin(a1 + a1d);
            c1 = cos(a1 + a1d);
            s2 = sin(a2 + a2d);
            c2 = cos(a2 + a2d);
            normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
            v1 =  *this->originPoint->getPosition() + this->radius * normal;
            glNormal3dv(normal.p);
            glVertex3dv(v1.p);
        }
        glEnd();
    }




}

bool Sphere::colidate(Vec3 * snakeHead) {

    double distanceX = fabs(this->originPoint->getPosition()->p[0] - snakeHead->p[0]);
    double distanceZ = fabs(this->originPoint->getPosition()->p[2] - snakeHead->p[2]);

//    std::cout << "distanceX: " << distanceX << std::endl;
//    std::cout << "distanceZ: " << distanceZ << std::endl;
//    std::cout << "point 1 : " << this->originPoint->getPosition()->p[0] << std::endl;
//    std::cout << "point 2 : " << this->originPoint->getPosition()->p[2] << std::endl;

    if(distanceX <= radius || distanceZ <= radius){

        std::cout << "treffer" << std::endl;
        return true;
    }
    return false;


}


double Sphere::getMiddlePoint(){

    return this->radius;
}