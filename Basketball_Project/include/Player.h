#ifndef PLAYER_H
#define PLAYER_H

#include<GL/gl.h>
#include<TextureLoader.h>

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

        vec vertices[4];              // boundary for player hitbox
        float xMin, yMin, xMax, yMax;

        int actionCounter;
        string action;

    protected:

    private:
};

#endif // PLAYER_H
