#include "GameClock.h"

GameClock::GameClock()
{
    //ctor

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
    Tex->loadTexture(filename);
    isActive = true;
}

void GameClock::startClock(int mins, int secs, int msecs)
{
    minutes = mins;
    seconds = secs;
    milliseconds = msecs;

    runTime = true;
    timeOver = false;
    Time->start();
}

bool GameClock::timeAction()
{
    if (runTime) {
        if (Time->getTicks() > 10) {
            milliseconds -= 1;
            Time->reset();
        }
        if (minutes == 0 && seconds == 0 && milliseconds == 0) {
            runTime = false;
            timeOver = true;
        }
        if (milliseconds == -1) {
            seconds -= 1;
            milliseconds = 99;
        }
        if (seconds == -1) {
            minutes -= 1;
            seconds = 59;
        }
    }
    return timeOver;
}

void GameClock::drawClock()
{
    Tex->binder();
    if (isActive){
        glPushMatrix();
        glTranslated(xPos,yPos,zPos);
        glBegin(GL_QUADS);

        glTexCoord2f(xMin,yMax);
        glVertex3f(0.0,0.0,-1.0);

        glTexCoord2f(xMax,yMax);
        glVertex3f(1.0,0.0,-1.0);

        glTexCoord2f(xMax,yMin);
        glVertex3f(1.0,1.0,-1.0);

        glTexCoord2f(xMin,yMin);
        glVertex3f(0.0,1.0,-1.0);

        glEnd();

        glPopMatrix();
    }
}

void GameClock::activateClock(bool act)
{
    isActive = act;
}

