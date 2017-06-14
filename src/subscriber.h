#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "msg.h"

namespace ros {
  class SubscriberBase {
  public:
    SubscriberBase(const char* topic);

    void handleMessage(char *data);

    const char* getMsgType();
    const char* getTopic();

  protected:
    const char* _msgType;
    void registerSubscriber();
    Msg* newMessage(const char* msgType);
    virtual void callback() = 0;
    virtual void deserialize(char* msgJSON) = 0;
  private:
    const char* _topic;
  };

  // TODO: add bound finction subscriber

  //  Standalone function subscriber.
  template<typename MsgT>
    class Subscriber: public SubscriberBase {
  public:
    typedef void(*CallbackT)(const MsgT&);

  Subscriber(const char* topic, CallbackT callback): SubscriberBase(topic), _callback(callback) {
      _msgType = _msg.getType();
    }

    virtual void deserialize(char* msgJSON) {
      _msg.deserialize(msgJSON);
    }

    virtual void callback() {
      (*_callback)(_msg);
    }

  private:
    CallbackT _callback;
    MsgT _msg;
  };
}

#endif
