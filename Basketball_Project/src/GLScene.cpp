#include "GLScene.h"
#include <GLLight.h>
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<Player.h>

Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *Plx = new Parallax();
Player *Ply = new Player();

GLScene::GLScene()
{
    //ctor

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

// Parts added in class below

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);                // for smooth animation transitions
    glClearColor(1.0f,0.6f,0.7f,0.0f);      // background color (r,g,b,a) - f sets value as float (class example uses 1,0,0)
    glClearDepth(1.0f);                     // decide what is at front and behind (depth)
    glEnable(GL_DEPTH_TEST);                // enable depth test flag for depth calculations

    //glEnable(GL_COLOR_MATERIAL);            // enable base color of object beneath texture
    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    //Mdl->modelInit("images/teapot.png");
    //Mdl->modelInit("images/teapot_alt.jpg");

    Plx->parallaxInit("images/Court_Temp.png");
    Ply->playerInit("images/player.png");

    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    // clear
    glLoadIdentity();                                    // initialize

    /*
    glPushMatrix();
    Mdl->drawModel();                                    // draw the model from the model class
    glPopMatrix();
    */

    glPushMatrix();
    Plx->drawSquare(screenWidth,screenHeight);
    glPopMatrix();

    glTranslated(Ply->xPos,Ply->yPos,Ply->zPos);
    Ply->drawPlayer();

    KbMs->checkKeyDown();

    KbMs->playerInput(Ply);
    Ply->playerActions();

    //Plx->scroll("right",0.002);
    KbMs->keyEnv(Plx,0.004);
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;  // finding aspect ratio - casting width and height as GLfloat
    glViewport(0, 0, width, height);                           // setting viewport
    glMatrixMode(GL_PROJECTION);                               // setting up projection (further things look smaller)
    glLoadIdentity();                                          // need after glMatrixMode
    gluPerspective(45.0, aspectRatio, 0.1, 100);

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int GLScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
	{                                               // Pass messages into Inputs via pointer class KbMs (of type Inputs)
	    case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
            KbMs->wParam = wParam;
            KbMs->keyPressed(Mdl);     // pass the thing that is manipulated by the keys into keyPressed
            break;
		}
		case WM_KEYUP:								// Has A Key Been Released?
		{
            KbMs->keyUp();
            break;
		}
		case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            KbMs->mouseEventUp();
        break;								// Jump Back
        }

        case WM_MOUSEMOVE:
        {
             KbMs->mouseEventMove(Mdl, LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            KbMs->mouseEventWheel(Mdl, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
        }
	}
}
