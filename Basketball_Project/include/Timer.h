#ifndef TIMER_H
#define TIMER_H

#include<time.h>

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        void start();
        void stop();
        void reset();

        clock_t getTicks();
        clock_t startAt;

    protected:

    private:
};

#endif // TIMER_H
