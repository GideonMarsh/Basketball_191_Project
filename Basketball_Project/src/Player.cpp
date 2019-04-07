#include "Player.h"

Player::Player()
{
    //ctor
    animateFrames = 7.0;

    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = -1.0;
    vertices[1].x = 0.5; vertices[1].y = 0.0; vertices[1].z = -1.0;
    vertices[2].x = 0.5; vertices[2].y = 0.5; vertices[2].z = -1.0;
    vertices[3].x = 0.0; vertices[3].y = 0.5; vertices[3].z = -1.0;

    xMin = 0.0;
    yMin = 0.0;
    xMax = 0.0;
    yMax = 0.0;

    //Starting position for player
    xPos = -0.3;
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
    glTranslated(xPos,yPos,zPos);
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
    xMax = 1.0/animateFrames;

    yMin = 0.02;
    yMax = 0.45;

    Time->start();
}

void Player::playerTranslate(float xChange, float yChange)
{
    xPos += xChange;
    if (xPos < -1.55) {
        xPos = -1.55;
    }
    if (xPos > 1.1) {
        xPos = 1.1;
    }
    yPos += yChange;
    if (yPos < -0.85) {
        yPos = -0.85;
    }
    if (yPos > 0.5) {
        yPos = 0.5;
    }
}

void Player::playerActions()
{

    if (action == "walk_right" && Time->getTicks() > 80) {
        if (actionCounter != 0) {
            xMin = -1.0/animateFrames;
            xMax = 0.0;
            actionCounter = 0;
        }
        xMin += 1.0/animateFrames;
        xMax += 1.0/animateFrames;

        yMin = 0.02;
        yMax = 0.45;

        Time->reset();
    }
    if (action == "walk_left" && Time->getTicks() > 80) {
        if (actionCounter != 1) {
            xMin = 0.0;
            xMax = -1.0/animateFrames;
            actionCounter = 1;
        }
        xMin += 1.0/animateFrames;
        xMax += 1.0/animateFrames;

        yMin = 0.02;
        yMax = 0.45;

        Time->reset();
    }
    if (action == "stand") {
        if (actionCounter != 2) {
            actionCounter = 2;
        }
        xMin = 1.0/animateFrames;
        xMax = 2.0/animateFrames;

        yMin = 0.5;
        yMax = 1.0;
    }
}

