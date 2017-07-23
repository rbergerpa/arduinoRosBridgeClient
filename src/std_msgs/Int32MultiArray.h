#ifndef INT32MULTIARRAY_H
#define  INT32MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int32MultiArray : public ros::NumericArrayMsg<int32_t, long> {
  public:
  Int32MultiArray() : NumericArrayMsg<int32_t, long>("std_msgs/Int32MultiArray") {}
  };
}

#endif


