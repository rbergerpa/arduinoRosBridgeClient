#ifndef INT32MULTIARRAY_H
#define  INT32MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int32MultiArray : public ros::NumericArrayMsg<int32_t>, ros::IntegerBaseClass<int32_t> {
  public:
  Int32MultiArray() : NumericArrayMsg<int32_t>("std_msgs/Int32MultiArray") {}
  };
}

#endif


