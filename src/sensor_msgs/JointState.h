#ifndef JOINT_STATE_H
#define  JOINT_STATE_H
#include "../msg.h"

#define MAX_JOINT_ITEMS 5

namespace sensor_msgs {
  class JointState: public ros::Msg {
    public:
      char** name;
      int data_length;
      float* position;
      float* velocity;
      float* effort;
      JointState();

     virtual int serialize(JsonObject& json);
     virtual int deserialize(JsonObject& json);
  };
}
#endif
