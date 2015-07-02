//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_RECTANGLE_H
#define GLFW3_DEMO_WITH_CMAKE_RECTANGLE_H

#import "GlObject.h"
class Rectangle : public GlObject{
public:
    Rectangle(double h, double w,Point *origin);
    void draw();
    bool colidate(Vec3 * postition);
private:
    double width;
    double height;
    Point* A;
    Point* B;
    Point* C;
    Point* D;
};


#endif //GLFW3_DEMO_WITH_CMAKE_RECTANGLE_H
