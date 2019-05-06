#include "Particles.h"

Particles::Particles()
{
    //ctor
}

Particles::~Particles()
{
    //dtor
}
void Particles::drawParticle()
{
    int i=0;
    glPointSize(rand()%5+1);

    glBegin(GL_POINTS);


    while(i<numDrops){
            glColor3f(drops[i].red, drops[i].green, drops[i].blue);
        if(drops[i].alive)
        {

            glVertex3f(drops[i].xpos, drops[i].ypos,-0.1);
        }

        i++;
    }
    glEnd();

}

void Particles::lifeTime()
{
    int i;

    for(i=0;i<numDrops;i++){

        if(drops[i].alive)
        {

            drops[i].xpos+=drops[i].velocityX;
            drops[i].ypos+=drops[i].velocityY;
            drops[i].alpha-=0.001;


            if(drops[i].alpha < 0){
                drops[i].alive = false;
            }
        }
    }
}

void Particles::generateParticles()
{

    int newDrops = rand()%600+1;

    if((numDrops + newDrops) > MAX_DROPS)
    {
        newDrops = MAX_DROPS - numDrops;
    }

    for (int i=numDrops; i<numDrops+newDrops; i++){
        drops[i].alive=true;

        drops[i].radius = 1;
        drops[i].xpos = (float)(rand()%5)*0.1;
        drops[i].ypos = (float)(rand()%5)*0.1;



        drops[i].explosionRadius = 0.01;
        drops[i].angle = rand()%180;

        drops[i].red=(float)(rand()%10)/10;
        drops[i].blue=(float)(rand()%10)/10;
        drops[i].green=(float)(rand()%10)/10;

        drops[i].velocityX = sin(drops[i].angle)*drops[i].explosionRadius;
        drops[i].velocityY = cos(drops[i].angle)*drops[i].explosionRadius;

        drops[i].alpha = (float)(rand()%100)/10;
    }

    numDrops += newDrops;
    if(numDrops >= MAX_DROPS)numDrops = 0;
}
