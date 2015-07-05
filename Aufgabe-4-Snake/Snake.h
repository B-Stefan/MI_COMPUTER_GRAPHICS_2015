//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKE_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKE_H

#import "GlObject.h"
#import "SnakeHead.h"
#import "SnakePart.h"
#import <vector>
class Snake : public GlObject{
public:
    Snake(Point *origin);
    void draw();
    Vec3 getHeadPoint();
    bool collidateThemSelf();
    bool colidate(Vec3 * vec);
    void addPart();
private:
    SnakePart * firstPart;
    std::vector<Vec3> * track;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKE_H
