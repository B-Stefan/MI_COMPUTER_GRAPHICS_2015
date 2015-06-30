//
// Created by Fabian Redecker on 25.06.15.
//

#include "Playground.h"



Playground::Playground() {
    //field height
    this->fieldHeight = 18;
    //field width
    this->fieldWidth = 19.0;
    //height of the side fence
    this->fieldZ = 2;
    // left down corner x position
    this->startX = -9.5;
    // left down corner y position
    this->startY = -9.5;
    // z position of the points
    this->fieldPosZ = 0;
}

Playground::Playground(double field_width, double field_height, double start_x, double start_y) {
    //field height
    this->fieldHeight = field_height;
    //field width
    this->fieldWidth = field_width;
    //height of the side fence
    this->fieldZ = 2;
    // left down corner x position
    this->startX = start_x;
    // left down corner y position
    this->startY = start_y;
    // z position of the points
    this->fieldPosZ = 0;
}

void Playground::setMaterialColoR(int side, double r, double g, double b) {
    float	amb[4], dif[4], spe[4];
    int mat;

    dif[0] = r;
    dif[1] = g;
    dif[2] = b;

    for(int i = 0; i < 3; i++) {
        amb[i] = .1 * dif[i];
        spe[i] = .5;
    }
    amb[3] = dif[3] = spe[3] = 1.0;

    switch(side){
        case 1:	mat = GL_FRONT;
            break;
        case 2:	mat = GL_BACK;
            break;
        default: mat = GL_FRONT_AND_BACK;
    }

    glMaterialfv(mat, GL_AMBIENT, amb);
    glMaterialfv(mat, GL_DIFFUSE, dif);
    glMaterialfv(mat, GL_SPECULAR, spe);
    glMaterialf( mat, GL_SHININESS, 20);
}

/*
void Playground::drawPlaygrounD(){

    //ground
    glBegin(GL_QUADS);
    setMaterialColoR(1,0,1,0);
    setMaterialColoR(2,0,1,0);
    glVertex3f(startX,startY,fieldPosZ);
    glVertex3f(fieldWidth + startX, startY, fieldPosZ);
    glVertex3f(fieldWidth + startX, fieldHeight + startY ,fieldPosZ);
    glVertex3f(startX,fieldHeight + startY, fieldPosZ);
    glEnd();
    glFlush();


    //left
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,startY,fieldPosZ);
    glVertex3f(startX, fieldHeight + startY, fieldPosZ);
    glVertex3f(startX, startY, fieldZ);
    glVertex3f(startY, fieldHeight + startY, fieldZ);
    glEnd();
    glFlush();

    //right
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(fieldWidth + startX, startY, fieldPosZ);
    glVertex3f(fieldWidth + startX ,startY ,fieldZ);
    glVertex3f(fieldWidth + startX, fieldHeight + startY, fieldPosZ);
    glVertex3f(fieldWidth + startX, fieldHeight + startY, fieldZ);
    glEnd();
    glFlush();


    //down
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,startY,fieldPosZ);
    glVertex3f(fieldWidth + startX, startY, fieldPosZ);
    glVertex3f(startX, startY, fieldZ);
    glVertex3f(fieldWidth + startX, startY,fieldZ);
    glEnd();
    glFlush();

    //Top
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,fieldHeight + startY,fieldPosZ);
    glVertex3f(fieldWidth + startX, fieldHeight + startY, fieldPosZ);
    glVertex3f(startX,fieldHeight + startY,fieldZ);
    glVertex3f(fieldWidth + startX, fieldHeight + startY, fieldZ);
    glEnd();
    glFlush();

}
 */

void Playground::drawPlaygrounD(){

    //ground
    glBegin(GL_QUADS);
    setMaterialColoR(1,0,1,0);
    setMaterialColoR(2,0,1,0);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(fieldWidth + startX ,fieldPosZ, fieldHeight + startY);
    glVertex3f(startX, fieldPosZ, fieldHeight + startY);
    glEnd();
    glFlush();


    //left
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(startX,  fieldZ, startY);
    glVertex3f(startY, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();

    //right
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(fieldWidth + startX  ,fieldZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();

    //down
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(startX, fieldZ, startY);
    glVertex3f(fieldWidth + startX,fieldZ, startY);
    glEnd();
    glFlush();

    //Top
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(1,0,0,0);
    setMaterialColoR(2,0,0,0);
    glVertex3f(startX,fieldPosZ,fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(startX,fieldZ,fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();


}

std::vector<double> Playground::distanceFromSideS(Vec3 k){
    //distance from k to top
    std::vector<double> distances;
/*
    std::cout << "height = " << this->fieldHeight << std::endl;
    std::cout << "width = " << this->fieldWidth << std::endl;
    std::cout << "x = " << this->startX << std::endl;
    std::cout << "y = " << this->startY << std::endl;
    std::cout << "K[0] = " << k.p[0] << std::endl;
    std::cout << "K[1] = " << k.p[1] << std::endl;

*/

    double o = ((abs(this->fieldHeight) + abs(this->startY)) - abs(k.p[1]));
    //distance from k to left side
    double l = (abs(this->startX) + abs(k.p[0]));
    //distance from k to right side
    double r = ((abs(this->fieldWidth) + abs(this->startX)) - abs(k.p[0]));
    //distance from k to down
    double u = (abs(this->startY) + abs(k.p[1]));


    /*
    double o = 8.5 + fabs(k.p[1]);
    //distance from k to left side
    double l = 9.5 - fabs(k.p[0]);
    //distance from k to right side
    double r = 9.5 + fabs(k.p[0]);
    //distance from k to down
    double u = 9.5 - fabs(k.p[1]);
    */
    //add distances to vector
    distances.push_back(o);
    distances.push_back(l);
    distances.push_back(r);
    distances.push_back(u);
    return distances;
}