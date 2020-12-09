#include <Romi32U4.h>
#include "Behaviors.h"
#include "Median_filter.h"
#include "IMU.h"
#include "Speed_controller.h"
#include "Wall_following_controller.h"
#include "Music_player.h"
//sensors
IMU_sensor LSM6;

Romi32U4ButtonA buttonA;

//motor-speed controller
SpeedController robot;

//wall following controller
WallFollowingController follower;

//median filter
MedianFilter med_x;
MedianFilter med_y;
MedianFilter med_z;

//Musicplayer
MusicPlayer player;

void Behaviors::Init(void)
{
    robot.Init();
    LSM6.Init();
    med_x.Init();
    med_y.Init();
    med_z.Init();
    player.Init();
}

void Behaviors::Stop(void)
{
    robot.Stop();
}

void Behaviors::UpdateLSM6Data(void) 
{
    auto data_acc = LSM6.ReadAcceleration();
    data[0] = med_x.Filter(data_acc.X)*0.061;
    data[1] = med_y.Filter(data_acc.Y)*0.061;
    data[2] = med_z.Filter(data_acc.Z)*0.061;
}

boolean Behaviors::DetectCollision(void)
{
    return ((abs(data[0]) > threshold) || (abs(data[1]) > threshold));
}

boolean Behaviors::DetectRamp(void)
{
    return(abs(data[0]) > ramp_threshold);
}

void Behaviors::Run(void)
{
    Behaviors::UpdateLSM6Data();
    float speed = 0;
    switch (robot_state)
    {
    case IDLE:
        if(buttonA.getSingleDebouncedRelease()){ 
            Serial.println("Button Pressed");
            robot_state = state_next; 
            robot.Stop();             
        } 
        break;
    
    case WAIT: 
        delay(1000);
        robot_state = DRIVE;
        break;

    case DRIVE:
        if(DetectCollision()){ 
            Serial.println("Collision Detected");
            robot.Stop();
            robot_state = IDLE;
            state_next = REVERSE;
        }
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = IDLE; 
            robot.Stop();             
        } else {
            robot.Run(150,150);
        }
        break;

    case REVERSE:
        Serial.println("Reverse");
        robot.DriveDistance(-50,22);
        robot.Stop();
        robot_state = TURN;
        break; 
    
    case TURN:
        Serial.println("Turn");
        robot.Turn(90,1);
        robot.Stop();
        robot_state = WALL_FOLLOW;
        break;

    case WALL_FOLLOW:
        speed = constrain(follower.Follow(22),-60,60);
        robot.Run(60-speed,60+speed); //speed in [[mm/s]]
        if(DetectRamp()) {
            Serial.println("Ramp Detected");
            robot_state = RAMP;
        }
        break;  
         
    case RAMP:
        robot.DriveDistance(50,45); // ramp distance
        robot.Stop();
        robot_state = POST_RAMP_FOLLOW;
        break;

    case POST_RAMP_FOLLOW: {
        uint32_t duration = 1000*((103)/(float)60); //in ms
        unsigned long now = millis();
        while ((unsigned long)(millis() - now) <= duration){
            speed = constrain(follower.Follow(22),-60,60);
            robot.Run(60-speed,60+speed); //speed in [[mm/s]]
        }
        robot.Stop();
        robot_state = PLAY_VICTORY_MUSIC;
        }
        break;
    case PLAY_VICTORY_MUSIC:
        player.Play();
        robot_state = IDLE;
        break;
    }
}  
