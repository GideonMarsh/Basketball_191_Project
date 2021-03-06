#include "Inputs.h"
#include "GLScene.h"

Inputs::Inputs()
{
    //ctor

    prev_mouse_X = 0;
    prev_mouse_Y = 0;

    mouse_Translate = 0;
    mouse_Rotate = 0;

    move_left = false;
    move_right = false;
    move_up = false;
    move_down = false;
    shoot = false;

    canShoot = false;
}

Inputs::~Inputs()
{
    //dtor
}

void Inputs::keyPressed(Model * Mdl)
{
    /*
    switch(wParam) {
    case VK_LEFT:
        move_left = true;
        break;
    case VK_RIGHT:
        move_right = true;
        break;
    case VK_UP:
        move_up = true;
        break;
    case VK_DOWN:
        move_down = true;
        break;
    default: break;
    }*/
}

void Inputs::keyUp()
{
    if (wParam == VK_SPACE) {
        canShoot = true;
    }
    /*
    switch(wParam) {
    case VK_LEFT:
        move_left = false;
        break;
    case VK_RIGHT:
        move_right = false;
        break;
    case VK_UP:
        move_up = false;
        break;
    case VK_DOWN:
        move_down = false;
        break;
    default: break;
    }*/
}

void Inputs::mouseEventDown(Model * Mdl, double x, double y)
{
    prev_mouse_X = x;
    prev_mouse_Y = y;

    switch(wParam) {

    case MK_LBUTTON:
        mouse_Rotate = true;                    // if left-click, rotate
        break;

    case MK_RBUTTON:
        mouse_Translate = true;                 // if right-click, translate
        break;

    case MK_MBUTTON:
        break;

    default: break;
    }
}

void Inputs::mouseEventUp()
{
    mouse_Rotate = false;                       // when either mouse button is released, stop rotating and translating
    mouse_Translate = false;                    // from mouse movement
}

void Inputs::mouseEventWheel(Model* Mdl, double Delta)
{
    Mdl->zoom += Delta/100;
}

void Inputs::mouseEventMove(Model* Mdl, double x, double y)
{
    if (mouse_Translate) {
        Mdl->xPos += (x - prev_mouse_X) / 100;       // divide by 100 to prevent extremely fast movement
        Mdl->yPos -= (y - prev_mouse_Y) / 100;       // use subtraction because windows y coordinates start at 0 at the top
                                                // and increase going down, our model has 0 in the middle, increases going
        prev_mouse_X = x;                       // up decreases going down.
        prev_mouse_Y = y;
    }
    if (mouse_Rotate) {
        Mdl->RotateY += (x - prev_mouse_X) / 3;      // x and y don't match up to make model movement intuitive to how mouse is moved
        Mdl->RotateX += (y - prev_mouse_Y) / 3;

        prev_mouse_X = x;
        prev_mouse_Y = y;
    }
}

// no longer used, combined with playerInput for full range of movement
void Inputs::keyEnv(Parallax * plx, float speed)
{
    /*
    switch(wParam) {
    case VK_LEFT:
        plx->scroll("left", speed);
        break;
    case VK_RIGHT:
        plx->scroll("right",speed);
        break;
    case VK_UP:
        plx->scroll("up",speed);
        break;
    case VK_DOWN:
        plx->scroll("down",speed);
        break;
    }

    if (move_right) {
        plx->scroll("right",speed);
    }
    else {
        if (move_left) {
            plx->scroll("left",speed);
        }
    }*/
}
// Checks to see if the given key is being pressed down and modifies the movement variables accordingly
void Inputs::checkKeyDown()
{
    move_left = (GetKeyState(VK_LEFT) & 0x8000) ? true : false;
    move_right = (GetKeyState(VK_RIGHT) & 0x8000) ? true : false;
    move_up = (GetKeyState(VK_UP) & 0x8000) ? true : false;
    move_down = (GetKeyState(VK_DOWN) & 0x8000) ? true : false;
    shoot = (GetKeyState(VK_SPACE) & 0x8000) ? true : false;
}
bool Inputs::playerInput(Player* ply, Parallax* plx, Enemy* enm, float speed)
{
    /*
    switch(wParam) {
    case VK_LEFT:
        ply->action = "walk_left";
        break;
    case VK_RIGHT:
        ply->action = "walk_right";
        break;
    }*/
    if (ply->knockedBack > 5) {         // increase this number to give the player more invincibility frames after being hit
        if (ply->xPos > -0.3) {
            ply->playerTranslate(-0.03,0.0);
        }
        else {
            if (! plx->scroll("left",speed * 2, enm)) {
                ply->playerTranslate(-0.03,0.0);
            }
        }
    }
    else {
        if (move_right) {
            ply->action = "walk_right";
            if (ply->xPos < -0.3) {
                ply->playerTranslate(0.015,0.0);
            }
            else {
                if (! plx->scroll("right",speed, enm)) {
                    ply->playerTranslate(0.015,0.0);
                }
            }
        }
        else {
            if (move_left) {
                ply->action = "walk_left";
                if (ply->xPos > -0.3) {
                    ply->playerTranslate(-0.015,0.0);
                }
                else {
                    if (! plx->scroll("left",speed, enm)) {
                        ply->playerTranslate(-0.015,0.0);
                    }
                }
            }
            else {
                ply->action = "stand";
            }
        }
        if (move_up) {
            if (!move_right && !move_left) {
                ply->action = "walk_right";
            }
            ply->playerTranslate(0.0, 0.015);
        }
        else {
            if (move_down) {
                if (!move_right && !move_left) {
                    ply->action = "walk_right";
                }
                ply->playerTranslate(0.0, -0.015);
            }
        }
    }

    if (shoot && ply->xPos > -0.15 && ply->yPos < 0.05 && ply->yPos > -0.2) {
        canShoot = false;
        shoot = false;
        return true;
    }
    shoot = false;
    return false;
}

bool Inputs::checkShot(Player* ply)
{
    if (shoot && canShoot && ply->actionCounter < 3) {
        ply->action = "shoot";
        canShoot = false;
        return true;
    }
    return false;
}



/*void Inputs::enemyMove(Enemy * enms, float xPos, float yPos)
{
    //move enemy based on player position
}*/
