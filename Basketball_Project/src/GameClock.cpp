#include "GameClock.h"

GameClock::GameClock()
{
    //ctor

    xMin = 0.47;
    yMin = 0.08;
    xMax = 0.53;
    yMax = 0.33;

    xPos = -0.5675;
    yPos = 0.275;
    zPos = 0;

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
    Tex.loadTexture(filename);
    for (int i = 0; i < 3; i++) {
        digits[i].digitInit("images/game_clock_digits.jpg");
        digits[i].xPos = -0.725 + (i * 0.08);
        if (i > 1) {
            digits[i].xPos += 0.025;
        }
        digits[i].yPos = 0.275;
    }
    isActive = true;
}

void GameClock::startClock(int mins, int secs, int msecs)
{
    minutes = mins;
    seconds = secs;
    milliseconds = msecs;

    runTime = true;
    timeOver = false;
    Time.start();
}

bool GameClock::timeAction()
{
    if (runTime) {
        if (Time.getTicks() > 85) {
            milliseconds -= 1;
            Time.reset();
        }
        if (minutes == 0 && seconds == 0 && milliseconds == 0) {
            runTime = false;
            timeOver = true;
        }
        if (milliseconds == -1) {
            seconds -= 1;
            milliseconds = 9;
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
    if (minutes > 0) {
        digits[0].value = minutes / 10;
        digits[1].value = minutes % 10;
        digits[2].value = seconds / 10;
    }
    else {
        digits[0].value = seconds / 10;
        digits[1].value = seconds % 10;
        digits[2].value = milliseconds;
    }
    for (int i = 0; i < 3; i++) {
        digits[i].drawDigit();
    }

    Tex.binder();
    if (isActive){
        glPushMatrix();
        glTranslated(xPos,yPos,zPos);
        glBegin(GL_QUADS);

        glTexCoord2f(xMin,yMax);
        glVertex3f(0.0,0.0,-1.0);

        glTexCoord2f(xMax,yMax);
        glVertex3f(0.03,0.0,-1.0);

        glTexCoord2f(xMax,yMin);
        glVertex3f(0.03,0.12,-1.0);

        glTexCoord2f(xMin,yMin);
        glVertex3f(0.0,0.12,-1.0);

        glEnd();

        glPopMatrix();
    }

}

void GameClock::activateClock(bool act)
{
    isActive = act;
}

