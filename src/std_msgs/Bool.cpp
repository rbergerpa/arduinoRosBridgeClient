#include "Bool.h"

namespace std_msgs {
  Bool::Bool() : Msg("std_msgs/Bool") {
    data = false;
  }

 int Bool::serialize(JsonObject& json) {
   json["data"] = data;
  }

  int Bool:: deserialize(JsonObject& json) {
    data = json["data"];
  }
}
