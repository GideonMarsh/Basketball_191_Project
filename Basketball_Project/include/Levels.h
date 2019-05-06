#ifndef LEVELS_H
#define LEVELS_H
#include <GLScene.h>


class Levels
{
    public:
        Levels();
        virtual ~Levels();

        int levelCount;

        void levelParam(int);
        GLScene * glS = new GLScene();

    protected:

    private:
};

#endif // LEVELS_H
