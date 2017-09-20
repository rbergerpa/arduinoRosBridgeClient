#include "msg.h"
#include <string.h>

namespace ros {
  Msg::Msg(const char* typeName) {
    _typeName = typeName;
    _includeHeader = false;
  }

  const char* Msg::getType() {
    return _typeName;
  }

  bool Msg::includeHeader() {
    return _includeHeader;
  }
}

// Returns pointer to character after first occurance of str)
char* stringSearch(char *str, char* pattern) {
  char* s = strstr(str, pattern);

  if (s) {
    s += strlen(pattern);
  }

  return s;
}
