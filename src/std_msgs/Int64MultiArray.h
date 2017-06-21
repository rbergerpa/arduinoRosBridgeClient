#ifndef INT64MULTIARRAY_H
#define  INT64MULTIARRAY_H
#include "../msg.h"

namespace std_msgs {
  class Int64MultiArray : public ros::NumericArrayMsg<int64_t>, ros::IntegerBaseClass<int64_t> {
  public:
  Int64MultiArray() : NumericArrayMsg<int64_t>("std_msgs/Int64MultiArray") {}
  };
}

#endif


