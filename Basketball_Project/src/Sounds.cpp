#include "Sounds.h"

Sounds::Sounds()
{
    //ctor
}

Sounds::~Sounds()
{
    //dtor
    engine->drop();
}

void Sounds::playMusic(char* filename)
{
    engine->play2D(filename, true);
}

void Sounds::playSound(char* filename)
{
    engine->play2D(filename, false, false);
}

void Sounds::stopAllSounds()
{

}

int Sounds::initSounds()
{
    if(!engine) {
        cout<<"Could not start engine"<<endl;
        return 1;                               // return 1 if error
    }
    return 0;                                   // return 0 if success
}
