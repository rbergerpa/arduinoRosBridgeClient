#ifndef FLOAT64MULTIARRAY_H
#define FLOAT64MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Float64MultiArray : public ros::NumericArrayMsg<double>, ros::FloatBaseClass<double> {
  public:
  Float64MultiArray() : NumericArrayMsg<double>("std_msgs/Float64MultiArray") {}
  };
}

#endif


