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
    bool colidate(Vec3 *point);

private:
    int score;
    void applyLogic();
    void applyDefaults();
    void loseGame();
    bool isRunning;
    void increaseScore();
    Snake * snake;
    Playground * playground;
    Sphere * apple;
    ScorePrinter * scorePrinter;


};


#endif //GLFW3_DEMO_WITH_CMAKE_GAME_H
