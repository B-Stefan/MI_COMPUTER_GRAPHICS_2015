//
// Created by Stefan B. on 05.07.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_GAME_H
#define GLFW3_DEMO_WITH_CMAKE_GAME_H


#include "Playground.h"
#include "Sphere.h"
#include "Snake.h"
#include "GlObject.h"
#include "ScorePrinter.h"


class Game :public GlObject {
public:
    Game(Point * origin);
    void start();
    void stop();
    void draw();
    void setVelocity(double v);
    double getVelocity();
    bool colidate(Vec3 *point);
    void setSnakeMovement(double angle);
    Vec3 randomVec();

private:
    int score;
    void applyLogic();
    void applyDefaults();
    void loseGame();
    bool isRunning;
    bool isSpecialApple;
    int  specialAppleTimer;
    void increaseScore();
    Snake * snake;
    Playground * playground;
    Sphere * apple;
    ScorePrinter * scorePrinter;


};


#endif //GLFW3_DEMO_WITH_CMAKE_GAME_H
