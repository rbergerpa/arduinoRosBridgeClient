#include "node_handle.h"
#include <ArduinoJson.h>

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);


namespace ros {
  static NodeHandle* nodeHandle; // singleton

  NodeHandle* getNodeHandle() {
    return nodeHandle;
  }

  NodeHandle::NodeHandle() {
    nodeHandle = this;
  }

  int NodeHandle::connected() {
    return _connected;
  }

  void NodeHandle::initNode(char *name, byte* mac, IPAddress &ip, const char* host) {
    _name = name;

    if (Ethernet.begin(mac) == 0) {
      Ethernet.begin(mac, ip);
    }

    _webSocket.begin(host, 9090);
    _webSocket.onEvent(webSocketEvent);

    while (! _connected) {
      _webSocket.loop();
    }
  }

  int  NodeHandle::spinOnce() {
    _webSocket.loop();
    return 1;
  }

  void NodeHandle::handleWebsocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
    case WStype_DISCONNECTED:
      _connected = false;
      Serial.println("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      _connected = true;
      Serial.print("[WSc] Connected to url: ");
      Serial.println((char *)payload);
      break;
    case WStype_TEXT:
      handleMessage((char *) payload);
      break;

    default:
      Serial.print("unhandled webSocketEvent type ");
      Serial.println((int) type);
    }
  }

#define MSG_SIZE 512
#define PUBLISH_MSG "{\"op\": \"publish\", \"topic\": \"/rosout\", \"msg\": {\"level\": %d, \"name\": \"%s\", \"topics\": [\"/rosout\"], \"msg\": \"%s\"}}"
  void NodeHandle::log(LogLevel logLevel, const char * msg, const char* file, const char* function, int line) {
    char json[MSG_SIZE];

    // TODO use ArduionoJSON
    // TODO send file, function, line
    // TODO timestamp
    // TODO list of topics
    snprintf(json, MSG_SIZE, PUBLISH_MSG, 1<<logLevel, _name, msg);
    _webSocket.sendTXT(json);
  }

  void NodeHandle::logdebug(const char* msg, const char* file, const char* function, int line) {
    log(DEBUG, msg, file, function, line);
  }

  void NodeHandle::loginfo(const char * msg, const char* file, const char* function, int line) {
    log(INFO, msg, file, function, line);
  }

  void NodeHandle::logwarn(const char *msg, const char* file, const char* function, int line) {
    log(WARN, msg, file, function, line);
  }

  void NodeHandle::logerror(const char*msg, const char* file, const char* function, int line) {
    log(ERROR, msg, file, function, line);
  }

  void NodeHandle:: logfatal(const char*msg, const char* file, const char* function, int line) {
    log(FATAL, msg, file, function, line);
  }

#define SUBSCRIBE_MSG "{\"op\": \"subscribe\",  \"topic\": \"%s\",  \"type\": \"%s\"}"
  void NodeHandle::subscribe(SubscriberBase& subscriber) {
    char json[MSG_SIZE];

    if (_numSubscribers == MAX_SUBSCRIBERS) {
      return;
    }

    _subscribers[_numSubscribers++] = &subscriber;

    snprintf(json, MSG_SIZE, SUBSCRIBE_MSG, subscriber.getTopic(), subscriber.getMsgType());
    _webSocket.sendTXT(json);
  }

  void NodeHandle::handleMessage(char* msg) {
    StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;

    Serial.print("msg: ");
    Serial.println(msg);

    JsonObject& json = jsonBuffer.parseObject(msg);
    Serial.print("parsed: ");
    json.printTo(Serial);
    Serial.println();

    const char* topic = json["topic"];
    Serial.print("topic: ");
    Serial.println(topic);

    SubscriberBase* subscriber = getSubscriber(topic);
    if (subscriber) {
    subscriber->handleMessage(json);
    } else {
      Serial.print("No subscriber found for topic: ");
      Serial.println(topic);
    }
  }

  void NodeHandle::advertise(Publisher& publisher) {
    StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
    char buffer[JSON_BUFFER_SIZE];

    JsonObject& root = jsonBuffer.createObject();
    root["op"] = "advertise";
    root["topic"] = publisher.getTopic();
    root["type"] = publisher.getMsgType();

    int size = root.printTo(buffer, JSON_BUFFER_SIZE);
    // Serial.print("buffer: ");
    // Serial.println(buffer);
    _webSocket.sendTXT(buffer, size);
  }

  void NodeHandle::publish(JsonObject& json) {
    char buffer[JSON_BUFFER_SIZE];

    int size = json.printTo(buffer, JSON_BUFFER_SIZE);
    // Serial.print("buffer: ");
    // Serial.println(buffer);

    _webSocket.sendTXT(buffer, size);
  }

  // TODO replace this with something more efficient
  SubscriberBase* NodeHandle::getSubscriber(const char* topic) {
    for (int i = 0; i < _numSubscribers; i++) {
      SubscriberBase* subscriber = _subscribers[i];
      if (strcmp(topic, subscriber->getTopic()) == 0) {
        return subscriber;
      }
    }

    return NULL;
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  ros::nodeHandle->handleWebsocketEvent(type, payload, length);
}
