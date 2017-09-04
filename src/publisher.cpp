#include "publisher.h"
#include "node_handle.h"
#include <ArduinoJson.h>

namespace ros {
  Publisher::Publisher(const char *topic, Msg* msg) {
      _topic = topic;
      _msgType = msg->getType();
    }


  void Publisher::publish(Msg* msg) {
    StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root["op"] = "publish";
    root["topic"] = _topic;
    root["type"] = _msgType;

    JsonObject& msgJson = root.createNestedObject("msg");
    // Add a blank time stamp so Rosbridge will fill it in
    JsonObject& header = msgJson.createNestedObject("header");
    header.createNestedObject("stamp");
    msg->serialize(msgJson);

    getNodeHandle()->publish(root);
  }

  const char * Publisher::getMsgType() {
    return _msgType;
  }

  const char * Publisher::getTopic() {
    return _topic;
  }

}
