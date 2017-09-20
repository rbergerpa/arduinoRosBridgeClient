#ifndef ROS_MSG_H
#define ROS_MSG_H
#include <ArduinoJson.h>

#define MAX_ARRAY_SIZE 32

char* stringSearch(char *str, char* pattern);

// Base class for messages
namespace ros {
  class Msg {
  public:
    int data_length;
    Msg(const char* typeName);

    const char* getType();

    bool includeHeader();

    virtual int serialize(JsonObject& json) = 0;
    virtual int deserialize(JsonObject& json) = 0;

  protected:
    bool _includeHeader;

  private:
    const char* _typeName;
  };

  template<typename ValueT, typename ParseT>
    class NumericMsg : public Msg {
  public:
    ValueT data;

  NumericMsg(const char* typeName) : Msg(typeName) {}
  public:
    virtual int deserialize(JsonObject& json) {
      JsonVariant dataJSON = json["msg"]["data"];

      data_length = 1;
      data = (ParseT) dataJSON;

      return 1;
    }

    virtual int serialize(JsonObject& json) {
      json["data"] = data;
      return 1;
    }
  };

  template<typename ValueT, typename ParseT>
    class NumericArrayMsg : public Msg {
  public:
    ValueT *data;

    NumericArrayMsg(const char* typeName) : Msg(typeName) {
      data = static_data;
    }

    virtual int deserialize(JsonObject& json) {
      JsonVariant dataJSON = json["msg"]["data"];

      data_length = dataJSON.size();

      for (int i = 0; i < data_length; i++) {
        data[i] = (ParseT) dataJSON[i];
      }

      return 1;
    }

    virtual int serialize(JsonObject& json) {
      JsonArray& array = json.createNestedArray("data");
      for (int i = 0; i < data_length; i++) {
        array.add(data[i]);
      }

      JsonObject& layout = json.createNestedObject("layout");
      layout.createNestedArray("dim");
      layout["data_offset"] = 0;
    }

  private:
    ValueT static_data[MAX_ARRAY_SIZE];
  };
}

#endif

