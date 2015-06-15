//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_CUBOID_H
#define GLFW3_DEMO_WITH_CMAKE_CUBOID_H

#import "GlObject.h"
#import "Rectangle.h"
class Cuboid : public GlObject{
public:
    Cuboid(double h, double w,Point *origin);
    void draw();
private:
    Rectangle* top;
    Rectangle* side_a ;
    Rectangle* side_b ;
    Rectangle* side_c ;
    Rectangle* side_d ;
    Rectangle* bottom ;
};


#endif //GLFW3_DEMO_WITH_CMAKE_CUBOID_H
