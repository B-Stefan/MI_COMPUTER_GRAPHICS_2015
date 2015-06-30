//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKE_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKE_H

#import "GlObject.h"
#import "SnakeHead.h"
#import "SnakePart.h"
class Snake : public GlObject{
public:
    Snake(Point *origin);
    void draw();
    Vec3 getHeadPoint();
private:
    SnakePart * firstPart;
    void addPart();
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKE_H
