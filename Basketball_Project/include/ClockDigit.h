#ifndef CLOCKDIGIT_H
#define CLOCKDIGIT_H

#include<TextureLoader.h>

class ClockDigit
{
    public:
        ClockDigit();
        virtual ~ClockDigit();

        void drawDigit();
        void digitInit(char*);

        int value;

        float xMin, yMin, xMax, yMax;
        float xPos, yPos, zPos;

        TextureLoader *T;

    protected:

    private:
};

#endif // CLOCKDIGIT_H
