#ifndef FLOAT32MULTIARRAY_H
#define FLOAT32MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Float32MultiArray : public ros::NumericArrayMsg<float> {
  public:
  Float32MultiArray() : NumericArrayMsg<float>("std_msgs/Float32MultiArray") {}

    // TODO: move this to a mixin
    virtual float parseValue(const char* str) {
      return atof(str);
    }

  };
}

#endif


