#ifndef CLOCK_H
#define CLOCK_H

static const int FPS = 30;
static const int MSPF = (int)(1000.0/FPS);
static const double SPF = 1.0/FPS;

class Clock {
    private:
        int time;
    public:
        Clock();
        int GetTimeDiff();
        void Sleep();
};

#endif
