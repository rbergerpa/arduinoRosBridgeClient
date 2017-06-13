#include "node_handle.h"


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

namespace ros {
  static NodeHandle* nodeHandle; // singleton

  NodeHandle::NodeHandle() {
    nodeHandle = this;
  }

  int NodeHandle::connected() {
    return _connected;
  }

  void NodeHandle::initNode( byte* mac, const char* host) {
    Serial.print("host: ");
    Serial.println(host);

    if (Ethernet.begin(mac) == 0) {
      Serial.println("Cannot initialize ethernet");
      return;
    }

    _webSocket.begin(host, 9090);
    _webSocket.onEvent(webSocketEvent);
  }

  int  NodeHandle::spinOnce() {
    _webSocket.loop();
    return 1;
  }

  void NodeHandle::handleWebsocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    Serial.print("webSocketEvent type ");
    Serial.println((int) type);
  }

  #define MSG_SIZE 512
  #define PUBLISH_MSG "{\"op\": \"publish\", \"topic\": \"/rosout\", \"msg\": {\"level\": %d, \"name\": \"/arduino_rosbridge\", \"topics\": [\"/rosout\"], \"msg\": \"%s\"}}"
  void NodeHandle::log(LogLevel logLevel, const char * msg) {
    // TODO use Jasson ?
    char publish_json[MSG_SIZE];

    // TODO use publish() after we support String message type
    snprintf(publish_json, MSG_SIZE, PUBLISH_MSG, 1<<logLevel, msg);
    Serial.print("JSON: ");
    Serial.println(publish_json);
    _webSocket.sendTXT(publish_json);
  }

  void NodeHandle::logdebug(const char* msg) {
    log(DEBUG, msg);
  }

  void NodeHandle::loginfo(const char * msg) {
    log(INFO, msg);
  }

  void NodeHandle::logwarn(const char *msg) {
    log(WARN, msg);
  }

  void NodeHandle::logerror(const char*msg) {
    log(ERROR, msg);
  }

  void NodeHandle:: logfatal(const char*msg) {
    log(FATAL, msg);
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  ros::nodeHandle->handleWebsocketEvent(type, payload, length);
}
