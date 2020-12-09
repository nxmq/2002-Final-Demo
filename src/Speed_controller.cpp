#include <Romi32U4.h>
#include "Encoders.h"
#include  "Speed_controller.h"
#include "Position_estimation.h"

Romi32U4Motors motors;
Encoder MagneticEncoder; 
Position odometry;

float time_track = 0;

void SpeedController::Init(void)
{
    MagneticEncoder.Init();
    odometry.Init();
}

void SpeedController::Run(float target_velocity_left, float target_velocity_right)
{
    if(MagneticEncoder.UpdateEncoderCounts()){
        time_track = time_track + 50/1000.0;
        float e_left = target_velocity_left - MagneticEncoder.ReadVelocityLeft();
        float e_right = target_velocity_right - MagneticEncoder.ReadVelocityRight();
        
        E_left += e_left;
        E_right += e_right;

        float u_left = Kp*e_left + Ki*E_left;
        float u_right = Kp*e_right + Ki*E_right;

        motors.setEfforts(u_left,u_right);
        odometry.UpdatePose(target_velocity_left,target_velocity_right);   
    }
}

boolean SpeedController::MoveToPosition(float target_x, float target_y)
{
    float tgtspeed = 200;   
    float error_distance = INFINITY;
    float error_distance_last = 0;
    float error_distance_acc = 0;
    float error_theta_last = 0;
    float error_theta_acc = 0;
    float error_theta = 0;
    float v_left_last = 0;
    float v_right_last = 0;
    float a_max_50ms = 13;
    do { 
        if(MagneticEncoder.UpdateEncoderCounts()) {
            Position::pose_data curpose = odometry.ReadPose();
            if(isinf(error_distance)) {
                error_distance_last = error_distance = sqrt(pow((target_x - curpose.X),2) + pow((target_y - curpose.Y),2));
                error_theta_last = error_theta = atan2((target_y - curpose.Y),(target_x - curpose.X)) - curpose.THETA;
            } else {
                error_distance = sqrt(pow((target_x - curpose.X),2) + pow((target_y - curpose.Y),2));
                error_theta = atan2((target_y - curpose.Y),(target_x - curpose.X)) - curpose.THETA;
            }
            error_theta = atan2(sin(error_theta),cos(error_theta)); //angular normalization
            int Kp = 2100;
            int Ki = 1;
            int Kd = 22;
            float u_left = Kp * error_distance + Kd * (error_distance-error_distance_last)/(50/1000.0) + Ki*error_distance_acc - Kp * error_theta - Kd * (error_theta-error_theta_last)/(50/1000.0) - Ki*error_theta_acc;
            float u_right = Kp * error_distance + Kd * (error_distance-error_distance_last)/(50/1000.0) + Ki*error_distance_acc + Kp * error_theta + Kd * (error_theta-error_theta_last)/(50/1000.0) + Ki*error_theta_acc;
            float v_left = constrain(u_left,-tgtspeed,tgtspeed);
            v_left = constrain(v_left,v_left_last-a_max_50ms,v_left_last+a_max_50ms);
            float v_right = constrain(u_right,-tgtspeed,tgtspeed);
            v_right = constrain(v_right,v_right_last-a_max_50ms,v_right_last+a_max_50ms);
            error_distance_last = error_distance;
            error_theta_last = error_theta;
            error_distance_acc += error_distance;
            error_theta_acc += error_theta;
            motors.setEfforts(v_left, v_right);
            odometry.UpdatePose(v_left,v_right);
            v_left_last = v_left;
            v_right_last = v_right;
            Serial.print(v_left);
            Serial.print("\t");
            Serial.print(v_right);
            Serial.print("\t");
            Serial.print(error_distance);
            Serial.print("\t");
            Serial.print(error_theta);
            Serial.println("\t");
        }
    } while (error_distance >= 0.02); //define a distance criteria that lets the robot know that it reached the waypoint.
    return 1;
}

boolean SpeedController::Turn(int degree, int direction)
{
    motors.setEfforts(0, 0);
    int turns = counts*(degree/180.0);
    int count_turn = MagneticEncoder.ReadEncoderCountLeft();

    while(abs(abs(count_turn) - abs(MagneticEncoder.ReadEncoderCountLeft())) <= turns)
    {
        if(!direction) Run(50,-50);
        else Run(-50,50);
    }
    motors.setEfforts(0, 0);
    return 1;
}

boolean SpeedController::Straight(int target_velocity, int time)
{
    float a_max_50ms = 20;

    motors.setEfforts(0, 0);
    unsigned long now = millis();

    while ((unsigned long)(millis() - now) <= time*1000){
        Run(target_velocity,target_velocity);
    }
    motors.setEfforts(0, 0);
    return 1;
}

boolean SpeedController::DriveDistance(int target_velocity, int distance) //in mm/s and cm
{
    motors.setEfforts(0, 0);
    uint32_t duration = 1000*((distance*10)/(float)abs(target_velocity)); //in ms
    unsigned long now = millis();
    while ((unsigned long)(millis() - now) <= duration){
        Run(target_velocity,target_velocity);
    }
    motors.setEfforts(0, 0);
    return 1;
}


boolean SpeedController::Curved(int target_velocity_left, int target_velocity_right, int time) //in mm/s and s
{
    motors.setEfforts(0, 0);
    unsigned long now = millis();

    while ((unsigned long)(millis() - now) <= time*1000){
        Run(target_velocity_left,target_velocity_right);
    }
    motors.setEfforts(0, 0);
    return 1;
}

void SpeedController::Stop()
{
    motors.setEfforts(0,0);
    odometry.Stop();
    time_track = 0;
}