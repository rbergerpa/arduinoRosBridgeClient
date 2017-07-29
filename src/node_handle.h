#ifndef NODE_HANDLE_H
#define NODE_HANDLE_H

#include <Arduino.h>
#include <Ethernet.h>
#include <WebSockets.h>
#include <WebSocketsClient.h>
#include "subscriber.h"
#include "publisher.h"

#define MAX_SUBSCRIBERS 20
#define JSON_BUFFER_SIZE 500

namespace ros {
  class NodeHandle {
    friend class Publisher;
  public:
    NodeHandle();

    void initNode(const char *name, byte* mac, IPAddress  &ip, const char* host);

    int spinOnce();

    int connected();

    void handleWebsocketEvent(WStype_t type, uint8_t * payload, size_t length);
    void logdebug(const char* msg, const char* file="", const char* function = "", int line = 0);
    void loginfo(const char * msg, const char* file="", const char* function = "", int line = 0);
    void logwarn(const char *msg, const char* file="", const char* function = "", int line = 0);
    void logerror(const char*msg, const char* file="", const char* function = "", int line = 0);
    void logfatal(const char*msg, const char* file="", const char* function = "", int line = 0);

    void subscribe(SubscriberBase& subscriber);
    void advertise(Publisher& publisher);

  private:
    WebSocketsClient _webSocket;
    boolean _connected = false;
    const char* _name;
    int _numSubscribers = 0;
    SubscriberBase* _subscribers[MAX_SUBSCRIBERS];

    enum LogLevel {DEBUG, INFO, WARN, ERROR, FATAL};

    void log(LogLevel logLevel, const char * msg, const char* file="", const char* function = "", int line = 0);

    void handleMessage(char* msg);

    SubscriberBase* getSubscriber(const char* topic);

    void publish(JsonObject& json);
  };

  NodeHandle* getNodeHandle();
}

#endif
