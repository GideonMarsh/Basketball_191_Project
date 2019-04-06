#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include<GL/gl.h>
#include<TextureLoader.h>
#include<time.h>
#include<Timer.h>

typedef struct {
    float x;
    float y;
    float z;
}vec;

class GameClock
{
    public:
        GameClock();
        virtual ~GameClock();

        void clockInit(char *);
        void startClock(int,int,int);
        void timeAction();
        void drawClock();
        void activateClock(bool);

        vec vertices[4];
        float xMin, yMin, xMax, yMax;
        float xPos, yPos, zPos;

        int minutes;
        int seconds;
        int milliseconds;

        bool timeOver;
        bool runTime;
        bool isActive;

        TextureLoader *T;
        Timer *Time;


    protected:

    private:
};

#endif // GAMECLOCK_H
