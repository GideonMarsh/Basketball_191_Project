#include "ShootScene.h"

ShootScene::ShootScene()
{
    //ctor
    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
    pages = 0;
    shotFloat = 0.0;
    bool moveUp = true;
    bool moveDown = false;
    bool winSpace = false;
    shotSpeed = 0.05;
}

ShootScene::~ShootScene()
{
    //dtor
}
GLvoid ShootScene::sceneInit(char* fileName)
{
    texture->loadTexture(fileName);
    Time->start();
    moveUp = true;
}
GLvoid ShootScene::UIInit(char* fileName2, char* fileName3)
{
    texture2->loadTexture(fileName2);
    texture3->loadTexture(fileName3);
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

    drawShotUI();





}
GLvoid ShootScene::drawShotUI()
{
    glColor3f(1, 0, 0);
<<<<<<< HEAD
    texture2->binder();
 //   glScaled(.5,.5,1.0);
=======

>>>>>>> 961db39040b034f58c19cdf576d4cf88b028e37d
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
	//Larger rectangle, the whole aiming meter
	glColor3f(1, 0, 0);
	glVertex3f(1.9f, -1.5f, -5.0f);
	glVertex3f(2.2f, -1.5f, -5.0f);
	glVertex3f(2.2f, -0.2f, -5.0f);
	glVertex3f(1.9f, -0.2f, -5.0f);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	//Triangle -- shows timing of aim
	glVertex3f(1.8f, -1.5f + shotFloat, -5.0f);
	glVertex3f(1.6f, -1.3f + shotFloat, -5.0f);
	glVertex3f(1.6f, -1.7f + shotFloat, -5.0f);
	glEnd(); //End triangle coordinates

	texture3->binder();
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	//Smaller rectangle- player shoots here to score
	glColor3f(1, 0, 0);
	glVertex3f(1.9f, -0.7f, -4.999f);
	glVertex3f(2.4f, -0.7f, -4.999f);
	glVertex3f(2.4f, -0.4f, -4.999f);
	glVertex3f(1.9f, -0.4f, -4.999f);
	glEnd();

	//shotFloat+= .01;
    if (moveUp) {
        shotFloat += shotSpeed;
        if (shotFloat > 1.3) {
            moveUp = false;
            moveDown = true;
        }
    }
    if (moveDown && !moveUp) {
        shotFloat -= shotSpeed;
        if (shotFloat < 0) {
            moveUp = true;
            moveDown = false;
        }
    }
    if (shotFloat > 0.8 && shotFloat < 1.1) {
        winSpace = true;
    }
    else {
        winSpace = false;
    }

   // Time->reset();
}
