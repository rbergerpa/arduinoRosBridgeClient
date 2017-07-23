#ifndef FLOAT64MULTIARRAY_H
#define FLOAT64MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Float64MultiArray : public ros::NumericArrayMsg<double, double> {
  public:
  Float64MultiArray() : NumericArrayMsg<double, double>("std_msgs/Float64MultiArray") {}
  };
}

#endif


