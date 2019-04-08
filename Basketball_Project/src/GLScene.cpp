#include "GLScene.h"
#include <GLLight.h>
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<Player.h>
#include <Enemy.h>
#include <ShootScene.h>

Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *Plx = new Parallax();
Player *Ply = new Player();

Enemy Enm[20];
TextureLoader * enmTex = new TextureLoader();


GLScene::GLScene()
{
    //ctor

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    flag0= true; //Landing page
    flag1 = false; //Menu page
    flag2 = false; //Game
    flag3 = false; //Help page
    flag4 = false; //Confirm to quit scene
    flagShoot = false; //Shoot screen
}

GLScene::~GLScene()
{
    //dtor
}

// Parts added in class below

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);                // for smooth animation transitions
    glClearColor(1.0f,1.6f,0.7f,0.0f);      // background color (r,g,b,a) - f sets value as float (class example uses 1,0,0)
    glClearDepth(1.0f);                     // decide what is at front and behind (depth)
    glEnable(GL_DEPTH_TEST);                // enable depth test flag for depth calculations

    //glEnable(GL_COLOR_MATERIAL);            // enable base color of object beneath texture
    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    //Mdl->modelInit("images/teapot.png");
    //Mdl->modelInit("images/teapot_alt.jpg");

   /*-----------------------init enemy----------------------------*/
    enmTex->loadTexture("images/skele.png");

        for(int i=0;i<2;i++)
    {

        Enm[i].enemyTex = enmTex->tex;


       Enm[i].xPos = (float)((rand())%10)/10;
        Enm[i].yPos = (float)(((rand()%20)-10)/10);

        Enm[i].placeEnemy(Enm[i].xPos,Enm[i].yPos,-0.3);
        Enm[i].enemyInit();

    }
/*--------------------------------end enemy init------------------*/


    // do load all the menus

    //Initializing all menus
    landingPage->slideInit("images/LandingPage.png");  //Landing page
    menuPage->slideInit("images/MenuPage.png"); //Menu
    helpPage->slideInit("images/HelpPage.png"); //Help
    popUp->slideInit("images/PopUp.png");





    //Initializing game scene
    Plx->parallaxInit("images/Court_Temp.png");
    Ply->playerInit("images/dribble.png");

    //Initializing Shoot Scene
    shooterView->sceneInit("images/placeholder.png");

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

  if(flag0) //If the flag of landing page is true, draw the landing scene
  {
    glPushMatrix();
    landingPage->drawSlide(screenWidth, screenHeight );
    glPopMatrix();

  }

  if(flag1)
  {
    glPushMatrix();
    menuPage->drawSlide(screenWidth, screenHeight );
    glPopMatrix();
  }


  //  do something

    if(flag2)
    {  //If game flag is true, draw game scene
        glPushMatrix();
        Plx->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        Ply->drawPlayer();
        KbMs->checkKeyDown();
        KbMs->playerInput(Ply,Plx,0.004);
        Ply->playerActions();

        /* ---------------------Enemy Drawing---------------------*/
        glPushMatrix();
        //objTex->binder();
        for(int i=0;i<2;i++){

        Enm[i].drawEnemy();
        //Enm[i].action=0;
        //Enm[i].actions();

/*
        if(Enm[i].xPos<-0.5){
            Enm[i].xMove=0.01;
            Enm[i].action=0;
        }
        else if(Enm[i].xPos>0.5){
            Enm[i].xMove=-0.01;
            Enm[i].action=1;
        }

        Enm[i].xPos+=Enm[i].xMove;
*/
        }

        glPopMatrix();

    }

    /*-----------------------------------------End of Enemy drawing-----------*/

    if(flag3)
    {
        glPushMatrix();
        helpPage->drawSlide(screenWidth, screenHeight );
        glPopMatrix();
    }


    if(flag4)
    {
        glPushMatrix();
        //glTranslated(0.0,0.0,-5.0); //Created another window
        popUp->drawSlide(screenWidth, screenHeight );
        glPopMatrix();
    }

    //KbMs->keyEnv(Plx,0.004);

    if(flagShoot) {
        glPushMatrix();
        shooterView->drawSlide(screenWidth, screenHeight);
        glPopMatrix();
    }
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


//Handling the Game inputs
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
