#include "ShootScene.h"

ShootScene::ShootScene()
{
    //ctor
    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
    pages = 0;
}

ShootScene::~ShootScene()
{
    //dtor
}
GLvoid ShootScene::sceneInit(char* fileName)
{
    texture->loadTexture(fileName);
}

GLvoid ShootScene::drawSlide(GLfloat w, GLfloat h)
{
    glPushMatrix();
    //glTranslated(0.0,0.0,-0.5); Created another window

    texture->binder();
//    glBegin(GL_POLYGON);
//        //Top-Left Corner to Bottom-Left Corner
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex2f(0, 0);
//
//        //Top-Right Corner to Bottom-Right Corner
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex2f(w, 0);
//
//        //Bottom-Right Corner to Top-Right Corner
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex2f(w, h);
//
//        //Bottom-Left Corner to Top-Left Corner
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex2f(0, h);
//    glEnd();
//    glPopMatrix();

    glPushMatrix();
    glScaled(5.0,4.0,1.0);

    glBegin(GL_POLYGON);                    // drawing in openGL

    glTexCoord2f(xMin,yMin);                // drawing the four vertices of the square
    glVertex3f(-w/h,1,-10.0f);     // using width/height (aspect ratio) lets us scale to any screen size later
    glTexCoord2f(xMax,yMin);                // alternate positives/negatives to have all combinations (each area on graph)
    glVertex3f(w/h,1,-10.0f);
    glTexCoord2f(xMax,yMax);
    glVertex3f(w/h,-1,-10.0f);
    glTexCoord2f(xMin,yMax);
    glVertex3f(-w/h,-1,-10.0f);

    glEnd();
    glPopMatrix();
}
