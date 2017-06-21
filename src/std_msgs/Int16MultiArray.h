#ifndef UINT16MULTIARRAY_H
#define  UINT16MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int16MultiArray : public ros::NumericArrayMsg<int16_t>, ros::IntegerBaseClass<int16_t> {
  public:
  Int16MultiArray() : NumericArrayMsg<int16_t>("std_msgs/Int16MultiArray") {}
  };
}

#endif


