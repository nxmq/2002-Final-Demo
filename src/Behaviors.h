#ifndef BEHAVIORS
#define BEHAVIORS

#include <Romi32U4.h>

class Behaviors{
    private:
       enum ROBOT_STATE {IDLE, DRIVE, RAMP, REVERSE, TURN, WALL_FOLLOW, WAIT, POST_RAMP_FOLLOW, PLAY_VICTORY_MUSIC};
        ROBOT_STATE robot_state = IDLE; //initial state: IDLE
        ROBOT_STATE state_next = WAIT; 
        int threshold = 500;
        int ramp_threshold = 250;
        int data[3] = {0};
    public:
        void Init(void);
        void Stop(void);
        void Run(void);
        boolean DetectCollision(void);
        boolean DetectRamp(void);
        void UpdateLSM6Data(void);
};
#endif