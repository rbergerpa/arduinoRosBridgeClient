#ifndef INT8MULTIARRAY_H
#define  INT8MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int8MultiArray : public ros::NumericArrayMsg<int8_t>, ros::IntegerBaseClass<int8_t> {
  public:
  Int8MultiArray() : NumericArrayMsg<int8_t>("std_msgs/Int8MultiArray") {}
  };
}

#endif


