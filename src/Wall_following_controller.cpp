#include <Romi32U4.h>
#include "Encoders.h"
#include "Wall_following_controller.h"
#include "IR_sensor.h"

IRsensor SharpIR;
void WallFollowingController::Init(void)
{
    SharpIR.Init();
}

float WallFollowingController::Follow(float target_distance)
{
  E_distance = target_distance - SharpIR.ReadData();
  float speed = Kp*E_distance + Kd * (E_distance-prev_e_distance);
  prev_e_distance = E_distance;
  return speed;
}