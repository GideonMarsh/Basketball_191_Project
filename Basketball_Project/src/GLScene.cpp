#include "GLScene.h"
#include <GLLight.h>
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<Player.h>
#include <Enemy.h>
#include <ShootScene.h>
#include<GameClock.h>
#include <Particles.h>
#include <Sounds.h>


Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *Plx = new Parallax();
Player *Ply = new Player();
GameClock *Gc = new GameClock();
Sounds *Snd = new Sounds();

Enemy Enm[20];
TextureLoader * enmTex = new TextureLoader();

Particles *pcl = new Particles();


GLScene::GLScene()
{
    //ctor

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    landingFlag= true; //Landing page
    menuFlag = false; //Menu page
    gameFlag = false; //Game
    helpFlag = false; //Help page
    exitFlag = false; //Confirm to quit scene
    flagShoot = false; //Shoot screen
    takenShot = false; //True when player hits space while on shot screen
    gameOverFlag = false;
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
    enmTex->loadTexture("images/enm12.png");
    Snd->playMusic("sounds/dance.mp3");

        for(int i=0;i<20;i++)
    {

        Enm[i].enemyTex = enmTex->tex;


        /*Enm[i].xPos = (float)((rand())%10)/10;
        Enm[i].yPos = (float)(((rand()%20)-10)/10);
        Enm[i].placeEnemy(Enm[i].xPos,Enm[i].yPos,-0.3);
        Enm[i].placeEnemy(0.5,0,-1);*/

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
    Gc->clockInit("images/game_clock.jpg");

    startingLevel();

    //Initializing Shoot Scene
    shooterView->sceneInit("images/shoot.png");

    gameOverPage->slideInit("images/gameOver.png");

    if(Snd->initSounds()) return false; // return false if sounds could not be initialized

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




  if(landingFlag) //If the flag of landing page is true, draw the landing scene
  {
    glPushMatrix();
    landingPage->drawSlide(screenWidth, screenHeight );
    glPopMatrix();


  }

  if(menuFlag)
  {
    glPushMatrix();
    menuPage->drawSlide(screenWidth, screenHeight );
    glPopMatrix();

    startingLevel();
  }


 if(gameOverFlag)
            {
              glPushMatrix();
             gameOverPage->drawSlide(screenWidth, screenHeight );
                glPopMatrix(); }


    //If game flag is true, draw game scene
    if(gameFlag)
    {
        glPushMatrix();
        Plx->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        if (Gc->timeAction()) {

            // Code for when time runs out, go to game over scene
            if(Gc->timeOver == true)
            {

                gameOverFlag = true;

            }
            else
            {
                //Code needed for if the player made a basket before time ran out, then move to next level

                nextLevel();
            }

        }



        if(gameOverFlag)
        {

          glPushMatrix();
          gameOverPage->drawSlide(screenWidth, screenHeight );
          glPopMatrix();

        }

        if(!gameOverFlag){

            Ply->drawPlayer();
            KbMs->checkKeyDown();
            if (KbMs->playerInput(Ply,Plx,Enm,0.004)) {
                gameFlag = false;
                flagShoot = true;
            }
            Ply->playerActions();

             /* ---------------------Enemy Drawing---------------------*/
            //objTex->binder();
            for(int i=0;i<enmNum;i++){

             //   glTranslated(Enm[i].xPos,Enm[i].yPos,Enm[i].zPos-i/100.0);
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
                }*/
                //Enm[i].xPos+=Enm[i].xMove;

                Enm[i].enemyMovement(Ply);

                Enm[i].checkCollision(Ply);
            }

            /*-----------------------------------------End of Enemy drawing-----------*/


            Ply->knockedBack > 0 ? Ply->knockedBack -= 1 : NULL;        // used in calculating enemy collision
            Gc->drawClock();
        }


    }


    if(helpFlag)
    {
        glPushMatrix();
        helpPage->drawSlide(screenWidth, screenHeight );
        glPopMatrix();
    }


    if(exitFlag)
    {
        glPushMatrix();
        //glTranslated(0.0,0.0,-5.0); //Created another window
        popUp->drawSlide(screenWidth, screenHeight );
        glPopMatrix();
    }


    //KbMs->keyEnv(Plx,0.004);

    if(flagShoot) {
        if (Gc->timeAction()) {
            // Code for running out of time goes here
            if(Gc->timeOver == true)
            {
                gameOverFlag = true;
            }

        }


        if(gameOverFlag)
        {

          glPushMatrix();
          gameOverPage->drawSlide(screenWidth, screenHeight );
          glPopMatrix();

        }

        if(!gameOverFlag)
        {


            if (Ply->actionCounter < 2) Ply->action = "stand";

            Gc->drawClock();

            KbMs->checkKeyDown();
            if (KbMs->checkShot(Ply)) {
                // code for player making the shot
                // if shot failed but player still has time left, set player action to "stand" to enable another shot to be taken
            }
            Ply->playerActions();

            glPushMatrix();
            shooterView->drawSlide(screenWidth, screenHeight);
            glPopMatrix();

           /* if(Ply->win==true){

                pcl->generateParticles();
                pcl->drawParticle();
                pcl->lifeTime();

            }
            */

            glPushMatrix();
            Ply->xPos=0.18;
            Ply->yPos=-0.38;
           // Ply->action = "shoot";
            Ply->drawPlayer();
            glPopMatrix();

            if (takenShot) {
            Ply->action = "shoot";
            }
        }




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

void GLScene::startingLevel()
{
    enmNum = 3;
    enemySpeed = 0.006;
    gameTime = 30.0;

    Ply->xPos = -0.3;
    Ply->yPos = -0.05;
    Plx->xMax = 0.4;
    Plx->xMin = 0.0;

    for (int i = 0; i < enmNum; i++) {
        Enm[i].placeEnemy((((rand() % 23) + 5) / 10.0),(((rand() % 8) - 4) / 10.0),-1.0);
        Enm[i].speed = enemySpeed;
        Enm[i].aiType = rand() % 12;
    }

    Gc->startClock(0,(int) gameTime,((int)(gameTime * 10)) % 10);
}

void GLScene::nextLevel()
{
    gameTime = ceil(gameTime * 9.5) / 10.0;
    gameTime < 10.0 ? gameTime = 10.0 : NULL;

    enmNum++;
    enmNum > 20 ? enmNum = 20 : NULL;

    enemySpeed = enemySpeed + 0.0002;

    Ply->xPos = -0.3;
    Ply->yPos = -0.05;
    Plx->xMax = 0.4;
    Plx->xMin = 0.0;

    for (int i = 0; i < enmNum; i++) {
        Enm[i].placeEnemy((((rand() % 23) + 5) / 10.0),(((rand() % 8) - 4) / 10.0),-1.0);
        Enm[i].speed = enemySpeed;
        Enm[i].aiType = rand() % 12;
    }

    Gc->startClock(0,(int) gameTime,((int)(gameTime * 10)) % 10);
}
