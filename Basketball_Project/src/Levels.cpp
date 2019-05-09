#include "Levels.h"

Levels::Levels()
{
    //ctor
}

Levels::~Levels()
{
    //dtor
}
void Levels::levelParam(int count)
{
    //enemy movement speed
    glS->enemySpeed=glS->enemySpeed*10;

    //number of enemies
    glS->enmNum=glS->enmNum*2;

    //number of shots
}
