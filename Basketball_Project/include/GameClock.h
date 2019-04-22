#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include<GL/gl.h>
#include<TextureLoader.h>
#include<time.h>
#include<Timer.h>

class GameClock
{
    public:
        GameClock();
        virtual ~GameClock();

        void clockInit(char *);
        void startClock(int,int,int);
        bool timeAction();
        void drawClock();
        void activateClock(bool);

        float xMin, yMin, xMax, yMax;
        float xPos, yPos, zPos;

        int minutes;
        int seconds;
        int milliseconds;

        bool timeOver;
        bool runTime;
        bool isActive;

        TextureLoader *Tex;
        Timer *Time;


    protected:

    private:
};

#endif // GAMECLOCK_H
