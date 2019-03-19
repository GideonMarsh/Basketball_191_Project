#include "Player.h"
#include<Timer.h>

Timer *Time = new Timer();

TextureLoader *T = new TextureLoader();

Player::Player()
{
    //ctor
    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = -1.0;
    vertices[1].x = 0.5; vertices[1].y = 0.0; vertices[1].z = -1.0;
    vertices[2].x = 0.5; vertices[2].y = 0.5; vertices[2].z = -1.0;
    vertices[3].x = 0.0; vertices[3].y = 0.5; vertices[3].z = -1.0;

    xMin = 0.0;
    yMin = 0.0;
    xMax = 0.0;
    yMax = 0.0;

    //Starting position for player
    xPos = -0.2;
    yPos = -0.3;
    zPos = -1;

    actionCounter = 0;
    action = "walk_left";
}

Player::~Player()
{
    //dtor
}

void Player::drawPlayer()
{
    T->binder();
    glPushMatrix();
    glBegin(GL_QUADS);

    glTexCoord2f(xMin,yMax);
    glVertex3f(vertices[0].x,vertices[0].y, vertices[0].z);

    glTexCoord2f(xMax,yMax);
    glVertex3f(vertices[1].x,vertices[1].y, vertices[1].z);

    glTexCoord2f(xMax,yMin);
    glVertex3f(vertices[2].x,vertices[2].y, vertices[2].z);

    glTexCoord2f(xMin,yMin);
    glVertex3f(vertices[3].x,vertices[3].y, vertices[3].z);

    glEnd();

    glPopMatrix();
}

void Player::playerInit(char *filename)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    T->loadTexture(filename);

    // Determines the sprite that is used from the spritesheet
    // swapping the values of min/max reverses the image
    xMin = 0.0;
    xMax = 0.1;

    yMin = 0.035;
    yMax = 0.11;

    Time->start();
}

void Player::playerTranslate(float xChange, float yChange)
{
    /*xPos += xChange;
    if (xPos < 0.0) {
        xPos = 0.0;
    }
    if (xPos > 1.0) {
        xPos = 1.0;
    }*/
    yPos += yChange;
    if (yPos < -1.0) {
        yPos = -1.0;
    }
    if (yPos > 0.5) {
        yPos = 0.5;
    }
}

void Player::playerActions()
{
    if (action == "walk_right") {
        if (Time->getTicks() > 120) {
            actionCounter += 1;
            Time->reset();
        }
        switch (actionCounter % 4) {
        case 0:
            xMin = 0.3;
            xMax = 0.4;
            break;
        case 1:
        case 3:
            xMin = 0.4;
            xMax = 0.5;
            break;
        case 2:
            xMin = 0.5;
            xMax = 0.6;
            break;
        }
    }
    if (action == "walk_left") {
        if (Time->getTicks() > 120) {
            actionCounter += 1;
            Time->reset();
        }
        switch (actionCounter % 4) {
        case 0:
            xMin = 0.4;
            xMax = 0.3;
            break;
        case 1:
        case 3:
            xMin = 0.5;
            xMax = 0.4;
            break;
        case 2:
            xMin = 0.6;
            xMax = 0.5;
            break;
        }
    }
    if (action == "stand") {
        xMin = 0.0;
        xMax = 0.1;
    }
}

