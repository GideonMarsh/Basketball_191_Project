#ifndef PLAYER_H
#define PLAYER_H

#include<GL/gl.h>
#include<TextureLoader.h>
#include<Timer.h>

typedef struct {
    float x;
    float y;
    float z;
}vec;

class Player
{
    public:
        Player();
        virtual ~Player();

        void drawPlayer();
        void playerInit(char *);
        void playerActions();
        void playerTranslate(float, float);

        vec vertices[4];              // boundary for player hitbox
        float xMin, yMin, xMax, yMax;
        float xPos, yPos, zPos;
        float animateFrames;

        int actionCounter;
        string action;

        Timer *Time = new Timer();
        TextureLoader *T = new TextureLoader();

    protected:

    private:
};

#endif // PLAYER_H
