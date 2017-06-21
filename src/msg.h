#ifndef ROS_MSG_H
#define ROS_MSG_H
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

    virtual int deserialize(char* json) = 0;

  private:
    char* _typeName;
  };

  template<typename ValueT>
    class FloatBaseClass {
  protected:
    ValueT parseValue(const char* str) {
      return atof(str);
    }
  };

  template<typename ValueT>
    class IntegerBaseClass {
  protected:
    ValueT parseValue(const char* str) {
      return atof(str);
    }
  };

  template<typename ValueT>
    class NumericArrayMsg : public Msg {
  public:
    ValueT data[MAX_ARRAY_SIZE];

  NumericArrayMsg(char* typeName) : Msg(typeName) {}

    ValueT parseValue(const char* str);

    virtual int deserialize(char* json) {
      char* buf = stringSearch(json, "\"data\": [");
      data_length = 0;

      while (*buf != ']' && data_length < MAX_ARRAY_SIZE) {
        data[data_length] = atof(buf);
        data_length++;

        while (*buf != ',' && *buf != ']') {
          buf++;
        }

        while (*buf == ',' || *buf == ' ') {
          buf++;
        }
      }

      return 1;
    }
  };
}

#endif

