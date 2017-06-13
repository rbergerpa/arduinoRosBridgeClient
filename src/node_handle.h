#ifndef NODE_HANDLE_H

#include <Arduino.h>
#include <WebSockets.h>
#include <WebSocketsClient.h>

namespace ros {
class NodeHandle {
    public:
        NodeHandle();

        void initNode(byte* mac, const char* host);

        int spinOnce();

        int connected();

        void handleWebsocketEvent(WStype_t type, uint8_t * payload, size_t length);
        void logdebug(const char* msg);
        void loginfo(const char * msg);
        void logwarn(const char *msg);
        void logerror(const char*msg);
        void logfatal(const char*msg);

    private:
        WebSocketsClient _webSocket;
        boolean _connected = false;

        enum LogLevel {DEBUG, INFO, WARN, ERROR, FATAL};

        void log(LogLevel logLevel, const char * msg);
    };
}

#define NODE_HANDLE_H
#endif
