#ifndef ROS_MSG_H
#define ROS_MSG_H
#include <ArduinoJson.h>
#include <arduino.h> // TODO remove after debugging

#define MAX_ARRAY_SIZE 32

char* stringSearch(char *str, char* pattern);

// Base class for messages
namespace ros {
  class Msg {
  public:
    int data_length;
    Msg(char* typeName);

    const char* getType();

    virtual int deserialize(JsonObject& json) = 0;

  private:
    char* _typeName;
  };

  template<typename ValueT, typename ParseT>
    class NumericArrayMsg : public Msg {
  public:
    ValueT data[MAX_ARRAY_SIZE];

  NumericArrayMsg(char* typeName) : Msg(typeName) {}
    virtual int deserialize(JsonObject& json) {
      JsonVariant dataJSON = json["msg"]["data"];
      Serial.print("dataJSON: ");
      dataJSON.printTo(Serial);
      Serial.println();

      data_length = dataJSON.size();
      Serial.print("data_length: ");
      Serial.print(data_length);
      Serial.println();

      for (int i = 0; i < data_length; i++) {
        data[i] = (ParseT) dataJSON[i];
      }

      return 1;
    }
  };
}

#endif

