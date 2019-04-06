#ifndef Enemy_H
#define Enemy_H

#include <Timer.h>
#include <TextureLoader.h>
#include <GL/gl.h>


class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();

        void drawEnemy();
        void placeEnemy(float, float, float);
        void actions();


        int action=0;

        float xMove;
        bool isEnemyLive = true;

        GLuint enemyTex;

        void enemyInit();

        float xPos,yPos,zPos;
        float xSize,ySize,zSize;
        float xMin,yMin,xMax,yMax;

        float rotateX,rotateY,rotateZ;

        float frames;

        Timer *T3 = new Timer();







    protected:

    private:
};

#endif // Enemy_H
