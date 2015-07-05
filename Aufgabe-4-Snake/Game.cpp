//
// Created by Stefan B. on 05.07.15.
//

#include "Game.h"
#include "Sphere.h"
#include "Playground.h"
#include "Snake.h"
#include "Point.h"

Game::Game(Point * origin)
    :GlObject::GlObject(origin)
    {
        this->applyDefaults();
        this->originPoint->setTranslationVec(new Vec3());
        //this->originPoint->setRotate(0,new Vec3());
}
void Game::applyDefaults() {
    this->playground = new Playground(17,17,-9,-9);
    this->snake= new Snake(this->originPoint);
    this->apple = new Sphere(0.3,this->originPoint);
    this->scorePrinter = new ScorePrinter(-3,0,-3,"PRESS SPACEBAR TO START THE GAME");
    this->isRunning = false;
    this->score = 0;
}
void Game::increaseScore() {
    this->score  += 10;
}
void Game::start() {
    this->isRunning = true;
}
void Game::stop() {
    this->isRunning = false;
    this->applyDefaults();
}
void Game::loseGame() {
    this->scorePrinter->changeText("You lose the game! Score: " + this->score);
    this->stop();
}
void Game::applyLogic() {
    Vec3 headPoint = this->snake->getHeadPoint();

    if( !this->playground->isVecInField(headPoint)
        || this->snake->collidateThemSelf()){


        //this->loseGame();
    }
    else if(this->apple->colidate(&headPoint)){

        this->increaseScore();
    }
}

bool Game::colidate(Vec3 *point) {
    return false;
}
void Game::draw() {
    GlObject::draw();
    glTranslated(this->translationVec->p[0],this->translationVec->p[1],this->translationVec->p[2]);
    glPushMatrix();
    this->applyLogic();
    if(this->isRunning){
        this->playground->drawPlaygrounD();
        this->apple->draw();
        this->snake->draw();
    }
    this->scorePrinter->print();
    glPopMatrix();
    glTranslated(this->translationVec->p[0]*-1,this->translationVec->p[1]*-1,this->translationVec->p[2]*-1);
}