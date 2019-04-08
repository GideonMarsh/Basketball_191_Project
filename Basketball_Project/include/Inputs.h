#ifndef INPUTS_H
#define INPUTS_H

#include<windows.h>
#include<Model.h>
#include<Parallax.h>
#include<Player.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void keyPressed(Model *);
        void keyUp();

        void mouseEventDown(Model *, double, double);
        void mouseEventUp();
        void mouseEventWheel(Model *, double);
        void mouseEventMove(Model *, double, double);

        void keyEnv(Parallax *,float);                    // for parallax movement (moving the background using the keys)
        void playerInput(Player *, Parallax*, float);

        void checkKeyDown();

        double prev_mouse_X;
        double prev_mouse_Y;

        bool mouse_Translate;
        bool mouse_Rotate;

        bool move_left, move_right, move_up, move_down, shoot;

        WPARAM wParam; // needed for windows programming - passed to keyboard

    protected:

    private:
};

#endif // INPUTS_H
