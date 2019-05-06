#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/gl.h>


#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


#define MAX_DROPS 500000

#define PI 3.14159


class Particles
{
    public:
        Particles();
        virtual ~Particles();

        int numDrops;


        float mx, my;

        typedef struct{

            bool alive;
            float xpos;
            float ypos;
            float xDir;
            float yDir;
            float red;
            float green;
            float blue;
            float mass;


            float radius;


            float explosionRadius;

            float angle;



            float velocityX;
            float velocityY;
            float alpha;
        }Parts;

        Parts drops[MAX_DROPS];

        void drawParticle();            //drawing
        void lifeTime();                //update
        void generateParticles();       //emitter


    protected:

    private:
};

#endif // PARTICLES_H
