#ifndef IMU_H
#define  IMU_H
#include <rosBridgeClient.h>
#include "../msg.h"

struct Quarternion {
  float x;
  float y;
  float z;
  float w;
};

struct Vector3 {
  float x;
  float y;
  float z;
};

namespace sensor_msgs {
  class Imu: public ros::Msg {
 public:
    Quarternion orientation;
    Vector3 angular_velocity;
    Vector3 linear_acceleration;

    Imu();

    virtual int serialize(JsonObject& json);
    virtual int deserialize(JsonObject& json);
  };
}

#endif
