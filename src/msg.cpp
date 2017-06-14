#include "msg.h"
#include <string.h>

namespace ros {
  Msg::Msg(char* typeName) {
    _typeName = typeName;
  }

  const char* Msg::getType() {
    return _typeName;
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
