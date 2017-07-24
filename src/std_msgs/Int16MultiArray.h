#ifndef INT16MULTIARRAY_H
#define  INT16MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int16MultiArray : public ros::NumericArrayMsg<int16_t, int> {
  public:
  Int16MultiArray() : NumericArrayMsg<int16_t, int>("std_msgs/Int16MultiArray") {}
  };
}

#endif


