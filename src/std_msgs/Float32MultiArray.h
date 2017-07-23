#ifndef FLOAT32MULTIARRAY_H
#define FLOAT32MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Float32MultiArray : public ros::NumericArrayMsg<float, float> {
  public:
  Float32MultiArray() : NumericArrayMsg<float, float>("std_msgs/Float32MultiArray") {}
  };
}

#endif


