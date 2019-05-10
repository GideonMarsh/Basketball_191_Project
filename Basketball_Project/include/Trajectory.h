#ifndef TRAJECTORY_H
#define TRAJECTORY_H


class Trajectory
{
    public:
        Trajectory();
        virtual ~Trajectory();
        void init();
        static void resize (int, int);
        static void display (void);
        static void key(unsigned char key, int x, int y);
        void Specialkeys(int key, int x, int y);
        static void idle(void);
        void mouse(int btn, int state, int x, int y);
        static void light(void);
        void draw(int argc, char *argv[]);

  //      float Wwidth, Wheight;


    protected:

    private:
};

#endif // TRAJECTORY_H
