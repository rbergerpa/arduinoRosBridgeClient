#ifndef INT64MULTIARRAY_H
#define  INT64MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int64MultiArray : public ros::NumericArrayMsg<int64_t, long> {
  public:
  Int64MultiArray() : NumericArrayMsg<int64_t, long>("std_msgs/Int64MultiArray") {}
  };
}

#endif


