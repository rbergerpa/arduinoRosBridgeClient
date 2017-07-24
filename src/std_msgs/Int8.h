#ifndef INT8_H
#define  INT8_H
#include "../msg.h"

namespace std_msgs {
  class Int8 : public ros::NumericMsg<int8_t, int> {
  public:
  Int8() : NumericMsg<int8_t, int>("std_msgs/Int8") {}
  };
}

#endif


