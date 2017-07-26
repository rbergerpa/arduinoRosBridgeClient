#ifndef ACKERMANN_DRIVE_H
#define  ACKERMANN_DRIVE_H
#include "../msg.h"

namespace ackermann_msgs {
  class AckermannDrive : public ros::Msg {
    public:

     float steering_angle;
     float steering_angle_velocity;
     float speed;
     float acceleration;
     float jerk;

     AckermannDrive();

     virtual int serialize(JsonObject& json);
     virtual int deserialize(JsonObject& json);
  };
}

#endif
