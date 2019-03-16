#ifndef MODEL_H
#define MODEL_H

#include<windows.h>
#include<GL/glut.h>

class Model
{
    public:
        Model();
        virtual ~Model();
        void drawModel();
        void modelInit(char*);

        double RotateX;
        double RotateY;
        double RotateZ;

        double zoom;
        double xPos;
        double yPos;

    protected:

    private:
};

#endif // MODEL_H
