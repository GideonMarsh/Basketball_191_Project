#include "GameClock.h"

GameClock::GameClock()
{
    //ctor
    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = -1.0;
    vertices[1].x = 1.0; vertices[1].y = 0.0; vertices[1].z = -1.0;
    vertices[2].x = 1.0; vertices[2].y = 1.0; vertices[2].z = -1.0;
    vertices[3].x = 0.0; vertices[3].y = 1.0; vertices[3].z = -1.0;

    xMin = 0.0;
    yMin = 0.0;
    xMax = 0.0;
    yMax = 0.0;

    xPos = 0.0;
    yPos = 0.0;
    zPos = -1;

    minutes = 0;
    seconds = 0;
    milliseconds = 0;

    timeOver = true;
    runTime = false;
}

GameClock::~GameClock()
{
    //dtor
}

void GameClock::clockInit(char* filename)
{
    T->loadTexture(filename);
    isActive = false;
}

void GameClock::startClock(int mins, int secs, int msecs)
{
    minutes = mins;
    seconds = secs;
    milliseconds = msecs;
}

void GameClock::timeAction()
{

}

void GameClock::drawClock()
{

}

void GameClock::activateClock(bool act)
{
    isActive = act;
}

