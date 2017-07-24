#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <ArduinoJson.h>
#include "msg.h"

namespace ros {
  class Publisher {
  public:
    Publisher(const char *topic, Msg* msg);
    void publish(Msg* msg);

    const char* getMsgType();
    const char* getTopic();

  private:
    const char* _topic;
    const char* _msgType;
  };
}
#endif
