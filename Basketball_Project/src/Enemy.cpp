#include "Enemy.h"

Enemy::Enemy()
{
    //ctor

    xPos = -0.3;
    yPos = 0.0;
    zPos = -0.5;

    xSize = 0.15;
    ySize = 0.15;

    /*frames = 4.0;

    xMin = 0.0;
    yMin = 0.0;
    xMax = 1.0/(float)frames;
    yMax = 0.25;*/

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;

    xMove=0.01;





}

Enemy::~Enemy()
{
    //dtor
}


void Enemy::enemyInit()
{

    frames = 1.0;

    xMin = 0.0;
    yMin = 0.0;
    //xMax = 1.0/(float)frames;
    xMax = 1.0;
    yMax = 1;

    //yPos=-0.12;
}


void Enemy::drawEnemy()
{
    glPushMatrix();

    glTranslated(xPos,yPos,zPos);

    glRotated(rotateX,1,0,0);
    glRotated(rotateY,0,1,0);
    glRotated(rotateZ,0,0,1);

    glBindTexture(GL_TEXTURE_2D,enemyTex);

    glScaled(xSize,ySize,1.0);

    glBegin(GL_QUADS);

    glTexCoord2f(xMin,yMax);
    glVertex3f(1.0,0.0,0.0);

    glTexCoord2f(xMax,yMax);
    glVertex3f(0.0,0.0, 0.0);

    glTexCoord2f(xMax,yMin);
    glVertex3f(0.0,1.0, 0.0);

    glTexCoord2f(xMin,yMin);
    glVertex3f(1.0,1.0, 0.0);

    glEnd();

    glPopMatrix();
}

void Enemy::placeEnemy(float x, float y, float z)
{
    xPos = x;
    yPos = y;
    zPos = z;
}

void Enemy::actions()
{
    switch(action)
    {
    case 0:
            if(T3->getTicks()>60){
                xMin +=1.0/(float)frames;
                xMax +=1.0/(float)frames;

                yMin = 0.0;
                yMax = 1.0;
                    if(xMax>=1){
                        xMin=1.0;
                        //xMax=1.0/(float)frames;
                        xMax = 0.0;
                        T3->reset();
                    }
                T3->reset();
                }


        break;

    case 1:
            if(T3->getTicks()>60){
                xMin +=1.0/(float)frames;
                xMax +=1.0/(float)frames;

                yMin = 0.4;
                yMax = 0.6;
                    if(xMax>=1){
                        xMin=0.0;
                        xMax=1.0/(float)frames;
                        T3->reset();
                    }
                T3->reset();
                }


        break;


    }
}

void Enemy::checkCollision(Player* ply)
{
    if (xPos + xSize >= ply->xPos && ply->xPos + ply->xSize >= xPos) {
        if (yPos + ySize >= ply->yPos && ply->yPos + ply->ySize >= yPos) {
            if (ply->knockedBack == 0) {
                ply->knockedBack = 14;                            // increase this number to knock the player back further
            }
        }
    }
}

