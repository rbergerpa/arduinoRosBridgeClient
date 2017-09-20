#ifndef BOOL_H
#define  BOOL_H
#include "../msg.h"

namespace std_msgs {
  class Bool : public ros::Msg {
  public:
    bool data;

    Bool();

    virtual int serialize(JsonObject& json);
    virtual int deserialize(JsonObject& json);
  };
}

#endif


