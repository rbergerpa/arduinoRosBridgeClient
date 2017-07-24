#include "subscriber.h"
#include "node_handle.h"
#include "std_msgs/Float32MultiArray.h"

namespace ros {

  SubscriberBase::SubscriberBase(const char* topic) {
    _topic = topic;
  }

  const char * SubscriberBase::getMsgType() {
    return _msgType;
  }

  const char * SubscriberBase::getTopic() {
    return _topic;
  }

  void SubscriberBase::handleMessage(JsonObject& json) {
       deserialize(json);
       callback();
  }

  Msg* SubscriberBase::newMessage(const char* msgType) {
    if (strcmp(msgType, "std_msgs/Float32MultiArray") == 0) {
      return new std_msgs::Float32MultiArray();
   }
  }
}
